#pragma once
#include "PluginProcessor.h"
#include "PluginEditor.h"
#ifndef AUDIO_PROCESSING_H_INCLUDED
#define AUDIO_PROCESSING_H_INCLUDED

#include <juce_audio_processors/juce_audio_processors.h>

class ProteusAudioProcessor : public juce::AudioProcessor {
public:
    // Constructor, destructor, and other public methods

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;

private:
    // Private member variables and objects
    juce::IIRFilter dcBlocker;
    juce::ResamplingAudioSource resampler;
    juce::LSTM LSTM;
    juce::LSTM LSTM2;
    juce::Convolution cabSimIRa;
    // ... other member variables ...
};

#endif // AUDIO_PROCESSING_H_INCLUDED
