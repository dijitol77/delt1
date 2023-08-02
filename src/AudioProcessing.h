// PluginProcessor.h
#pragma once
#include "JuceHeader.h"

class ProteusAudioProcessor : public AudioProcessor
{
public:
    ProteusAudioProcessor();
    ~ProteusAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages);
    void releaseResources();
    void set_ampEQ(float bass_slider, float mid_slider, float treble_slider);
    bool acceptsMidi() const;
    bool producesMidi() const;
    bool isMidiEffect() const;
    double getTailLengthSeconds() const;
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);
    bool hasEditor() const;
    AudioProcessorEditor* createEditor();
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
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
    // Declare private member variables and functions here
    // ...
};
