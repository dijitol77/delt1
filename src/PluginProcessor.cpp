#include <juce_audio_processors/juce_audio_processors.h> // for AudioBuffer, MidiBuffer
#include <juce_dsp/juce_dsp.h> // for dsp::AudioBlock, dsp::ProcessContextReplacing, ScopedNoDenormals
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginProcessorInit.h"
#include "AudioProcessing.h"
#include "MidiProcessing.h"
#include "Programs.h"
#include "StateManagement.h"
#include "EditorCreation.h"
#include "UtilityFunctions.h"
