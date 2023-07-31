/*
/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define GAIN_MODULE1_NAME "Module1"
#define GAIN_MODULE2_ID "Module2_ID"
#define GAIN_MODULE2_NAME "Module2"
#define GAIN_ID3 "Gain3_ID"
#define GAIN_NAME3 "Gain3"
#define GAIN_ID4 "Gain4_ID"
#define GAIN_NAME4 "Gain4"

ProteusAudioProcessor::ProteusAudioProcessor()
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
    conditioned3(false), // Initialize conditioned3 with the desired value

    // Your code for treeState initialization remains 
    firmwareState(1), // Initialize firmwareState with the desired value
    treeState(*this, nullptr, "PARAMETER", {

        // Gain for Module 1
        std::make_unique<AudioParameterFloat>(GAIN_MODULE1_ID, GAIN_MODULE1_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),
        // Gain for Module 2
        std::make_unique<AudioParameterFloat>(GAIN_MODULE2_ID, GAIN_MODULE2_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),
        // Other parameters for both modules
        std::make_unique<AudioParameterFloat>(BASS_ID, "Bass", NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
        std::make_unique<AudioParameterFloat>(MID_ID, "Mid", NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
        std::make_unique<AudioParameterFloat>(TREBLE_ID, "Treble", NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
        std::make_unique<AudioParameterFloat>(MASTER_ID, "Master", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),
        std::make_unique<AudioParameterFloat>(GAIN_ID3, GAIN_NAME3, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f), // Add this line for LSTM3
        std::make_unique<AudioParameterFloat>(GAIN_ID4, GAIN_NAME4, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f) // Add this line for LSTM4
    })
{
    driveParam = treeState.getRawParameterValue(GAIN_ID);
    masterParam = treeState.getRawParameterValue(MASTER_ID);
    bassParam = treeState.getRawParameterValue(BASS_ID);
    midParam = treeState.getRawParameterValue(MID_ID);
    trebleParam = treeState.getRawParameterValue(TREBLE_ID);

    auto bassValue = static_cast<float>(bassParam->load());
    auto midValue = static_cast<float>(midParam->load());
    auto trebleValue = static_cast<float>(trebleParam->load());

    eq4band.setParameters(bassValue, midValue, trebleValue, 0.0);
    eq4band2.setParameters(bassValue, midValue, trebleValue, 0.0);

    pauseVolume = 3;

    cabSimIRa.load(BinaryData::default_ir_wav, BinaryData::default_ir_wavSize);

    // Add these declarations at the appropriate location in your code
    RT_LSTM LSTM3;
    RT_LSTM LSTM4;
}

ProteusAudioProcessor::~ProteusAudioProcessor()
{
}
void ProteusAudioProcessor::loadConfig2()
{
    // Set the parameters directly
    *driveParam = 0.5;
    *masterParam = 0.5;
    // ...and so on for the other parameters
}



void ProteusAudioProcessor::loadConfig3()
{
    // Set the parameters directly
    *driveParam = 0.5;
    *masterParam = 0.5;
    // ...and so on for the other parameters
}

void ProteusAudioProcessor::loadConfig4()
{
    // Set the parameters directly
    *driveParam = 0.5;
    *masterParam = 0.5;
    // ...and so on for the other parameters
}

//==============================================================================
const String ProteusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ProteusAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool ProteusAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool ProteusAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double ProteusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ProteusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ProteusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ProteusAudioProcessor::setCurrentProgram(int index)
{
}

const String ProteusAudioProcessor::getProgramName(int index)
{
    return {};
}

void ProteusAudioProcessor::changeProgramName(int index, const String& newName)
{
}

void ProteusAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    *dcBlocker.state = *dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 35.0f);

    // prepare resampler for target sample rate: 44.1 kHz
    constexpr double targetSampleRate = 44100.0;
    resampler.prepareWithTargetSampleRate({ sampleRate, (uint32)samplesPerBlock, 2 }, targetSampleRate);

    dsp::ProcessSpec specMono{ sampleRate, static_cast<uint32>(samplesPerBlock), 1 };
    dsp::ProcessSpec spec{ sampleRate, static_cast<uint32>(samplesPerBlock), 2 };

    dcBlocker.prepare(spec);

    LSTM.reset();
    LSTM2.reset();
    LSTM3.reset();
    LSTM4.reset();

    // Set up IR
    cabSimIRa.prepare(spec);

    // Initialize driveSliderAttach3
    driveSliderAttach3.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    driveSliderAttach3.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(driveSliderAttach3);

    // Initialize odDriveKnob3
    odDriveKnob3.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    odDriveKnob3.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(odDriveKnob3);

    // Other UI component initialization...

    // Other code...
}

void ProteusAudioProcessor::releaseResources()
{
    // ... (implementation of releaseResources)
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ProteusAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
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
#endif

void ProteusAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // This is the place for the actual processing
    if (fw_state == 1 && model_loaded == true) {
        // Process audio buffer with first LSTM model
        LSTM.process(buffer.getReadPointer(0), buffer.getWritePointer(0), buffer.getNumSamples());
        LSTM2.process(buffer.getReadPointer(1), buffer.getWritePointer(1), buffer.getNumSamples());

        // Store output of first LSTM model
        AudioBuffer<float> output1 = buffer;

        // Process output of first LSTM model with second LSTM model
        LSTM.process(output1.getReadPointer(0), buffer.getWritePointer(0), buffer.getNumSamples());
        LSTM2.process(output1.getReadPointer(1), buffer.getWritePointer(1), buffer.getNumSamples());
    }

    // Apply ramped changes for gain smoothing
    auto driveValue = static_cast<float>(driveParam->load());
    auto masterValue = static_cast<float>(masterParam->load());

    if (driveValue == previousDriveValue)
    {
        buffer.applyGain(driveValue * 2.5);
    }
    else {
        buffer.applyGainRamp(0, buffer.getNumSamples(), previousDriveValue * 2.5, driveValue * 2.5);
        previousDriveValue = driveValue;
    }

    auto block44k = resampler.processIn(buffer);

    // Apply LSTM models
    if (fw_state == 1 && model_loaded == true && conditioned == false) {
        LSTM.process(block44k.getChannelPointer(0), block44k.getChannelPointer(0), buffer.getNumSamples());
        LSTM2.process(block44k.getChannelPointer(1), block44k.getChannelPointer(1), buffer.getNumSamples());
    } else {
        buffer.applyGain(1.5); // Apply default boost to help sound
        LSTM.process(block44k.getChannelPointer(0), driveValue, block44k.getChannelPointer(0), buffer.getNumSamples());
        LSTM2.process(block44k.getChannelPointer(1), driveValue, block44k.getChannelPointer(1), buffer.getNumSamples());
    }

    resampler.processOut(block44k, buffer);

    // Apply the third LSTM model if not conditioned
    auto driveValue3 = static_cast<float>(treeState.getRawParameterValue(GAIN_ID3)->load());
    auto pauseVolume2 = 3;
    if (conditioned3 == false) {
        if (driveValue3 == previousDriveValue3)
        {
            buffer.applyGain(driveValue3 * 2.5);
        }
        else {
            buffer.applyGainRamp(0, buffer.getNumSamples(), previousDriveValue3 * 2.5, driveValue3 * 2.5);
            previousDriveValue3 = driveValue3;
        }

        auto block44k3 = resampler3.processIn(buffer);

        if (fw_state == 1 && model_loaded == true) {
            LSTM3.process(block44k3.getChannelPointer(0), block44k3.getChannelPointer(0), buffer.getNumSamples());
            LSTM4.process(block44k3.getChannelPointer(1), block44k3.getChannelPointer(1), buffer.getNumSamples());
        } else {
            buffer.applyGain(1.5); // Apply default boost to help sound
            LSTM3.process(block44k3.getChannelPointer(0), driveValue3, block44k3.getChannelPointer(0), buffer.getNumSamples());
            LSTM4.process(block44k3.getChannelPointer(1), driveValue3, block44k3.getChannelPointer(1), buffer.getNumSamples());
        }

        resampler3.processOut(block44k3, buffer);
    }

    dcBlocker.process(dsp::ProcessContextReplacing<float>(buffer));

    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
        // Apply EQ
        if (ch == 0) {
            eq4band.process(buffer.getReadPointer(0), buffer.getWritePointer(0), midiMessages, buffer.getNumSamples(), totalNumInputChannels, getSampleRate());
        }
        else if (ch == 1) {
            eq4band2.process(buffer.getReadPointer(1), buffer.getWritePointer(1), midiMessages, buffer.getNumSamples(), totalNumInputChannels, getSampleRate());
        }
    }

    if (cab_state == 1) {
        cabSimIRa.process(dsp::ProcessContextReplacing<float>(buffer)); // Process IR a on channel 0
        buffer.applyGain(2.0);
    }

    // Clip
    for (int ch = 0; ch < buffer.getNumChannels(); ++ch) {
        for (int i = 0; i < buffer.getNumSamples(); i++) {
            if (buffer.getSample(ch, i) > 1.0f) {
                buffer.setSample(ch, i, 1.0f);
            }
            else if (buffer.getSample(ch, i) < -1.0f) {
                buffer.setSample(ch, i, -1.0f);
            }
        }
    }

    // Smooth pop sound when changing models
    if (pauseVolume > 0) {
        buffer.applyGainRamp(0, buffer.getNumSamples(), 0.0, driveValue);
        pauseVolume--;
    }

    if (pauseVolume2 > 0) {
        buffer.applyGainRamp(0, buffer.getNumSamples(), 0.0, driveValue3);
        pauseVolume2--;
    }

    // Update current values for next iteration
    auto bassValue = static_cast<float>(bassParam->load());
    auto midValue = static_cast<float>(midParam->load());
    auto trebleValue = static_cast<float>(trebleParam->load());

    eq4band.setParameters(bassValue, midValue, trebleValue, 0.0);
    eq4band2.setParameters(bassValue, midValue, trebleValue, 0.0);

    // save current drive value for next ramp
    previousDriveValue = driveValue;
    previousMasterValue = masterValue;
}

void ProteusAudioProcessor::processBlockBypassed(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // This is the place for the actual processing
    if (fw_state == 1 && model_loaded == true) {
        // Process audio buffer with first LSTM model
        LSTM.process(buffer.getReadPointer(0), buffer.getWritePointer(0), buffer.getNumSamples());
        LSTM2.process(buffer.getReadPointer(1), buffer.getWritePointer(1), buffer.getNumSamples());

        // Store output of first LSTM model
        AudioBuffer<float> output1 = buffer;

        // Process output of first LSTM model with second LSTM model
        LSTM.process(output1.getReadPointer(0), buffer.getWritePointer(0), buffer.getNumSamples());
        LSTM2.process(output1.getReadPointer(1), buffer.getWritePointer(1), buffer.getNumSamples());
    }

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
}

void ProteusAudioProcessor::processBlockRealtime(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    processBlock(buffer, midiMessages);
}

//==============================================================================
bool ProteusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ProteusAudioProcessor::createEditor()
{
    return new ProteusAudioProcessorEditor(*this);
}

//==============================================================================
void ProteusAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // Create an XmlElement object to store the current state of your parameters
    std::unique_ptr<XmlElement> xml (new XmlElement ("MyPluginSettings"));

    // Store the value of each parameter in the XmlElement
    xml->setAttribute ("driveParam", *driveParam);
    xml->setAttribute ("masterParam", *masterParam);
    xml->setAttribute ("bassParam", *bassParam);
    xml->setAttribute ("midParam", *midParam);
    xml->setAttribute ("trebleParam", *trebleParam);

    // Convert the XmlElement to a string and store it in the MemoryBlock
    copyXmlToBinary (*xml, destData);
}

void ProteusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Convert the data back into an XmlElement
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    // If the XmlElement isn't null and its tag matches the one you used when saving, you can restore the parameters
    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName ("MyPluginSettings"))
        {
            // Restore the parameters from the XmlElement
            *driveParam = xmlState->getDoubleAttribute ("driveParam", 1.0);
            *masterParam = xmlState->getDoubleAttribute ("masterParam", 1.0);
            *bassParam = xmlState->getDoubleAttribute ("bassParam", 1.0);
            *midParam = xmlState->getDoubleAttribute ("midParam", 1.0);
            *trebleParam = xmlState->getDoubleAttribute ("trebleParam", 1.0);
        }
    }
}
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProteusAudioProcessor();
}
