/*
  =============================================================================
    This file was auto-generated!
    It contains the basic framework code for a JUCE plugin editor.
  =============================================================================
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
    ProteusAudioProcessor& processor;

    // Containers
    Component originalContainer;
    Component duplicateContainer;

    // Components
    TextButton loadButton1;
    TextButton loadButton2;

    // Event handlers
    virtual void buttonClicked1(Button* button) override;    
    virtual void buttonClicked2(Button* button) override;

    // Utility functions
    bool isValidFormat(File configFile);
    void loadButton1Clicked();
    void loadButton2Clicked();

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
    myLookAndFeel bigKnobLAF;
    myLookAndFeel smallKnobLAF;

    virtual void slider1ValueChanged(Slider* slider) override;
    virtual void slider2ValueChanged(Slider* slider) override;

    AudioProcessorParameter* getParameter(const String& paramId);

    void odFootSw1Clicked();
    void modelSelect1Changed();
    void cabOnButton1Clicked();
    void odFootSw2Clicked();
    void modelSelect2Changed();
    void cabOnButton2Clicked();

    bool model_loaded = false;

public:
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
};
