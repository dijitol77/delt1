#include "EditorCreation.h"
#include "PluginEditor.h"
#include "juce_audio_processors/juce_audio_processors.h" // Include this for the AudioProcessorEditor class

bool EditorCreation::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EditorCreation::createEditor()
{
    return new ProteusAudioProcessorEditor (processor);
}
