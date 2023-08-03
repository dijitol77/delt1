#pragma once
#include "AudioProcessing.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

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


class ProteusAudioProcessor : public juce::AudioProcessor
{
public:
    ProteusAudioProcessor();
    ~ProteusAudioProcessor();

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

    const dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>>& getDcBlocker() const { return dcBlocker; }
    const chowdsp::ResampledProcess<chowdsp::ResamplingTypes::SRCResampler<>>& getResampler() const { return resampler; }
    const CabSim& getCabSimIRa() const { return cabSimIRa; }
    const Eq4Band& getEq4band() const { return eq4band; }
    const Eq4Band& getEq4band2() const { return eq4band2; }
    float getPreviousMasterValue() const { return previousMasterValue; }


    // Add your methods and member variables here
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

    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> dcBlocker;

    chowdsp::ResampledProcess<chowdsp::ResamplingTypes::SRCResampler<>> resampler;

    // IR processing
    CabSim cabSimIRa;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProteusAudioProcessor)

    // ... Other private member functions and variables ...
};
