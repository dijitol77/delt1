#pragma once

#include <JuceHeader.h>
#include "StateManagement.h"
#include "RTNeural.h"

class ProteusAudioProcessor  : public juce::AudioProcessor
{
public:
    ProteusAudioProcessor();
    ~ProteusAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // Additional member variables and functions from Proteus
    dsp::IIR::Filter<float> eq4band, eq4band2;
    RTNeural::RTModel<float> LSTM, LSTM2;
    bool fw_state, cab_state;
    juce::AudioParameterFloat* driveParam;
    juce::AudioParameterFloat* masterParam;
    // ... add other parameters as needed

    void set_ampEQ(float bass_slider, float mid_slider, float treble_slider);
    void loadConfig(const juce::File& configFile);

    // IR Processing
    juce::dsp::Convolution cabSimIRa;

private:
    StateManagement stateManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessor)
};
