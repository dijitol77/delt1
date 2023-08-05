#pragma once
#include "PluginProcessor.h"

class EditorCreation {
public:
    EditorCreation(ProteusAudioProcessor& p) : processor(p) {}
    bool hasEditor() const;
    juce::AudioProcessorEditor* createEditor();

private:
    ProteusAudioProcessor& processor;
};

