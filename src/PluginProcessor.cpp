
/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
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
    // Initialize the treeState with the audio parameters
    treeState(*this, nullptr, "PARAMETER", { std::make_unique<AudioParameterFloat>(GAIN1_ID, GAIN1_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),
                                            std::make_unique<AudioParameterFloat>(BASS1_ID, BASS1_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                                            std::make_unique<AudioParameterFloat>(MID1_ID, MID1_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                                            std::make_unique<AudioParameterFloat>(TREBLE1_ID, TREBLE1_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                                            std::make_unique<AudioParameterFloat>(MASTER1_ID, MASTER1_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5),
                                            std::make_unique<AudioParameterFloat>(GAIN2_ID, GAIN2_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),
                                            std::make_unique<AudioParameterFloat>(BASS2_ID, BASS2_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                                            std::make_unique<AudioParameterFloat>(MID2_ID, MID2_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                                            std::make_unique<AudioParameterFloat>(TREBLE2_ID, TREBLE2_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                                            std::make_unique<AudioParameterFloat>(MASTER2_ID, MASTER2_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5)})
#endif
{
    // Initialize parameters
    driveParam1 = treeState.getRawParameterValue(GAIN1_ID);
    masterParam1 = treeState.getRawParameterValue(MASTER1_ID);
    bassParam1 = treeState.getRawParameterValue(BASS1_ID);
    midParam1 = treeState.getRawParameterValue(MID1_ID);
    trebleParam1 = treeState.getRawParameterValue(TREBLE1_ID);

    // Load parameter values for Container 1
    auto bassValue1 = static_cast<float>(bassParam1->load());
    auto midValue1 = static_cast<float>(midParam1->load());
    auto trebleValue1 = static_cast<float>(trebleParam1->load());

    // Update EQ band parameters for Container 1
    eq4band1.setParameters(bassValue1, midValue1, trebleValue1, 0.0);
    eq4band2_1.setParameters(bassValue1, midValue1, trebleValue1, 0.0);

    // Assign parameter values for Container 2
    driveParam2 = treeState.getRawParameterValue(GAIN2_ID);
    masterParam2 = treeState.getRawParameterValue(MASTER2_ID);
    bassParam2 = treeState.getRawParameterValue(BASS2_ID);
    midParam2 = treeState.getRawParameterValue(MID2_ID);
    trebleParam2 = treeState.getRawParameterValue(TREBLE2_ID);

    // Load parameter values for Container 2
    auto bassValue2 = static_cast<float>(bassParam2->load());
    auto midValue2 = static_cast<float>(midParam2->load());
    auto trebleValue2 = static_cast<float>(trebleParam2->load());

    // Update EQ band parameters for Container 2
    eq4band3.setParameters(bassValue2, midValue2, trebleValue2, 0.0);
    eq4band4.setParameters(bassValue2, midValue2, trebleValue2, 0.0);

    pauseVolume = 3;

    // Initialize LSTM models
    LSTM1.reset();
    LSTM2_1.reset();
    LSTM3.reset();
    LSTM4.reset();
}

void ProteusAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void ProteusAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback initialization
    dcBlocker.state = *dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 35.0f);

    // prepare resampler for target sample rate: 44.1 kHz
    constexpr double targetSampleRate = 44100.0;
    //resampler.prepareWithTargetSampleRate ({ sampleRate, (uint32) samplesPerBlock, 1 }, targetSampleRate);
    resampler.prepareWithTargetSampleRate({ sampleRate, (uint32)samplesPerBlock, 2 }, targetSampleRate);

    dsp::ProcessSpec specMono{ sampleRate, static_cast<uint32>(samplesPerBlock), 1 };
    dsp::ProcessSpec spec{ sampleRate, static_cast<uint32>(samplesPerBlock), 2 };

    dcBlocker.prepare(spec);

    // Reset LSTM models
    LSTM1.reset();
    LSTM2_1.reset();
    LSTM3.reset();
    LSTM4.reset();

    // Set up IR
    cabSimIRa.prepare(spec);

}

void ProteusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ProteusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return checkBusesLayoutSupport(layouts);
}
#endif


void ProteusAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    processAudio(buffer, midiMessages);
        ScopedNoDenormals noDenormals;

    // Load parameter values for Container 1
    auto driveValue1 = static_cast<float> (driveParam1->load());
    auto masterValue1 = static_cast<float> (masterParam1->load());
    auto bassValue1 = static_cast<float> (bassParam1->load());
    auto midValue1 = static_cast<float> (midParam1->load());
    auto trebleValue1 = static_cast<float> (trebleParam1->load());

    // TODO: Load parameter values for Container 2 here

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
                    LSTM1.process(block44k.getChannelPointer(0), block44k.getChannelPointer(0), (int)block44k.getNumSamples());
                }
                else if (ch == 1) {
                    LSTM2_1.process(block44k.getChannelPointer(1), block44k.getChannelPointer(1), (int)block44k.getNumSamples());
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
                    LSTM1.process(block44k.getChannelPointer(0), driveValue, block44k.getChannelPointer(0), (int)block44k.getNumSamples());
                }
                else if (ch == 1) {
                    LSTM2_1.process(block44k.getChannelPointer(1), driveValue, block44k.getChannelPointer(1), (int)block44k.getNumSamples());
                }
            }
            resampler.processOut(block44k, block);
        }

        dcBlocker.process(context);

        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        {
            // Apply EQ
            if (ch == 0) {
                eq4band1.process(buffer.getReadPointer(0), buffer.getWritePointer(0), midiMessages, numSamples, numInputChannels, sampleRate);
            
            }
            else if (ch == 1) {
                eq4band2_1.process(buffer.getReadPointer(1), buffer.getWritePointer(1), midiMessages, numSamples, numInputChannels, sampleRate);
            }
        }
}

 // Overdrive Pedal 2 ================================================================== 
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
                    LSTM3.process(block44k.getChannelPointer(0), block44k.getChannelPointer(0), (int)block44k.getNumSamples());
                }
                else if (ch == 1) {
                    LSTM3.process(block44k.getChannelPointer(1), block44k.getChannelPointer(1), (int)block44k.getNumSamples());
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
                    LSTM3.process(block44k.getChannelPointer(0), driveValue, block44k.getChannelPointer(0), (int)block44k.getNumSamples());
                }
                else if (ch == 1) {
                    LSTM4.process(block44k.getChannelPointer(1), driveValue, block44k.getChannelPointer(1), (int)block44k.getNumSamples());
                }
            }
            resampler.processOut(block44k, block);
        }

        dcBlocker.process(context);

        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        {
            // Apply EQ
            if (ch == 0) {
                eq4band3.process(buffer.getReadPointer(0), buffer.getWritePointer(0), midiMessages, numSamples, numInputChannels, sampleRate);
            
            }
            else if (ch == 1) {
                eq4band4.process(buffer.getReadPointer(1), buffer.getWritePointer(1), midiMessages, numSamples, numInputChannels, sampleRate);
            }
        }
        if (cab_state == 1) {
            cabSimIRa.process(context); // Process IR a on channel 0
            buffer.applyGain(2.0);
        //} else {
        //    buffer.applyGain(0.7);
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
bool ProteusAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* ProteusAudioProcessor::createEditor()
{
    return new ProteusAudioProcessorEditor (*this);
}

//==============================================================================
void ProteusAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    saveStateInformation( 
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    auto state = treeState.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    xml->setAttribute ("fw_state", fw_state);
    xml->setAttribute("folder", folder.getFullPathName().toStdString());
    xml->setAttribute("saved_model", saved_model.getFullPathName().toStdString());
    xml->setAttribute("current_model_index", current_model_index);
    xml->setAttribute ("cab_state", cab_state);
    copyXmlToBinary (*xml, destData););
}

void ProteusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    loadStateInformation 
    ( 
        // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName (treeState.state.getType()))
        {
            treeState.replaceState (juce::ValueTree::fromXml (*xmlState));
            fw_state = xmlState->getBoolAttribute ("fw_state");
            File temp_saved_model = xmlState->getStringAttribute("saved_model");
            saved_model = temp_saved_model;
            cab_state = xmlState->getBoolAttribute ("cab_state");

            current_model_index = xmlState->getIntAttribute("current_model_index");
            File temp = xmlState->getStringAttribute("folder");
            folder = temp;
            if (auto* editor = dynamic_cast<ProteusAudioProcessorEditor*> (getActiveEditor()))
                editor->resetImages();

            if (saved_model.existsAsFile()) {
                loadConfig(saved_model);
            }          

        }
    }
    )
}

void ProteusAudioProcessor::set_ampEQ(float bass_slider, float mid_slider, float treble_slider)
{
    updateEQParameters(bass_slider, mid_slider, treble_slider);
}

void ProteusAudioProcessor::loadConfig(File configFile)
{
    this->suspendProcessing(true);
    pauseVolume = 3;
    String path = configFile.getFullPathName();
    char_filename = path.toUTF8();

    LSTM1.reset();
    LSTM2_1.reset();
    LSTM3.reset();
    LSTM4.reset();


    LSTM1.load_json(char_filename);
    LSTM2_1.load_json(char_filename);
    LSTM3.load_json(char_filename);
    LSTM4.load_json(char_filename);

    if (LSTM1.input_size == 1) {
        conditioned = false;
    }
    else {
        conditioned = true;
    }

    //saved_model = configFile;
    model_loaded = true;
    this->suspendProcessing(false);
    );
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProteusAudioProcessor();
}
