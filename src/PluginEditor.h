#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "JUCE/modules/juce_gui_basics/layout/juce_FlexBox.h"  // Uncommented this line

#include "PluginProcessor.h"
#include "myLookAndFeel.h"


//==============================================================================

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
    // repsonsive layout

    juce::FlexBox mainFlexBox;
    juce::FlexBox leftContainerFlexBox;
    juce::FlexBox rightContainerFlexBox;

    ProteusAudioProcessor& processor;

    // Declare the left container 

    Component leftContainer;
    TextButton loadButton;

    // Declare the right container

    Component rightContainer;   
    TextButton loadButtonRight;

    virtual void buttonClicked(Button* button) override;

    bool isValidFormat(File configFile);
    void loadButtonRightClicked();
    void loadButtonClicked();
    


ImageComponent leftBackground;  // For displaying the image in the left container
Image leftBackgroundImage;      // The actual image data for the left container

ImageComponent rightBackground; // For displaying the image in the right container
Image rightBackgroundImage;     // The actual image data for the right container


Image leftBackground_on;
Image leftBackground_on_blue;
Image rightBackground_on;
Image rightBackground_on_blue;





    

    // Global Widgets
    Label modelLabel;
    Label versionLabel;

    ComboBox modelSelect;
    ComboBox modelSelectRight;

    // Overdrive Widgets
    Slider ampBassKnob;
    Slider ampMidKnob;
    Slider ampTrebleKnob;
    Slider odDriveKnob;
    Slider odDriveKnobRight;
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
    void modelSelectChanged();
    void modelSelectChangedRight();
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
