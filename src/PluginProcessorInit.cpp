#include "PluginProcessorInit.h"

void PluginProcessorInit::initialize(ProteusAudioProcessor& p) {
    midiProcessing.initialize(p); // Initialize MidiProcessing first
    audioProcessing.initialize(p, midiProcessing); // Pass MidiProcessing to AudioProcessing
    programs.initialize(p);
    stateManagement.initialize(p);
    editorCreation.initialize(p);
    utilityFunctions.initialize(p);
}
