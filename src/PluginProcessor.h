/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <nlohmann/json.hpp>
#include "RTNeuralLSTM.h"
#include "Eq4Band.h"
#include "CabSim.h"

//  MODEL 1

#define GAIN1_ID "drive"
#define GAIN1_NAME "Drive"
#define MASTER1_ID "level"
#define MASTER1_NAME "Level"

//  MODEL 2  

#define GAIN2_ID "drive"
#define GAIN2_NAME "Drive"
// #define MASTER2_ID "level"
// #define MASTER2_NAME "Level" // This seems like a typo. Should it be MASTER2_NAME?

#define BASS_ID "bass"
#define BASS_NAME "Bass"
#define MID_ID "mid"
#define MID_NAME "Mid"
#define TREBLE_ID "treble"
#define TREBLE_NAME "Treble"

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

    // Additional methods
    void set_ampEQ(float bass_slider, float mid_slider, float treble_slider);
     // Files and configuration
    void loadConfig(File configFile1, File configFile2);
    // Files and configuration

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
    Eq4Band eq4band1; // Amp EQ
    Eq4Band eq4band2; // Amp EQ

    std::atomic<float>* driveParam1 = nullptr;
    std::atomic<float>* masterParam = nullptr;
    std::atomic<float>* bassParam = nullptr;
    std::atomic<float>* midParam = nullptr;
    std::atomic<float>* trebleParam = nullptr;

 

    // Parameters for Container 2
    std::atomic<float>* driveParam2 = nullptr;



    
    float previousDriveValue = 0.5;
    float previousMasterValue = 0.5;
    //float steppedValue1 = 0.0;


    // LSTM models
    RT_LSTM LSTM1;
    RT_LSTM LSTM2;
    RT_LSTM LSTM3;
    RT_LSTM LSTM4;

 
    // Other members 
    // ... (e.g., eq4band, eq4band2, cabSimIRa, dcBlocker, resampler, etc.  
    // dcBlocker

    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> dcBlocker;

    // resampler
    chowdsp::ResampledProcess<chowdsp::ResamplingTypes::SRCResampler<>> resampler;

    // IR processing
    CabSim cabSimIRa;

  

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessor)
};
