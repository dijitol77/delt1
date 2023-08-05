#pragma once

// Forward declarations
class ProteusAudioProcessor;
class MidiProcessing;

// Includes
#include "PluginProcessor.h"
#include "juce_dsp/juce_dsp.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_core/juce_core.h"

{
public:
    AudioProcessing(ProteusAudioProcessor& p, MidiProcessing& m);

    void initialize();
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
    const juce::String getProgramName(int index); // Removed 'override'
    void changeProgramName(int index, const juce::String& newName); // Removed 'override'
    bool hasEditor() const;
    juce::AudioProcessorEditor* createEditor();
    void getStateInformation(juce::MemoryBlock& destData);
    void setStateInformation(const void* data, int sizeInBytes);
    void loadConfig(juce::File configFile);

    // Declare member variables here
    juce::AudioProcessorValueTreeState treeState;
    std::atomic<float>* driveParam;
    std::atomic<float>* masterParam;
    std::atomic<float>* bassParam;
    std::atomic<float>* midParam;
    std::atomic<float>* trebleParam;
    // ... other member variables ...

private:
    ProteusAudioProcessor& processor;
    MidiProcessing& midiProcessing;
};
