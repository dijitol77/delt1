#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "AudioProcessing.h"
#include "MidiProcessing.h"
#include "Programs.h"
#include "StateManagement.h"
#include "EditorCreation.h"
#include "UtilityFunctions.h"

class PluginProcessorInit {
public:
    PluginProcessorInit(ProteusAudioProcessor& p) : processor(p),
        audioProcessing(static_cast<AudioProcessing&>(p)), // Fix the constructor argument type
        midiProcessing(p), programs(p), 
        stateManagement(p), editorCreation(p), utilityFunctions(p) {}
    void initialize();

private:
    ProteusAudioProcessor& processor;
    AudioProcessing audioProcessing;
    MidiProcessing midiProcessing;
    Programs programs;
    StateManagement stateManagement;
    EditorCreation editorCreation;
    UtilityFunctions utilityFunctions;
};
