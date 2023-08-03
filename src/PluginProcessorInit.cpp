#include "PluginProcessorInit.h"

void PluginProcessorInit::initialize() {
    audioProcessing.initialize();
    midiProcessing.initialize();
    programs.initialize();
    stateManagement.initialize();
    editorCreation.initialize();
    utilityFunctions.initialize();
}

