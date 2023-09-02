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


class ProteusAudioProcessorEditor : public juce::AudioProcessorEditor,
                                    public Button::Listener,
                                    public Slider::Listener,
                                    public juce::ComboBox::Listener // <-- Add this line               
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


 //   TextButton loadButton;
 //   virtual void buttonClicked(Button* button) override;

 //   bool isValidFormat(File configFile);
//    void loadButtonClicked();
   Image background2;
  // Image background2 = ImageCache::getFromMemory(BinaryData::BACK2_jpg, BinaryData::BACK2_jpgSize);
    //Image background = ImageCache::getFromMemory(BinaryData::smart_pedal_jpg, BinaryData::smart_pedal_jpgSize);
    // LookandFeels and Graphics
  //  Image background_on = ImageCache::getFromMemory(BinaryData::background_on_jpg, BinaryData::background_on_jpgSize);
  //  Image background_on_blue = ImageCache::getFromMemory(BinaryData::background_on_blue_jpg, BinaryData::background_on_blue_jpgSize);
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
Slider odDriveKnob2;
    Slider odLevelKnob;

    ImageButton cabOnButton;
    juce::FlexBox mainFlexBox;
    juce::FlexBox controlFlexBox;
    juce::Label loadedModelLabel;  // Add this line

juce::Component block1;
juce::Component block2;  // Declare block2 here
juce::Component block3;  // Declare block3 here

    myLookAndFeel bigKnobLAF;
    myLookAndFeel smallKnobLAF;

    std::unique_ptr<juce::ResizableCornerComponent> resizableCorner;
    std::unique_ptr<juce::ResizableBorderComponent> resizableBorder;
    juce::ComponentBoundsConstrainer constrainer;


    virtual void sliderValueChanged(Slider* slider) override;

    AudioProcessorParameter* getParameter(const String& paramId);
 
    void odFootSwClicked();
    void modelSelectChanged();
    void cabOnButtonClicked();
void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

    bool model_loaded = false;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> bassSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> midSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> trebleSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};
