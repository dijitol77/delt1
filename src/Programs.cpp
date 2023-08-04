#include "Programs.h"

// Constructor: Initialize the processor member variable
Programs::Programs(ProteusAudioProcessor& p) : processor(p) {}

// Initialize method: Add any necessary initialization code here
void Programs::initialize(ProteusAudioProcessor& p)
{
    // Initialization code goes here
}

// Get the number of programs
int Programs::getNumPrograms()
{
    return 1;
}

// Get the current program
int Programs::getCurrentProgram()
{
    return 0;
}

// Set the current program: Add code to set the current program here
void Programs::setCurrentProgram (int index)
{
    // Code to set current program goes here
}

// Get the name of a program
const juce::String Programs::getProgramName (int index)
{
    return {};
}

// Change the name of a program: Add code to change the name of a program here
void Programs::changeProgramName (int index, const juce::String& newName)
{
    // Code to change program name goes here
}
