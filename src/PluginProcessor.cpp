/*
1. HEADER AND INCLUDES
   ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin processor.
   ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "StateManagement.h" // Include the StateManagement header
#include "RTNeuralLSTM.h"

// ... [rest of the file remains unchanged]


//==============================================================================
// 2. CONSTRUCTOR AND DESTRUCTOR

// 2.1 Constructor for the ProteusAudioProcessor class.
ProteusAudioProcessor::ProteusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
    treeState(*this, nullptr, "PARAMETER", { std::make_unique<AudioParameterFloat>(GAIN_ID, GAIN_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),
                        std::make_unique<AudioParameterFloat>(BASS_ID, BASS_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                        std::make_unique<AudioParameterFloat>(MID_ID, MID_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                        std::make_unique<AudioParameterFloat>(TREBLE_ID, TREBLE_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                        std::make_unique<AudioParameterFloat>(MASTER_ID, MASTER_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5) })
#endif
{
    driveParam = treeState.getRawParameterValue (GAIN_ID);
    masterParam = treeState.getRawParameterValue (MASTER_ID);
    bassParam = treeState.getRawParameterValue (BASS_ID);
    midParam = treeState.getRawParameterValue (MID_ID);
    trebleParam = treeState.getRawParameterValue (TREBLE_ID);

    auto bassValue = static_cast<float> (bassParam->load());
    auto midValue = static_cast<float> (midParam->load());
    auto trebleValue = static_cast<float> (trebleParam->load());

    eq4band.setParameters(bassValue, midValue, trebleValue, 0.0);
    eq4band2.setParameters(bassValue, midValue, trebleValue, 0.0);

    pauseVolume = 3;

    cabSimIRa.load(BinaryData::default_ir_wav, BinaryData::default_ir_wavSize);
}

// 2.2 Destructor for the ProteusAudioProcessor class.
ProteusAudioProcessor::~ProteusAudioProcessor()
{
}

//==============================================================================
// 3. PLUGIN INFORMATION FUNCTIONS

// 3.1 Return the name of the plugin.
const String ProteusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

// 3.2 Check if the plugin accepts MIDI input.
bool ProteusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

// 3.3 Check if the plugin produces MIDI output.
bool ProteusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

// 3.4 Check if the plugin is a MIDI effect.
bool ProteusAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

// 3.5 Return the tail length in seconds.
double ProteusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

// 3.6 Return the number of programs.
int ProteusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

// 3.7 Return the current program.
int ProteusAudioProcessor::getCurrentProgram()
{
    return 0;
}

// 3.8 Set the current program.
void ProteusAudioProcessor::setCurrentProgram (int index)
{
}

// 3.9 Return the program name.
const String ProteusAudioProcessor::getProgramName (int index)
{
    return {};
}

// 3.10 Change the program name.
void ProteusAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
// 4. AUDIO PROCESSING FUNCTIONS

// 4.1 Prepare the plugin for playback.
void ProteusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    *dcBlocker.state = *dsp::IIR::Coefficients<float>::makeHighPass (sampleRate, 35.0f);

    // prepare resampler for target sample rate: 44.1 kHz
    constexpr double targetSampleRate = 44100.0;
    resampler.prepareWithTargetSampleRate({ sampleRate, (uint32)samplesPerBlock, 2 }, targetSampleRate);

    dsp::ProcessSpec specMono { sampleRate, static_cast<uint32> (samplesPerBlock), 1 };
    dsp::ProcessSpec spec{ sampleRate, static_cast<uint32> (samplesPerBlock), 2 };

    dcBlocker.prepare (spec); 

    LSTM.reset();
    LSTM2.reset();

    // Set up IR
    cabSimIRa.prepare(spec);
}

// 4.2 Release any resources when playback stops.
void ProteusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

// 4.3 Check if the bus layout is supported.
bool ProteusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

// 4.4 Process the audio buffer.
void ProteusAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;

    auto driveValue = static_cast<float> (driveParam->load());
    auto masterValue = static_cast<float> (masterParam->load());
    auto bassValue = static_cast<float> (bassParam->load());
    auto midValue = static_cast<float> (midParam->load());
    auto trebleValue = static_cast<float> (trebleParam->load());

    // Setup Audio Data
    const int numSamples = buffer.getNumSamples();
    const int numInputChannels = getTotalNumInputChannels();
    const int sampleRate = getSampleRate();

    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);

    // Overdrive Pedal ================================================================== 
    if (fw_state == 1 && model_loaded == true) {
        
        if (conditioned == false) {
            // Apply ramped changes for gain smoothing
            if (driveValue == previousDriveValue)
            {
                buffer.applyGain(driveValue*2.5);
            }
             else {
                buffer.applyGainRamp(0, (int) buffer.getNumSamples(), previousDriveValue * 2.5, driveValue * 2.5);
                previousDriveValue = driveValue;
            }
            auto block44k = resampler.processIn(block);
            for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
            {
                // Apply LSTM model
                if (ch == 0) {
                    LSTM.process(block44k.getChannelPointer(0), block44k.getChannelPointer(0), (int)block44k.getNumSamples());
                }
                else if (ch == 1) {
                    LSTM2.process(block44k.getChannelPointer(1), block44k.getChannelPointer(1), (int)block44k.getNumSamples());
                }
            }
            resampler.processOut(block44k, block);
        } else {
            buffer.applyGain(1.5); // Apply default boost to help sound
            // resample to target sample rate
            
            auto block44k = resampler.processIn(block);
            for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
            {
                // Apply LSTM model
                if (ch == 0) {
                    LSTM.process(block44k.getChannelPointer(0), driveValue, block44k.getChannelPointer(0), (int)block44k.getNumSamples());
                }
                else if (ch == 1) {
                    LSTM2.process(block44k.getChannelPointer(1), driveValue, block44k.getChannelPointer(1), (int)block44k.getNumSamples());
                }
            }
            resampler.processOut(block44k, block);
        }

        dcBlocker.process(context);

        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        {
            // Apply EQ
            if (ch == 0) {
                eq4band.process(buffer.getReadPointer(0), buffer.getWritePointer(0), midiMessages, numSamples, numInputChannels, sampleRate);
            
            }
            else if (ch == 1) {
                eq4band2.process(buffer.getReadPointer(1), buffer.getWritePointer(1), midiMessages, numSamples, numInputChannels, sampleRate);
            }
        }

        if (cab_state == 1) {
            cabSimIRa.process(context); // Process IR a on channel 0
            buffer.applyGain(2.0);
        }

        // Master Volume 
        // Apply ramped changes for gain smoothing
        if (masterValue == previousMasterValue)
        {
            buffer.applyGain(masterValue);
        }
        else {
            buffer.applyGainRamp(0, (int) buffer.getNumSamples(), previousMasterValue, masterValue);
            previousMasterValue = masterValue;
        }

        // Smooth pop sound when changing models
        if (pauseVolume > 0) {
            if (pauseVolume > 2)
                buffer.applyGain(0.0);
            else if (pauseVolume == 2)
                buffer.applyGainRamp(0, (int)buffer.getNumSamples(), 0, masterValue / 2);
            else
                buffer.applyGainRamp(0, (int)buffer.getNumSamples(), masterValue / 2, masterValue);
            pauseVolume -= 1;
        }
    }
}

//==============================================================================
// 5. EDITOR FUNCTIONS

// 5.1 Check if the plugin has an editor.
bool ProteusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

// 5.2 Create the plugin editor.
AudioProcessorEditor* ProteusAudioProcessor::createEditor()
{
    return new ProteusAudioProcessorEditor (*this);
}

//==============================================================================
// 6. STATE MANAGEMENT FUNCTIONS

// 6.1 Store the plugin state.
void ProteusAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    stateManager.getStateInformation(destData, treeState, fw_state, folder, saved_model, current_model_index, cab_state);
}

// 6.2 Restore the plugin state.
void ProteusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    stateManager.setStateInformation(data, sizeInBytes, treeState, fw_state, saved_model, current_model_index, cab_state, folder, getActiveEditor());
}


// 6.3 Set the EQ parameters for the amplifier.
void ProteusAudioProcessor::set_ampEQ(float bass_slider, float mid_slider, float treble_slider)
{
    stateManager.set_ampEQ(bass_slider, mid_slider, treble_slider, eq4band, eq4band2);
}


// 6.4 Load the configuration from a file.
void ProteusAudioProcessor::loadConfig(File configFile)
{
    stateManager.loadConfig(configFile, conditioned, model_loaded, &suspendProcessingFunction, pauseVolume, LSTM, LSTM2);
}

//==============================================================================
// 7. PLUGIN CREATION

// This creates new instances of the plugin.
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProteusAudioProcessor();
}
