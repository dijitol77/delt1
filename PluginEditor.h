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
    // Add these lines in the public section
    void buttonClicked2(Button* button);
    void loadButtonClicked();
    void cabOnButtonClicked();
    // Your implementation here
    void modelSelectChanged2();
}

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ProteusAudioProcessor& processor;

    TextButton loadButton;
    void buttonClicked(Button* button) override;
    bool isValidFormat(File configFile);

    //Image background = ImageCache::getFromMemory(BinaryData::smart_pedal_jpg, BinaryData::smart_pedal_jpgSize);
    // LookandFeels and Graphics
    Image background_on = ImageCache::getFromMemory(BinaryData::background_on_jpg, BinaryData::background_on_jpgSize);
    Image background_on_blue = ImageCache::getFromMemory(BinaryData::background_on_blue_jpg, BinaryData::background_on_blue_jpgSize);
    //Image background_off = ImageCache::getFromMemory(BinaryData::background_off_jpg, BinaryData::background_off_jpgSize);

    // Global Widgets
    Label modelLabel;
    Label versionLabel;

    ComboBox modelSelect;
    // Add these lines in the private section
    ComboBox modelSelect3;
    ComboBox modelSelect4;
    

    // Overdrive Widgets
    Slider ampBassKnob;
    Slider ampMidKnob;
    Slider ampTrebleKnob;
    Slider odDriveKnob;
    Slider odLevelKnob;
    Slider odDriveKnob3;  // Add this line
    Slider odLevelKnob3;  // Add this line
    Slider odDriveKnob4;  // Add this line
    Slider odLevelKnob4;  // Add this line
    //ImageButton odFootSw;
    //ImageButton odLED;
    ImageButton cabOnButton;
    ImageButton odFootSw3;  // Add this line
    ImageButton odLED3;  // Add this line
    ImageButton odFootSw4;  // Add this line
    ImageButton odLED4;  // Add this line

    TextButton loadButton2;
    
    // LookandFeels 
    //myLookAndFeel blackHexKnobLAF;
    myLookAndFeel bigKnobLAF;
    myLookAndFeel smallKnobLAF;

    virtual void sliderValueChanged(Slider* slider) override;

    AudioProcessorParameter* getParameter(const String& paramId);
 
    void odFootSwClicked();
    void modelSelectChanged();// Add this line
    void modelSelect3Changed();// Add this line
    void modelSelect4Changed();// Add this line
    void cabOnButtonClicked();
    void odFootSwClicked3();  // Add this line
    void modelSelectChanged3();  // Add this line
    void odFootSwClicked4();  // Add this line
    void modelSelectChanged4();  // Add this line

    bool model_loaded = false;

public:
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> bassSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> midSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> trebleSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach3;  // Add this line
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach3;  // Add this line
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach4;  // Add this line
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach4;  // Add this line
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};
