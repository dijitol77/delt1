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

    Slider odDriveKnob2, odLevelKnob2;

    TextButton loadButton;
    //2

    TextButton loadButton2;
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
    //2
    ComboBox modelSelect2;

    // Overdrive Widgets
    Slider ampBassKnob;
    Slider ampMidKnob;
    Slider ampTrebleKnob;
    Slider odDriveKnob;
    Slider odLevelKnob;
 
    //ImageButton odFootSw;
    //ImageButton odLED;
    ImageButton cabOnButton;
     
   // 2
    Slider odDriveKnob2;
    Slider odLevelKnob2;
    ImageButton cabOnButton2;

    
    // LookandFeels 
    //myLookAndFeel blackHexKnobLAF;
    myLookAndFeel bigKnobLAF;
    myLookAndFeel smallKnobLAF;

    virtual void sliderValueChanged(Slider* slider) override;

    AudioProcessorParameter* getParameter(const String& paramId);
 
    void odFootSwClicked();
    void modelSelectChanged();
    void cabOnButtonClicked();

    // 2

    void modelSelect2Changed();
    void cabOnButton2Clicked();

    bool model_loaded = false;

public:
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> bassSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> midSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> trebleSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> driveSlider2Attach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};
