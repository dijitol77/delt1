#include "MidiProcessing.h"
#include "PluginProcessor.h"
#include "juce_audio_plugin_client/juce_audio_plugin_client.h" // Include this for the JucePlugin_WantsMidiInput, etc.

void MidiProcessing::processMidi(juce::MidiBuffer& midiMessages)
{
    // Use processor to access necessary member variables and functions
    // For example:
    // processor.someMemberVariable = someValue;
    // processor.someMemberFunction(someArgument);
}

bool MidiProcessing::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiProcessing::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiProcessing::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}
