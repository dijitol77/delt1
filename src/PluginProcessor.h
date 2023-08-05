#pragma once

#include "AudioProcessing.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "CabSim.h" // Include the header for the CabSim class
#include <nlohmann/json.hpp>
#include "RTNeuralLSTM.h"
#include "Eq4Band.h"
#include "CabSim.h"
#include "StateManagement.h" // Include the StateManagement header file

class ProteusAudioProcessor : public juce::AudioProcessor
{
public:
    ProteusAudioProcessor();

    StateManagement stateManagement{*this};

#ifndef JucePlugin_PreferredChannelConfigurations
     AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
      treeState(*this, nullptr, "PARAMETERS", createParameterLayout()),
      stateManagement(*this) // Initialize stateManagement with a reference to this object
#endif


    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;

    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    void set_ampEQ(float bass_slider, float mid_slider, float treble_slider);

    // Files and configuration
    void loadConfig(File configFile);
const RT_LSTM& getLSTM() const { return LSTM; }
    const RT_LSTM& getLSTM2() const { return LSTM2; }

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

    CabSim cabSimIRa; // Declare cabSimIRa of type CabSim
    int input_size;   // Declare input_size as an integer

   
    const dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>>& getDcBlocker() const { return dcBlocker; }
    const chowdsp::ResampledProcess<chowdsp::ResamplingTypes::SRCResampler<>>& getResampler() const { return resampler; }
    const CabSim& getCabSimIRa() const { return cabSimIRa; }
    const Eq4Band& getEq4band() const { return eq4band; }
    const Eq4Band& getEq4band2() const { return eq4band2; }
    float getPreviousMasterValue() const { return previousMasterValue; }

 int getInputSize() const { return input_size; }

   ~ProteusAudioProcessor();

    // Your other member functions

    void getStateInformation (juce::MemoryBlock& destData) override
    {
        stateManagement.getStateInformation(destData); // Call the getStateInformation method of the stateManagement object
    }

    void setStateInformation (const void* data, int sizeInBytes) override
    {
        stateManagement.setStateInformation(data, sizeInBytes); // Call the setStateInformation method of the stateManagement object
    }

private:
    RT_LSTM LSTM;
    RT_LSTM LSTM2;

    Eq4Band eq4band; // Amp EQ
    Eq4Band eq4band2; // Amp EQ

    std::atomic<float>* driveParam = nullptr;
    std::atomic<float>* masterParam = nullptr;
    std::atomic<float>* bassParam = nullptr;
    std::atomic<float>* midParam = nullptr;
    std::atomic<float>* trebleParam = nullptr;

    float previousDriveValue = 0.5;
    float previousMasterValue = 0.5;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> dcBlocker;

    chowdsp::ResampledProcess<chowdsp::ResamplingTypes::SRCResampler<>> resampler;
 // ... other member variables ...
    StateManagement stateManagement{*this}; // Initialize stateManagement with a referenc
    
};
