/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


#define GAIN1_ID "drive"
#define GAIN1_NAME "Drive"
#define MASTER1_ID "level"
#define MASTER1_NAME "Level"
#define BASS1_ID "bass"
#define BASS1_NAME "Bass"
#define MID1_ID "mid"
#define MID1_NAME "Mid"
#define TREBLE1_ID "treble"
#define TREBLE1_NAME "Treble"


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
    ~ProteusAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void set_ampEQ1(float bass_slider1, float mid_slider1, float treble_slider1);

    // Files and configuration
    void loadConfig(File configFile);

    // Pedal/amp states
    int fw_state = 1;       // 0 = off, 1 = on
    int cab_state = 1; // 0 = off, 1 = on

    File currentDirectory = File::getCurrentWorkingDirectory().getFullPathName();
    int current_model_index = 0;

    Array<File> fileArray;
    std::vector<File> jsonFiles;
    int num_models = 0;
    File folder = File::getSpecialLocation(File::userDesktopDirectory);
    File saved_model;

    AudioProcessorValueTreeState treeState;

    bool conditioned = false;

    const char* char_filename = "";

    int pauseVolume = 3;

    bool model_loaded = false;

private:

// Renamed variables for Container 1

    std::atomic<float>* driveParam1 = nullptr;
    std::atomic<float>* masterParam1 = nullptr;
    std::atomic<float>* bassParam1 = nullptr;
    std::atomic<float>* midParam1 = nullptr;
    std::atomic<float>* trebleParam1 = nullptr;

    float previousDriveValue = 0.5;
    float previousMasterValue = 0.5;
    //float steppedValue1 = 0.0;

// Renamed LSTM for Container 1

    RT_LSTM LSTM1;
    RT_LSTM LSTM2_1;
    RT_LSTM LSTM3;
    RT_LSTM LSTM4;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> dcBlocker;

    chowdsp::ResampledProcess<chowdsp::ResamplingTypes::SRCResampler<>> resampler;

    // IR processing
    CabSim cabSimIRa;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessor)
};
