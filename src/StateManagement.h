#pragma once
#include "AudioProcessing.h"
#include "juce_core/juce_core.h" // Include this for the MemoryBlock class

class ProteusAudioProcessor;

class StateManagement {
public:
    StateManagement(ProteusAudioProcessor& p) : processor(p) {}
    void getStateInformation (juce::MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

private:
    ProteusAudioProcessor& processor;
};
