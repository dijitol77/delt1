/*
1. HEADER AND INCLUDES
   ==============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin processor.
   ==============================================================================
*/

#pragma once

#include "RTNeuralLSTM.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "StateManagement.h" // Include the StateManagement header

ProteusAudioProcessor::ProteusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
    treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    // Initialize any other required variables or states
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
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
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
    // Prepare to play code here
}

void ProteusAudioProcessor::releaseResources()
{
    // Release resources code here
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ProteusAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

#if !JucePlugin_IsSynth
    // This checks if the input layout matches the output layout
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void ProteusAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    // Process block code here
}

bool ProteusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ProteusAudioProcessor::createEditor()
{
    return new ProteusAudioProcessorEditor(*this, treeState);
}

void ProteusAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    // Your preset save code here
    stateManagement.getStateInformation(destData, treeState, fw_state, folder, saved_model, current_model_index, cab_state);
}

void ProteusAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // Your preset load code here
    stateManagement.setStateInformation(data, sizeInBytes, treeState, fw_state, folder, saved_model, current_model_index, cab_state, dynamic_cast<ProteusAudioProcessorEditor*>(getActiveEditor()));
}

void ProteusAudioProcessor::set_ampEQ(float bass_slider, float mid_slider, float treble_slider)
{
    stateManagement.set_ampEQ(bass_slider, mid_slider, treble_slider, eq4band, eq4band2);
}

void ProteusAudioProcessor::loadConfig(File configFile)
{
    stateManagement.loadConfig(configFile, conditioned, model_loaded, nullptr, pauseVolume, LSTM, LSTM2, char_filename);
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ProteusAudioProcessor();
}
