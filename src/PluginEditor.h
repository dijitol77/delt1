/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "myLookAndFeel.h"

//==============================================================================
/**
*/
class ProteusAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                     public juce::Button::Listener
{
public:
    ProteusAudioProcessorEditor(ProteusAudioProcessor& p);

    //==============================================================================
    void paint(Graphics&) override;
    void resized() override;
    std::unique_ptr<FileChooser> myChooser;

    void loadFromFolder();
    void resetImages();
    void buttonClicked(juce::Button* button) override;
    void loadButtonClicked();
    void cabOnButtonClicked();
    void modelSelectChanged2();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ProteusAudioProcessor& processor;

    TextButton loadButton;
    TextButton loadButton2; // Add the declaration of loadButton2
    Label modelLabel;
    myLookAndFeel bigKnobLAF;
    myLookAndFeel smallKnobLAF;
    ImageButton cabOnButton;
    Slider odDriveKnob;
    Slider odLevelKnob;
    ComboBox modelSelect;
    ComboBox modelSelect2;
    ComboBox modelSelect3;
    ComboBox modelSelect4;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;

    virtual void buttonClicked(Button* button) override;

    bool isValidFormat(File configFile);
    void loadButtonClicked();

    //Image background = ImageCache::getFromMemory(BinaryData::smart_pedal_jpg, BinaryData::smart_pedal_jpgSize);
    // LookandFeels and Graphics
    Image background_on = ImageCache::getFromMemory(BinaryData::background_on_jpg, BinaryData::background_on_jpgSize);
    Image background_on_blue = ImageCache::getFromMemory(BinaryData::background_on_blue_jpg, BinaryData::background_on_blue_jpgSize);
    //Image background_off = ImageCache::getFromMemory(BinaryData::background_off_jpg, BinaryData::background_off_jpgSize);

    // Global Widgets
    Label modelLabel;
    Label versionLabel;

    // Existing ComboBoxes
    juce::ComboBox modelSelect;
    juce::ComboBox modelSelect2;

    // New ComboBoxes for the third and fourth model
    juce::ComboBox modelSelect3;
    juce::ComboBox modelSelect4;

    // Overdrive Widgets
    Slider ampBassKnob;
    Slider ampMidKnob;
    Slider ampTrebleKnob;
    Slider odDriveKnob;
    Slider odLevelKnob;
    //ImageButton odFootSw;
    //ImageButton odLED;
    ImageButton cabOnButton;

    // LookandFeels 
    //myLookAndFeel blackHexKnobLAF;
    myLookAndFeel bigKnobLAF;
    myLookAndFeel smallKnobLAF;

    virtual void sliderValueChanged(Slider* slider) override;

    AudioProcessorParameter* getParameter(const String& paramId);

    void odFootSwClicked();
    void cabOnButtonClicked();
    void modelSelectChanged();
    void modelSelect2Changed();
    void modelSelect3Changed();
    void modelSelect4Changed();

    bool model_loaded = false;

public: // Public access specifier should be placed here
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> bassSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> midSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> trebleSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};

/*
    Label versionLabel;

    // Existing ComboBoxes
    juce::ComboBox modelSelect2;

    // New ComboBoxes for the third and fourth model
    juce::ComboBox modelSelect3;
    juce::ComboBox modelSelect4;

    // Overdrive Widgets
    Slider ampBassKnob;
    Slider ampMidKnob;
    Slider ampTrebleKnob;

    virtual void sliderValueChanged(Slider* slider) override;

    AudioProcessorParameter* getParameter(const String& paramId);

    void odFootSwClicked();
    void cabOnButtonClicked();
    void modelSelectChanged();
    void modelSelect2Changed();
    void modelSelect3Changed();
    void modelSelect4Changed();

    bool model_loaded = false;

public: // Public access specifier should be placed here
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> bassSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> midSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> trebleSliderAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
*/
};
