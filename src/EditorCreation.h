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

bool EditorCreation::hasEditor() const
{
    return true; // return true if your plugin has an editor, false otherwise
}

juce::AudioProcessorEditor* EditorCreation::createEditor()
{
    return new ProteusAudioProcessorEditor(processor);
}

