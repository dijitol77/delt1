#pragma once

#include "juce_core/juce_core.h" // Include only the required header for juce::File

class ProteusAudioProcessor; // Forward declaration

class UtilityFunctions
{
public:
    UtilityFunctions(ProteusAudioProcessor& p); // Constructor
    void loadConfig(juce::File configFile);

private:
    ProteusAudioProcessor& processor;
};
