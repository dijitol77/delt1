#pragma once

class Programs {
public:
    Programs(ProteusAudioProcessor& p); // Constructor
    void initialize(ProteusAudioProcessor& p);
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const juce::String getProgramName (int index);
    void changeProgramName (int index, const juce::String& newName);

private:
    ProteusAudioProcessor& processor; // Add this member variable
};
