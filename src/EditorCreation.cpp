#include "PluginProcessor.h"
#include "PluginEditor.h"

bool ProteusAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* ProteusAudioProcessor::createEditor()
{
    return new ProteusAudioProcessorEditor (*this);
}
