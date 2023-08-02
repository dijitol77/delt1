#include <juce_audio_processors/juce_audio_processors.h> // for AudioBuffer, MidiBuffer
#include <juce_dsp/juce_dsp.h> // for dsp::AudioBlock, dsp::ProcessContextReplacing, ScopedNoDenormals
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginProcessorInit.cpp"
#include "AudioProcessing.cpp"
#include "MidiProcessing.cpp"
#include "Programs.cpp"
#include "StateManagement.cpp"
#include "EditorCreation.cpp"
#include "UtilityFunctions.cpp"
