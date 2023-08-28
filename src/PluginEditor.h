#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "myLookAndFeel.h"

class LeftContainer : public Component
{
public:
    LeftContainer(ProteusAudioProcessor& p);
    void paint(Graphics& g) override;
    void resized() override;

private:
    ProteusAudioProcessor& processor;
    TextButton loadButton;
    ComboBox modelSelect;
    Slider odDriveKnob;
    // ... other components
};

class RightContainer : public LeftContainer
{
public:
    RightContainer(ProteusAudioProcessor& p);
};

class ProteusAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ProteusAudioProcessorEditor (ProteusAudioProcessor&);
    ~ProteusAudioProcessorEditor() override;

    void paint (Graphics&) override;
    void resized() override;

private:
    ProteusAudioProcessor& processor;

    LeftContainer leftContainer;
    RightContainer rightContainer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};
