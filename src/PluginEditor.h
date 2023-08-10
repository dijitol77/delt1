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


class ProteusAudioProcessorEditor  : public AudioProcessorEditor,
                                     public Button::Listener,
                                     public Slider::Listener,
                                     public ComboBox::Listener
{
public:
    ProteusAudioProcessorEditor (ProteusAudioProcessor&);
    ~ProteusAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    bool isValidFormat(File configFile);
    void loadButton1Clicked();
    void loadButton2Clicked();
    void loadFromFolder1();
    void loadFromFolder2();
    void button1Clicked(juce::Button* button);
    void button2Clicked(juce::Button* button);
    bool isValidFormat(File configFile);
    void loadButton1Clicked();
    void loadButton2Clicked();
    void loadFromFolder1();
    void loadFromFolder2();
    void button1Clicked(juce::Button* button);
    void button2Clicked(juce::Button* button);
    void resetImages();

    // UI Components
    TextButton loadButton1, loadButton2;
    ComboBox modelSelect1, modelSelect2;
    Label versionLabel1, versionLabel2;
    ImageButton cabOnButton1, cabOnButton2;
    Slider odDriveKnob1, odLevelKnob1, ampBassKnob1, ampMidKnob1, ampTrebleKnob1;
    Slider odDriveKnob2, odLevelKnob2, ampBassKnob2, ampMidKnob2, ampTrebleKnob2;
    Slider driveSlider2, driveSlider1, masterSlider;
    juce::Slider driveSlider;

    // Containers

    Component originalContainer;
    Component duplicateContainer;



    // LookandFeels and Graphics
    Image background_on = ImageCache::getFromMemory(BinaryData::background_on_jpg, BinaryData::background_on_jpgSize);
    Image background_on_blue = ImageCache::getFromMemory(BinaryData::background_on_blue_jpg, BinaryData::background_on_blue_jpgSize);

    // Global Widgets
    Label modelLabel1;
    Label versionLabel1;
    
    ComboBox modelSelect1;

    // Overdrive Widgets
    Slider ampBassKnob1;
    Slider ampMidKnob1;
    Slider ampTrebleKnob1;
    Slider odDriveKnob1;
    Slider odLevelKnob1;
    
    ImageButton cabOnButton1;


    // Duplicated Components
    Label modelLabel2;
    Label versionLabel2;
    ComboBox modelSelect2;

    Slider ampBassKnob2;
    Slider ampMidKnob2;
    Slider ampTrebleKnob2;
    Slider odDriveKnob2;
    Slider odLevelKnob2;

    ImageButton cabOnButton2;

    // LookandFeels 
    //myLookAndFeel blackHexKnobLAF;
    myLookAndFeel bigKnobLAF;
    myLookAndFeel smallKnobLAF;

 // Slider Value Changed Functions
    virtual void sliderValue1Changed(Slider* slider) override;
    virtual void sliderValue1Changed(Slider* slider) override;

    AudioProcessorParameter* getParameter(const String& paramId);

    bool model_loaded = false;

    // Slider Attachments
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> bassSlider1Attach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> midSlider1Attach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> trebleSlider1Attach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> driveSlider1Attach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> masterSlider1Attach;

    // Duplicated Slider Attachments
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> bassSlider2Attach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> midSlider2Attach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> trebleSlider2Attach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> driveSlider2Attach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> masterSlider2Attach;

private:
    // Reference to the processor
    ProteusAudioProcessor& processor;

    // Additional member variables
    std::unique_ptr<FileChooser> myChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};
