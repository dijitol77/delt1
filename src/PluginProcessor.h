/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "RTNeuralLSTM.h"

#define GAIN_ID "drive"
#define GAIN_NAME "Drive"
#define MASTER_ID "level"
#define MASTER_NAME "Level"
#define BASS_ID "bass"
#define BASS_NAME "Bass"
#define MID_ID "mid"
#define MID_NAME "Mid"
#define TREBLE_ID "treble"
#define TREBLE_NAME "Treble"

#include <nlohmann/json.hpp>
#include "RTNeuralLSTM.h"
#include "Eq4Band.h"
#include "CabSim.h"

//==============================================================================
/**
*/
class ProteusAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    ProteusAudioProcessor();
    ~ProteusAudioProcessor() override;

    //==============================================================================
    void loadConfig2();
    void loadConfig3();
    void loadConfig4();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void processBlockBypassed (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void processBlockRealtime (juce::AudioBuffer<float>&, juce::MidiBuffer&);

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:

    Eq4Band eq4band; // Amp EQ
    Eq4Band eq4band2; // Amp EQ
// Remove these lines
    // std::atomic<float>* driveParam = nullptr;
    // std::atomic<float>* masterParam = nullptr;
    // std::atomic<float>* bassParam = nullptr;
    // std::atomic<float>* midParam = nullptr;
    // std::atomic<float>* trebleParam = nullptr;

    juce::AudioProcessorValueTreeState treeState;
    juce::AudioParameterFloat* driveParam;
    juce::AudioParameterFloat* masterParam;
    juce::AudioParameterFloat* bassParam;
    juce::AudioParameterFloat* midParam;
    juce::AudioParameterFloat* trebleParam;
    float previousDriveValue = 0.5f;
    float previousMasterValue = 0.5f;

    RT_LSTM LSTM;
    RT_LSTM LSTM2;

    // Add these declarations here
    RT_LSTM LSTM3;
    RT_LSTM LSTM4;

    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> dcBlocker;

    chowdsp::ResampledProcess<chowdsp::ResamplingTypes::SRCResampler<>> resampler;

    // IR processing
    CabSim cabSimIRa;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessor)
};
class ProteusAudioProcessor  : public juce::AudioProcessor
{
public:
    // ...
    std::vector<File> jsonFiles; // This is just an example, replace with the actual type
    int num_models;
    int saved_model;
    void loadConfig();
    bool cab_state;
    void set_ampEQ();
    // ...
};
class ProteusAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    // ...
    void buttonClicked2();
    void loadButtonClicked();
    void cabOnButtonClicked();
    void modelSelectChanged2()
    // ...
    juce::TextButton loadButton2;
    juce::TextButton cabOnButton;
    ProteusAudioProcessor& processor;
    // ...
};
