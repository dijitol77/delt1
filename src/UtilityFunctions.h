#pragma once
#include "AudioProcessing.h"
#include "juce_core/juce_core.h" // Include this for the File class

class ProteusAudioProcessor;

class UtilityFunctions {
public:
    void loadConfig(juce::File configFile);
};
