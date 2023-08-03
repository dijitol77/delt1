#pragma once

#include "PluginProcessor.h"
#include "juce_core/juce_core.h"

class UtilityFunctions
{
public:
    UtilityFunctions(ProteusAudioProcessor& p);

    void loadConfig(juce::File configFile);

private:
    ProteusAudioProcessor& processor;
};
