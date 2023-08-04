#include "Programs.h"

Programs::Programs(ProteusAudioProcessor& p) : processor(p) {}

void Programs::initialize(ProteusAudioProcessor& p)
{
    // Initialization code goes here
}

int Programs::getNumPrograms()
{
    return 1;
}

int Programs::getCurrentProgram()
{
    return 0;
}

void Programs::setCurrentProgram (int index)
{
    // Code to set current program goes here
}

const juce::String Programs::getProgramName (int index)
{
    return {};
}

void Programs::changeProgramName (int index, const juce::String& newName)
{
    // Code to change program name goes here
}




void Programs::changeProgramName (int index, const juce::String& newName)
{
}
