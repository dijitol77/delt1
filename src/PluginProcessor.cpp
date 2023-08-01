#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProteusAudioProcessor::ProteusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Initialize parameters
    parameters.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>("ampBass", "Amp Bass", 0.0f, 1.0f, 0.5f));
    parameters.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>("ampMid", "Amp Mid", 0.0f, 1.0f, 0.5f));
    parameters.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>("ampTreble", "Amp Treble", 0.0f, 1.0f, 0.5f));
    parameters.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>("odDrive", "OD Drive", 0.0f, 1.0f, 0.5f));

    // Initialize models
    jsonFiles = juce::Array<juce::File>();
    loadModels();

    // Initialize state
    treeState = new juce::AudioProcessorValueTreeState(*this, nullptr, "PARAMETERS", parameters);
}

ProteusAudioProcessor::~ProteusAudioProcessor()
{
    odDriveKnob.setLookAndFeel(nullptr);
    odLevelKnob.setLookAndFeel(nullptr);
    ampBassKnob.setLookAndFeel(nullptr);
    ampMidKnob.setLookAndFeel(nullptr);
    ampTrebleKnob.setLookAndFeel(nullptr);
}

//==============================================================================
void ProteusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Prepare the models for playing audio
    // This might involve setting the sample rate and block size for the models
    for (auto& model : models)
    {
        model.prepareToPlay(sampleRate, samplesPerBlock);
    }
}

void ProteusAudioProcessor::releaseResources()
{
    // Release any resources used by the models
    for (auto& model : models)
    {
        model.releaseResources();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ProteusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Check if the bus layout is supported by the models
    for (const auto& model : models)
    {
        if (!model.isBusesLayoutSupported(layouts))
        {
            return false;
        }
    }
    return true;
}
#endif
}

void ProteusAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // Process the audio block using the currently selected model
    if (currentModel >= 0 && currentModel < models.size())
    {
        models[currentModel].processBlock(buffer, midiMessages);
    }
}

//==============================================================================
bool ProteusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ProteusAudioProcessor::createEditor()
{
    return new ProteusAudioProcessorEditor (*this);
}

//==============================================================================
void ProteusAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
void ProteusAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Get the state of the currently selected model
    if (currentModel >= 0 && currentModel < models.size())
    {
        models[currentModel].getStateInformation(destData);
    }
}

void ProteusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Set the state of the currently selected model
    if (currentModel >= 0 && currentModel < models.size())
    {
        models[currentModel].setStateInformation(data, sizeInBytes);
    }
    repaint();
}

//==============================================================================
void ProteusAudioProcessor::loadModels()
{
    // Load the models from the JSON files
    // This might involve parsing the JSON files and creating model objects based on the parsed data
    for (const auto& jsonFile : jsonFiles)
    {
        models.push_back(Model(jsonFile));
    }
}

void ProteusAudioProcessor::loadModel(int index)
{
    // Set the current model based on the index
    if (index >= 0 && index < models.size())
    {
        currentModel = index;
    }
}

void ProteusAudioProcessor::loadNewModel(int index)
{
    // Load a new model based on the index
    // This might involve creating a new model object and adding it to the models array
    if (index >= 0 && index < jsonFiles.size())
    {
        models.push_back(Model(jsonFiles[index]));
        currentModel = models.size() - 1;
    }
}

// ... (Implement other listener methods)

bool isValidFormat(const juce::File& file)
{
    return file.hasFileExtension(".json");
}
