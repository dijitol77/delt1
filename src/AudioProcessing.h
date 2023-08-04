#pragma once
#include "PluginProcessor.h"
#include "juce_dsp/juce_dsp.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_core/juce_core.h"

class AudioProcessing
{
public:
    AudioProcessing(ProteusAudioProcessor& p) : processor(p) {}

    void initialize()

    AudioProcessing();
    ~AudioProcessing();
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);
    void set_ampEQ(float bass_slider, float mid_slider, float treble_slider);
    bool acceptsMidi() const;
    bool producesMidi() const;
    bool isMidiEffect() const;
    double getTailLengthSeconds() const;
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram(int index);
    const juce::String getProgramName(int index) override; // Add 'override' here
    void changeProgramName(int index, const juce::String& newName) override; // Add 'override' here
    bool hasEditor() const;
    juce::AudioProcessorEditor* createEditor();
    void getStateInformation(juce::MemoryBlock& destData); // Use fully qualified name for MemoryBlock
    void setStateInformation(const void* data, int sizeInBytes);
    void loadConfig(juce::File configFile); // Use fully qualified name for File

    // Declare member variables here
    juce::AudioProcessorValueTreeState treeState; // Use fully qualified name for AudioProcessorValueTreeState
    std::atomic<float>* driveParam;
    std::atomic<float>* masterParam;
    std::atomic<float>* bassParam;
    std::atomic<float>* midParam;
    std::atomic<float>* trebleParam;
    // ... other member variables ...

private:
    ProteusAudioProcessor& processor; // assuming 'processor' is a member variable of AudioProcessing
};
