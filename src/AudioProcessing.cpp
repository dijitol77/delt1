#include "PluginProcessor.h"
#include "AudioProcessing.h"
#include "juce_dsp/juce_dsp.h" // Include this for the dsp::IIR::Coefficients class

AudioProcessing::AudioProcessing(ProteusAudioProcessor& p, MidiProcessing& m) : processor(p), midiProcessing(m) 

  
void AudioProcessing::initialize()
{
    // Initialize treeState with the parameters of the audio processor
    treeState = processor.treeState;

    // Initialize the parameters with the corresponding parameters from the audio processor
    driveParam = processor.driveParam;
    masterParam = processor.masterParam;
    bassParam = processor.bassParam;
    midParam = processor.midParam;
    trebleParam = processor.trebleParam;

    // Add any other necessary initialization code here
}

void AudioProcessing::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    *processor.dcBlocker.state = *dsp::IIR::Coefficients<float>::makeHighPass (sampleRate, 35.0f);

    // prepare resampler for target sample rate: 44.1 kHz
    constexpr double targetSampleRate = 44100.0;
    processor.resampler.prepareWithTargetSampleRate({ sampleRate, (uint32)samplesPerBlock, 2 }, targetSampleRate);

    dsp::ProcessSpec specMono { sampleRate, static_cast<uint32> (samplesPerBlock), 1 };
    dsp::ProcessSpec spec{ sampleRate, static_cast<uint32> (samplesPerBlock), 2 };

    processor.dcBlocker.prepare (spec); 

    processor.LSTM.reset();
    processor.LSTM2.reset();

    // Set up IR
    processor.cabSimIRa.prepare(spec);
}

void AudioProcessing::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
}

void AudioProcessing::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    midiProcessing.processMidi(midiMessages);

    auto driveValue = static_cast<float> (this->driveParam->load());
    auto masterValue = static_cast<float> (this->masterParam->load());
    auto bassValue = static_cast<float> (this->bassParam->load());
    auto midValue = static_cast<float> (this->midParam->load());
    auto trebleValue = static_cast<float> (this->trebleParam->load());

    // Setup Audio Data
    const int numSamples = buffer.getNumSamples();
    const int numInputChannels = processor.getTotalNumInputChannels();
    const int sampleRate = processor.getSampleRate();

    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);

    // Overdrive Pedal ================================================================== 
    if (processor.fw_state == 1 && processor.model_loaded == true) {
        
        if (processor.conditioned == false) {
            // Apply ramped changes for gain smoothing
            if (driveValue == processor.previousDriveValue)
            {
                buffer.applyGain(driveValue*2.5);
            }
             else {
                buffer.applyGainRamp(0, (int) buffer.getNumSamples(), processor.previousDriveValue * 2.5, driveValue * 2.5);
                processor.previousDriveValue = driveValue;
            }
            auto block44k = processor.resampler.processIn(block);
            for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
            {
                // Apply LSTM model
                if (ch == 0) {
                    processor.LSTM.process(block44k.getChannelPointer(0), block44k.getChannelPointer(0), (int)block44k.getNumSamples());
                }
                else if (ch == 1) {
                    processor.LSTM2.process(block44k.getChannelPointer(1), block44k.getChannelPointer(1), (int)block44k.getNumSamples());
                }
            }
            processor.resampler.processOut(block44k, block);
        } else {
            buffer.applyGain(1.5); // Apply default boost to help sound
            // resample to target sample rate
            
            auto block44k = processor.resampler.processIn(block);
            for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
            {
                // Apply LSTM model
                if (ch == 0) {
                    processor.LSTM.process(block44k.getChannelPointer(0), driveValue, block44k.getChannelPointer(0), (int)block44k.getNumSamples());
                }
                else if (ch == 1) {
                    processor.LSTM2.process(block44k.getChannelPointer(1), driveValue, block44k.getChannelPointer(1), (int)block44k.getNumSamples());
                }
            }
            processor.resampler.processOut(block44k, block);
        }

        processor.dcBlocker.process(context);

        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        {
            // Apply EQ
            if (ch == 0) {
                processor.eq4band.process(buffer.getReadPointer(0), buffer.getWritePointer(0), midiMessages, numSamples, numInputChannels, sampleRate);
            
            }
            else if (ch == 1) {
                processor.eq4band2.process(buffer.getReadPointer(1), buffer.getWritePointer(1), midiMessages, numSamples, numInputChannels, sampleRate);
            }
        }

        if (processor.cab_state == 1) {
            processor.cabSimIRa.process(context); // Process IR a on channel 0
            buffer.applyGain(2.0);
        //} else {
        //    buffer.applyGain(0.7);
        }

        // Master Volume 
        // Apply ramped changes for gain smoothing
        if (masterValue == processor.previousMasterValue)
        {
            buffer.applyGain(masterValue);
        }
        else {
            buffer.applyGainRamp(0, (int) buffer.getNumSamples(), processor.previousMasterValue, masterValue);
            processor.previousMasterValue = masterValue;
        }

        // Smooth pop sound when changing models
        if (processor.pauseVolume > 0) {
            if (processor.pauseVolume > 2)
                buffer.applyGain(0.0);
            else if (processor.pauseVolume == 2)
                buffer.applyGainRamp(0, (int)buffer.getNumSamples(), 0, masterValue / 2);
            else
                buffer.applyGainRamp(0, (int)buffer.getNumSamples(), masterValue / 2, masterValue);
            processor.pauseVolume -= 1;
        }
    }
}
