#include "PluginProcessorInit.h"

void PluginProcessorInit::initialize(ProteusAudioProcessor& p) {
    audioProcessing.initialize(p);
    midiProcessing.initialize(p);
    programs.initialize(p);
    stateManagement.initialize(p);
    editorCreation.initialize(p);
    utilityFunctions.initialize(p);
}
