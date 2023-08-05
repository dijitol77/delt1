#pragma once

// Forward declaration of ProteusAudioProcessor
class ProteusAudioProcessor;

#include "PluginProcessor.h"
#include <JuceHeader.h>

class StateManagement
{
public:
    StateManagement(ProteusAudioProcessor& p) : processor(p) {}
    void getStateInformation(juce::MemoryBlock& destData);
    void setStateInformation(const void* data, int sizeInBytes);
private:
    ProteusAudioProcessor& processor;
};
