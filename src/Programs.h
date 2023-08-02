#pragma once
#include "AudioProcessing.h"
#include "juce_core/juce_core.h" // Include this for the String class

class ProteusAudioProcessor;

class Programs {
public:
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const juce::String getProgramName (int index);
    void changeProgramName (int index, const juce::String& newName);
};
