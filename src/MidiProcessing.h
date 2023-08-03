#pragma once
#include "PluginProcessor.h"

class MidiProcessing {
public:
    MidiProcessing(ProteusAudioProcessor& p) : processor(p) {}
    void processMidi(juce::MidiBuffer& midiMessages);

private:
    ProteusAudioProcessor& processor;
};
