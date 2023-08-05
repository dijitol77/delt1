#include "EditorCreation.h"
#include "PluginEditor.h"
#include "juce_audio_processors/juce_audio_processors.h" // Include this for the AudioProcessorEditor class

bool EditorCreation::hasEditor() const
{
    return true; // return true if your plugin has an editor, false otherwise
}

juce::AudioProcessorEditor* EditorCreation::createEditor()
{
    return new ProteusAudioProcessorEditor(processor);
}

