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
    // Implement this method to return whether your plugin has an editor.
}

juce::AudioProcessorEditor* EditorCreation::createEditor()
{
    return new ProteusAudioProcessorEditor(processor);
}

