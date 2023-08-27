#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "myLookAndFeel.h"

//==============================================================================
/**
*/
class ProteusAudioProcessorEditor  : public AudioProcessorEditor,
                                       private Button::Listener,
                                       private Slider::Listener                  
{
public:
    ProteusAudioProcessorEditor (ProteusAudioProcessor&);
    ~ProteusAudioProcessorEditor() override;
    {
        // Initialize UI components here
        addAndMakeVisible(loadButton);
        addAndMakeVisible(ampBassKnob);
        addAndMakeVisible(ampMidKnob);
        // ... (initialize other UI components)

        setSize (400, 300);
    }

    ~ProteusAudioProcessorEditor() override;

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void loadFromFolder();
    void resetImages();

private:
    ProteusAudioProcessor& processor;

    TextButton loadButton;
    void buttonClicked(Button* button) override;

    bool isValidFormat(File configFile);
    void loadButtonClicked();

    Image background_on = ImageCache::getFromMemory(BinaryData::background_on_jpg, BinaryData::background_on_jpgSize);
    Image background_on_blue = ImageCache::getFromMemory(BinaryData::background_on_blue_jpg, BinaryData::background_on_blue_jpgSize);

    Label modelLabel;
    Label versionLabel;
    ComboBox modelSelect;

    Slider ampBassKnob;
    Slider ampMidKnob;
    Slider ampTrebleKnob;
    Slider odDriveKnob;
    Slider odLevelKnob;
    ImageButton cabOnButton;

    myLookAndFeel bigKnobLAF;
    myLookAndFeel smallKnobLAF;

    void sliderValueChanged(Slider* slider) override;

    AudioProcessorParameter* getParameter(const String& paramId);

    void odFootSwClicked();
    void modelSelectChanged();
    void cabOnButtonClicked();

    bool model_loaded = false;

public:
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> bassSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> midSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> trebleSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};
