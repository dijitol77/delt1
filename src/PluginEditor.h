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
class ProteusAudioProcessorEditor  : public AudioProcessorEditor,
                                       private Button::Listener,
                                       private Slider::Listener                  
{
public:
    ProteusAudioProcessorEditor (ProteusAudioProcessor&);
    ~ProteusAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    std::unique_ptr<FileChooser> myChooser;

    void loadFromFolder();
    void resetImages();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ProteusAudioProcessor& processor;

    // Containers
    Component originalContainer;
    Component duplicateContainer;

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

    // Duplicated Components
    
    Label modelLabel2;
    Label versionLabel2;

    ComboBox modelSelect2;

    Slider ampBassKnob2;
    Slider ampMidKnob2;
    Slider ampTrebleKnob2;
    Slider odDriveKnob2;
    Slider odLevelKnob2;
    // ... other component initializations ...
    //ImageButton odFootSw;
