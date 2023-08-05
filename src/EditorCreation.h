#pragma once

class EditorCreation {
public:
    EditorCreation(ProteusAudioProcessor& p) : processor(p) {}
    bool hasEditor() const;
    juce::AudioProcessorEditor* createEditor();

private:
    ProteusAudioProcessor& processor;
};

