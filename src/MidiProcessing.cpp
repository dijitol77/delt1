#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MidiProcessing.h"
#include "juce_audio_plugin_client/juce_audio_plugin_client.h" // Include this for the JucePlugin_WantsMidiInput, etc.

bool ProteusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ProteusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ProteusAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}
