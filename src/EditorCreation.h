#pragma once
#include "AudioProcessing.h"
#include "juce_audio_processors/juce_audio_processors.h" // Include this for the AudioProcessorEditor class

class ProteusAudioProcessor;

class EditorCreation {
public:
    bool hasEditor() const;
    juce::AudioProcessorEditor* createEditor();
};
