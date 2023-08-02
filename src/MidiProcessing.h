#pragma once
#include "AudioProcessing.h"
#include "juce_audio_plugin_client/juce_audio_plugin_client.h" // Include this for the JucePlugin_WantsMidiInput, etc.

class ProteusAudioProcessor;

class MidiProcessing {
public:
    bool acceptsMidi() const;
    bool producesMidi() const;
    bool isMidiEffect() const;
};
