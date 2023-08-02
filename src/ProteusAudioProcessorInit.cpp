#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "juce_audio_processors/juce_audio_processors.h" // Include this for the AudioParameterFloat class

//==============================================================================
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

}

ProteusAudioProcessor::~ProteusAudioProcessor()
{
}

//==============================================================================
const String ProteusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

double ProteusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

//==============================================================================


#ifndef JucePlugin_PreferredChannelConfigurations
bool ProteusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif
