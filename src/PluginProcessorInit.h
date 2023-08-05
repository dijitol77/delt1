#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "AudioProcessing.h"
#include "MidiProcessing.h"
#include "Programs.h"
#include "EditorCreation.h"
#include "UtilityFunctions.h"
#include "AudioProcessing.h"
#include "CabSim.h"
#include "RTNeuralLSTM.h"
#include "Eq4Band.h"
#include "StateManagement.h"

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
