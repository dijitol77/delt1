#include "PluginProcessor.h"
#include "PluginEditor.h"

bool ProteusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ProteusAudioProcessor::createEditor()
{
    return new ProteusAudioProcessorEditor (*this);
}
