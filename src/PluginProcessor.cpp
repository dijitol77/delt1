
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
                                            std::make_unique<AudioParameterFloat>(BASS_ID, BASS_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                                            std::make_unique<AudioParameterFloat>(MID_ID, MID_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                                            std::make_unique<AudioParameterFloat>(TREBLE_ID, TREBL1_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                                            std::make_unique<AudioParameterFloat>(MASTER_ID, MASTER_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5),
                                            std::make_unique<AudioParameterFloat>(GAIN2_ID, GAIN2_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),

                            
                                })
#endif
{
    // Initialize parameters for Container 1
    driveParam1 = treeState.getRawParameterValue(GAIN1_ID);
    masterParam1 = treeState.getRawParameterValue(MASTER_ID);
    bassParam1 = treeState.getRawParameterValue(BASS_ID);
    midParam1 = treeState.getRawParameterValue(MID_ID);
    trebleParam1 = treeState.getRawParameterValue(TREBLE_ID);

    // Load parameter values for Container 1
    auto bassValue1 = static_cast<float>(bassParam1->load());
    auto midValue1 = static_cast<float>(midParam1->load());
    auto trebleValue1 = static_cast<float>(trebleParam1->load());


    // Load parameter values for Container 1 and update EQ bands
    driveParam2 = treeState.getRawParameterValue(GAIN2_ID);

    

    // Update EQ band parameters for Container 1
    eq4band1.setParameters(bassValue1, midValue1, trebleValue1, 0.0);
    eq4band2.setParameters(bassValue1, midValue1, trebleValue1, 0.0);

    pauseVolume = 3;

    cabSimIRa.load(BinaryData::default_ir_wav, BinaryData::default_ir_wavSize);

}

ProteusAudioProcessor::~ProteusAudioProcessor()
{
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

void ProteusAudioProcessor::setCurrentProgram (int index)
{
}

const String ProteusAudioProcessor::getProgramName (int index)
{
    return {};
}

void ProteusAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ProteusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    *dcBlocker.state = *dsp::IIR::Coefficients<float>::makeHighPass (sampleRate, 35.0f);

    // prepare resampler for target sample rate: 44.1 kHz
    constexpr double targetSampleRate = 44100.0;
    //resampler.prepareWithTargetSampleRate ({ sampleRate, (uint32) samplesPerBlock, 1 }, targetSampleRate);
    resampler.prepareWithTargetSampleRate({ sampleRate, (uint32)samplesPerBlock, 2 }, targetSampleRate);


    dsp::ProcessSpec specMono { sampleRate, static_cast<uint32> (samplesPerBlock), 1 };
    dsp::ProcessSpec spec{ sampleRate, static_cast<uint32> (samplesPerBlock), 2 };

    dcBlocker.prepare (spec); 

    LSTM1.reset();
    LSTM2.reset();
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
#endif


void ProteusAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;

    // Load parameter values for Container 1

    // Load parameter values for Container 2
    auto driveValue1 = static_cast<float> (driveParam1->load());
    auto masterValue1 = static_cast<float> (masterParam1->load());
    auto bassValue1 = static_cast<float> (bassParam1->load());
    auto midValue1 = static_cast<float> (midParam1->load());
    auto trebleValue1 = static_cast<float> (trebleParam1->load());

    // Load parameter values for Container 2
    auto driveValue2 = static_cast<float> (driveParam2->load());
    


    // Setup Audio Data
    const int numSamples = buffer.getNumSamples();
    const int numInputChannels = getTotalNumInputChannels();
    const int sampleRate = getSampleRate();

    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);

    // Container 1 Processing
    if (fw_state == 1 && model_loaded == true) {
        // ... [Your existing code for Container 1]
         if (conditioned == false) {
        // Apply ramped changes for gain smoothing
        if (driveValue == previousDriveValue) {
            buffer.applyGain(driveValue*2.5);
        } else {
            buffer.applyGainRamp(0, (int) buffer.getNumSamples(), previousDriveValue * 2.5, driveValue * 2.5);
            previousDriveValue = driveValue;
        }
        
        for (int ch = 0; ch < buffer.getNumChannels(); ++ch) {
            // Apply LSTM model
            if (ch == 0) {
                LSTM1.process(buffer.getReadPointer(0), buffer.getWritePointer(0), (int)buffer.getNumSamples());
            } else if (ch == 1) {
                LSTM2.process(buffer.getReadPointer(1), buffer.getWritePointer(1), (int)buffer.getNumSamples());
            }
        }
    } else {
        buffer.applyGain(1.5); // Apply default boost to help sound
        
        for (int ch = 0; ch < buffer.getNumChannels(); ++ch) {
            // Apply LSTM model
            if (ch == 0) {
                LSTM1.process(buffer.getReadPointer(0), driveValue, buffer.getWritePointer(0), (int)buffer.getNumSamples());
            } else if (ch == 1) {
                LSTM2.process(buffer.getReadPointer(1), driveValue, buffer.getWritePointer(1), (int)buffer.getNumSamples());
            }
            resampler.processOut(block44k, block);
        }
    }

    // Load parameter values for Container 2
    auto driveValue2 = static_cast<float> (driveParam2->load());

    // Container 2 Processing
    if (fw_state == 1 && model_loaded == true) {
        // ... [Your existing code for Container 2]
    if (conditioned == false) {
        // Apply ramped changes for gain smoothing
        if (driveValue == previousDriveValue) {
            buffer.applyGain(driveValue*2.5);
        } else {
            buffer.applyGainRamp(0, (int) buffer.getNumSamples(), previousDriveValue * 2.5, driveValue * 2.5);
            previousDriveValue = driveValue;
        }
        
        for (int ch = 0; ch < buffer.getNumChannels(); ++ch) {
            // Apply LSTM model
            if (ch == 0) {
                LSTM3.process(buffer.getReadPointer(0), buffer.getWritePointer(0), (int)buffer.getNumSamples());
            } else if (ch == 1) {
                LSTM4.process(buffer.getReadPointer(1), buffer.getWritePointer(1), (int)buffer.getNumSamples());
            }
        }
    } else {
        buffer.applyGain(1.5); // Apply default boost to help sound
        
        for (int ch = 0; ch < buffer.getNumChannels(); ++ch) {
            // Apply LSTM model
            if (ch == 0) {
                LSTM3.process(buffer.getReadPointer(0), driveValue, buffer.getWritePointer(0), (int)buffer.getNumSamples());
            } else if (ch == 1) {
                LSTM4.process(buffer.getReadPointer(1), driveValue, buffer.getWritePointer(1), (int)buffer.getNumSamples());
            }
            resampler.processOut(block44k, block);
        }
    }

    dcBlocker.process(context);
}


    // EQ Adjustments (applied after both Container 1 and Container 2 processing)
    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
        // Apply EQ
        if (ch == 0) {
            eq4band1.process(buffer.getReadPointer(0), buffer.getWritePointer(0), midiMessages, numSamples, numInputChannels, sampleRate);
        }
        else if (ch == 1) {
            eq4band2.process(buffer.getReadPointer(1), buffer.getWritePointer(1), midiMessages, numSamples, numInputChannels, sampleRate);
        }
    }

    // Impulse Response Application (if cabinet simulation is enabled)
    if (cab_state == 1) {
        dsp::AudioBlock<float> block(buffer);
        dsp::ProcessContextReplacing<float> context(block);
        cabSimIRa.process(context);
    }

    // Master Volume Adjustment
    auto masterValue = static_cast<float> (masterParam1->load());
    if (masterValue != previousMasterValue)
    {
        buffer.applyGainRamp(0, buffer.getNumSamples(), previousMasterValue, masterValue);
        previousMasterValue = masterValue;
    }
    else {
        buffer.applyGain(masterValue);
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

//==============================================================================
bool ProteusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ProteusAudioProcessor::createEditor()
{
    return new ProteusAudioProcessorEditor (*this);
}

//==============================================================================
void ProteusAudioProcessor::getStateInformation (MemoryBlock& destData)
{
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
    copyXmlToBinary (*xml, destData);

}

void ProteusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
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
    
}

void ProteusAudioProcessor::set_ampEQ(float bass_slider, float mid_slider, float treble_slider)
{
    eq4band1.setParameters(bass_slider, mid_slider, treble_slider, 0.0f);
    eq4band2.setParameters(bass_slider, mid_slider, treble_slider, 0.0f);
}

void ProteusAudioProcessor::loadConfig(File configFile1, File configFile2) {

    this->suspendProcessing(true);
    pauseVolume = 3;
    String path = configFile.getFullPathName();
    char_filename = path.toUTF8();

    // Load model for Container 1 (LSTM1 and LSTM2)
    String path1 = configFile1.getFullPathName();
    char_filename1 = path1.toUTF8();
    try {
        RT_LSTM model1;
        model1.load_json(char_filename1);
        LSTM1 = model1;
        LSTM2 = model1;
    } catch (const std::exception& e) {
        model_loaded = false;
        std::cerr << "Error loading LSTM model for Container 1: " << e.what() << std::endl;
    }

    // Load model for Container 2 (LSTM3 and LSTM4)
    String path2 = configFile2.getFullPathName();
    char_filename2 = path2.toUTF8();
    try {
        RT_LSTM model2;
        model2.load_json(char_filename2);
        LSTM3 = model2;
        LSTM4 = model2;
    } catch (const std::exception& e) {
        // Handle any exceptions that might occur during loading
        // This could be due to a malformed file, incorrect path, etc.
        model_loaded = false;
        std::cerr << "Error loading LSTM model for Container 2: " << e.what() << std::endl;
    }

    //saved_model = configFile;
    model_loaded = true;
    this->suspendProcessing(false);

}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new ProteusAudioProcessor();
}
