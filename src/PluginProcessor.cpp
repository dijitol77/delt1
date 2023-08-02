#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginProcessorInit.cpp"
#include "AudioProcessing.cpp"
#include "MidiProcessing.cpp"
#include "Programs.cpp"
#include "StateManagement.cpp"
#include "EditorCreation.cpp"
#include "UtilityFunctions.cpp"

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProteusAudioProcessor();
}
