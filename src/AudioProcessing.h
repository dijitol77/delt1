#pragma once
#include "PluginProcessor.h"
#include "PluginEditor.h"

class ProteusAudioProcessor
{
public:
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages);
};
