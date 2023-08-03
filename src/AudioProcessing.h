#pragma once
#include "PluginProcessor.h"
#include "juce_dsp/juce_dsp.h"

class ProteusAudioProcessor; // Forward declaration of ProteusAudioProcessor

class AudioProcessing
{
public:
    AudioProcessing(); // constructor
    ~AudioProcessing(); // destructor
    void initialize(ProteusAudioProcessor& p);
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
    const String getProgramName(int index);
    void changeProgramName(int index, const String& newName);
    bool hasEditor() const;
    AudioProcessorEditor* createEditor();
    void getStateInformation(MemoryBlock& destData);
    void setStateInformation(const void* data, int sizeInBytes);
    void loadConfig(File configFile);

    // Declare member variables here
    AudioProcessorValueTreeState treeState;
    std::atomic<float>* driveParam;
    std::atomic<float>* masterParam;
    std::atomic<float>* bassParam;
    std::atomic<float>* midParam;
    std::atomic<float>* trebleParam;
    // ... other member variables ...

private:
    ProteusAudioProcessor& processor; // assuming 'processor' is a member variable of AudioProcessing
};
