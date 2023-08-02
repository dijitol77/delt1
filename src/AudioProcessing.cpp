#include "PluginProcessor.h"

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

    LSTM.reset();
    LSTM2.reset();

    // Set up IR
    cabSimIRa.prepare(spec);

}

void ProteusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

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
    eq4band.setParameters(bass_slider, mid_slider, treble_slider, 0.0f);
    eq4band2.setParameters(bass_slider, mid_slider, treble_slider, 0.0f);
}

void ProteusAudioProcessor::loadConfig(File configFile)
{
    this->suspendProcessing(true);
    pauseVolume = 3;
    String path = configFile.getFullPathName();
    char_filename = path.toUTF8();

    LSTM.reset();
    LSTM2.reset();

    LSTM.load_json(char_filename);
    LSTM2.load_json(char_filename);

    if (LSTM.input_size == 1) {
        conditioned = false;
    } else {
        conditioned = true;
    }

    //saved_model = configFile;
    model_loaded = true;
    this->suspendProcessing(false);
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProteusAudioProcessor();
}
