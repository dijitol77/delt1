##pragma once
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "RTNeuralLSTM.h" // Include this for RT_LSTM

#ifndef AUDIO_PROCESSING_H_INCLUDED
#define AUDIO_PROCESSING_H_INCLUDED

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h> // Include this for dsp related classes

class ProteusAudioProcessor : public juce::AudioProcessor {
public:
    // Constructor, destructor, and other public methods

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;
    int getTotalNumInputChannels();
    double getSampleRate();
    void load();

    // Member variables
    float driveParam, masterParam, bassParam, midParam, trebleParam;
    bool fw_state, model_loaded, conditioned, cab_state;
    float previousDriveValue, previousMasterValue, pauseVolume;
    juce::dsp::IIR::Filter<float> eq4band, eq4band2;

private:
    // Private member variables and objects
    juce::IIRFilter dcBlocker;
    juce::ResamplingAudioSource resampler;
    RT_LSTM LSTM; // Using RT_LSTM from RTNeuralLSTM.h
    RT_LSTM LSTM2; // Using RT_LSTM from RTNeuralLSTM.h
    juce::dsp::Convolution cabSimIRa; // Using dsp::Convolution from juce_dsp namespace
    juce::AudioBuffer<float> buffer;
    juce::MidiBuffer midiMessages;
    juce::dsp::AudioBlock<float> block;
    juce::dsp::ProcessContextReplacing<float> context;
    juce::AudioBuffer<float> block44k;
    // ... other member variables ...
};

#endif // AUDIO_PROCESSING_H_INCLUDED
