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

ProteusAudioProcessor::ProteusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
    treeState(*this, nullptr, "PARAMETER", { std::make_unique<AudioParameterFloat>(GAIN_ID, GAIN_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),
                        std::make_unique<AudioParameterFloat>(BASS_ID, BASS_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                        std::make_unique<AudioParameterFloat>(MID_ID, MID_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                        std::make_unique<AudioParameterFloat>(TREBLE_ID, TREBLE_NAME, NormalisableRange<float>(-8.0f, 8.0f, 0.01f), 0.0f),
                        std::make_unique<AudioParameterFloat>(MASTER_ID, MASTER_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5) })
#endif
{
    driveParam = treeState.getRawParameterValue (GAIN_ID);
    masterParam = treeState.getRawParameterValue (MASTER_ID);
    bassParam = treeState.getRawParameterValue (BASS_ID);
    midParam = treeState.getRawParameterValue (MID_ID);
    trebleParam = treeState.getRawParameterValue (TREBLE_ID);

    auto bassValue = static_cast<float> (bassParam->load());
    auto midValue = static_cast<float> (midParam->load());
    auto trebleValue = static_cast<float> (trebleParam->load());

    eq4band.setParameters(bassValue, midValue, trebleValue, 0.0);
    eq4band2.setParameters(bassValue, midValue, trebleValue, 0.0);

    pauseVolume = 3;

    cabSimIRa.load(BinaryData::default_ir_wav, BinaryData::default_ir_wavSize);

    PluginProcessorInit processorInit(*this);
    processorInit.initialize();
}

ProteusAudioProcessor::~ProteusAudioProcessor()
{
    // Destructor code here
}
