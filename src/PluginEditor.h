#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "myLookAndFeel.h"

class ProteusAudioProcessorEditor : public juce::AudioProcessorEditor,
                                    public Slider::Listener,
                                    public juce::ComboBox::Listener
{
public:
    ProteusAudioProcessorEditor (ProteusAudioProcessor&);
    ~ProteusAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    std::unique_ptr<FileChooser> myChooser;

    void loadFromFolder();
    void resetImages();
    bool isValidFormat(File configFile);

private:
    ProteusAudioProcessor& processor;

    // Global Widgets
    Label modelLabel;
    Label versionLabel;
    ComboBox modelSelect;

    // Overdrive Widgets
    Slider odDriveKnob;
    Slider odDriveKnob2;
    Slider odLevelKnob;

    Image background2;

    // ... (rest of the code remains unchanged)

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};
