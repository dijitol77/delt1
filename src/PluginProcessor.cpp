#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProteusAudioProcessor::ProteusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations  // Start of #ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect  // Start of #if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth  // Start of #if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif  // End of #if ! JucePlugin_IsSynth
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif  // End of #if ! JucePlugin_IsMidiEffect
    ),
    treeState(*this, nullptr, "PARAMETER", { std::make_unique<AudioParameterFloat>(GAIN_ID, GAIN_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),
                       std::make_unique<AudioParameterFloat>(MASTER_ID, MASTER_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5) })
#endif  // End of #ifndef JucePlugin_PreferredChannelConfigurations
{
    driveParam = treeState.getRawParameterValue(GAIN_ID);
    masterParam = treeState.getRawParameterValue(MASTER_ID);
    pauseVolume = 3;
}


ProteusAudioProcessor::~ProteusAudioProcessor()
{
}

const String ProteusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ProteusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ProteusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ProteusAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ProteusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ProteusAudioProcessor::getNumPrograms()
{
    return 1;
}

int ProteusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ProteusAudioProcessor::setCurrentProgram(int index)
{
}

const String ProteusAudioProcessor::getProgramName(int index)
{
    return {};
}

void ProteusAudioProcessor::changeProgramName(int index, const String& newName)
{
}

void ProteusAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    *dcBlocker.state = *dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 35.0f);
    constexpr double targetSampleRate = 44100.0;
    resampler.prepareWithTargetSampleRate({ sampleRate, (uint32)samplesPerBlock, 2 }, targetSampleRate);
    dsp::ProcessSpec specMono { sampleRate, static_cast<uint32>(samplesPerBlock), 1 };
    dsp::ProcessSpec spec{ sampleRate, static_cast<uint32>(samplesPerBlock), 2 };
    dcBlocker.prepare(spec);
    LSTM.reset();
    LSTM2.reset();
}

void ProteusAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ProteusAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif
    return true;
  #endif
}

void ProteusAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto driveValue = static_cast<float>(driveParam->load());
    auto masterValue = static_cast<float>(masterParam->load());
    const int numSamples = buffer.getNumSamples();
    const int numInputChannels = getTotalNumInputChannels();
    const int sampleRate = getSampleRate();
    dsp::AudioBlock<float> block(buffer);
    dsp::ProcessContextReplacing<float> context(block);

    // (Your existing processing code here)

    // Master Volume 
    if (masterValue == previousMasterValue)
    {
        buffer.applyGain(masterValue);
    }
    else {
        buffer.applyGainRamp(0, numSamples, previousMasterValue, masterValue);
        previousMasterValue = masterValue;
    }
}

bool ProteusAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* ProteusAudioProcessor::createEditor()
{
    return new ProteusAudioProcessorEditor(*this);
}

void ProteusAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    auto state = treeState.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void ProteusAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(treeState.state.getType()))
        {
            treeState.replaceState(juce::ValueTree::fromXml(*xmlState));
        }
    }
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProteusAudioProcessor();
}
