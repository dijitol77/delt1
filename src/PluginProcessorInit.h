#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "AudioProcessingDerived.h" // Include the header for the derived class

#include "MidiProcessing.h"
#include "Programs.h"
#include "StateManagement.h"
#include "EditorCreation.h"
#include "UtilityFunctions.h"

class PluginProcessorInit {
public:
    PluginProcessorInit(ProteusAudioProcessor& p) : processor(p),
        audioProcessing(static_cast<AudioProcessingDerived&>(p)), // Use the derived class
        midiProcessing(p), programs(p),
        stateManagement(p), editorCreation(p), utilityFunctions(p) {}
    void initialize();

private:
    ProteusAudioProcessor& processor;
    AudioProcessingDerived audioProcessing; // Use the derived class
    MidiProcessing midiProcessing;
    Programs programs;
    StateManagement stateManagement;
    EditorCreation editorCreation;
    UtilityFunctions utilityFunctions;
};
