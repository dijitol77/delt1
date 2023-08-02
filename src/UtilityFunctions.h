#pragma once
#include "PluginProcessor.h"
#include "juce_core/juce_core.h" // Include this for the File class

void loadConfig(ProteusAudioProcessor& processor, juce::File configFile);

class ProteusAudioProcessor;

class UtilityFunctions {
public:
    void loadConfig(juce::File configFile);
};
