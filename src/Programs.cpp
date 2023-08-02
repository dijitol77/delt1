#include "PluginProcessor.h"

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

const String ProteusAudioProcessor::getProgramName (int index)
{
    return {};
}

void ProteusAudioProcessor::changeProgramName (int index, const String& newName)
{
}
