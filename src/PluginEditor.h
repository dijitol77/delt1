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

class GUIContainer : public Component, private Button::Listener, private Slider::Listener
{
public:
    GUIContainer(ProteusAudioProcessor& p);
    void resized() override;
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;

private:
    // Declare all the existing GUI elements here
    TextButton loadButton;
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

    ComboBox modelSelect;

    // Overdrive Widgets
    Slider ampBassKnob;
    Slider ampMidKnob;
    Slider ampTrebleKnob;
    Slider odDriveKnob;
    Slider odLevelKnob;
    //ImageButton odFootSw;
    //ImageButton odLED;
    ImageButton cabOnButton;

    // Attachments
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> bassSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> midSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> trebleSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;

    ProteusAudioProcessor& processor;
};

class ProteusAudioProcessorEditor : public AudioProcessorEditor
{
public:
    ProteusAudioProcessorEditor(ProteusAudioProcessor&);
    ~ProteusAudioProcessorEditor();

    void paint(Graphics&) override;
    void resized() override;

private:
    ProteusAudioProcessor& processor;

    GUIContainer guiContainer1;
    GUIContainer guiContainer2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProteusAudioProcessorEditor)
};
