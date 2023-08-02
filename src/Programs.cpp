#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Programs.h"
#include "juce_core/juce_core.h" // Include this for the String class

int ProteusAudioProcessor::getNumPrograms()
{
    return 1;
}

int ProteusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ProteusAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ProteusAudioProcessor::getProgramName (int index)
{
    return {};
}

void ProteusAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}
