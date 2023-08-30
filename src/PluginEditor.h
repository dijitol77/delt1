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
                                    public Slider::Listener                  
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


    TextButton loadButton;
    virtual void buttonClicked(Button* button) override;

    bool isValidFormat(File configFile);
    void loadButtonClicked();
    
  Image background2;
  

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
    ImageButton cabOnButton;
    juce::FlexBox mainFlexBox;
    juce::FlexBox controlFlexBox;
    juce::Label loadedModelLabel;

    juce::Component block1;
    juce::Component block2;
    juce::Component block3;

    myLookAndFeel bigKnobLAF;
    myLookAndFeel smallKnobLAF;

    std::unique_ptr<juce::ResizableCornerComponent> resizableCorner;
    std::unique_ptr<juce::ResizableBorderComponent> resizableBorder;
    juce::ComponentBoundsConstrainer constrainer;

    juce::FlexBox flexBox;
    juce::FlexBox nestedFlexBox;

    // ... other member variables ...

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (YourAudioProcessorEditor)
};

    virtual void sliderValueChanged(Slider* slider) override;

    AudioProcessorParameter* getParameter(const String& paramId);
 
    void odFootSwClicked();
    void modelSelectChanged();
    void cabOnButtonClicked();

    bool model_loaded = false;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> bassSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> midSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> trebleSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};
