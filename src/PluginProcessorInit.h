#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"


#include "MidiProcessing.h"
#include "Programs.h"
#include "StateManagement.h"
#include "EditorCreation.h"
#include "UtilityFunctions.h"

class PluginProcessorInit {
public:
    PluginProcessorInit(ProteusAudioProcessor& p) : processor(p),
        audioProcessing(p), // Use the base class
        midiProcessing(p), programs(p),
        stateManagement(p), editorCreation(p), utilityFunctions(p) {}
    void initialize();

private:
    ProteusAudioProcessor& processor;
    MidiProcessing midiProcessing;
    Programs programs;
    StateManagement stateManagement;
    EditorCreation editorCreation;
    UtilityFunctions utilityFunctions;
};
