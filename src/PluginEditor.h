// ==============================================================================
// 
// This file was auto-generated!
// 
// It contains the basic framework code for a JUCE plugin editor.
// 
// ==============================================================================

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "myLookAndFeel.h"
#include <fstream>
#include <nlohmann/json.hpp>

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
    void modelSelectChanged(); // Added
    bool isValidFormat(File configFile); // Added

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ProteusAudioProcessor& processor;

    // UI Components
    Label modelLabel;
    Label versionLabel;
    ComboBox modelSelect;
    Slider ampBassKnob;
    Slider ampMidKnob;
    Slider ampTrebleKnob;
    Slider odDriveKnob;
    Slider odLevelKnob;
    ImageButton cabOnButton;
    juce::FlexBox mainFlexBox;
    juce::FlexBox controlFlexBox;
    juce::Label loadedModelLabel;  // Add this line

 // Add these new members
    Image background2;
    ToggleButton placeholderSwitch;  // Assuming it's a ToggleButton
    ToggleButton secondPlaceholderSwitch;  // Assuming it's a ToggleButton
    bool isPlaceholderSwitchOn = false;
    bool issecondPlaceholderSwitchOn = false;

    juce::Component block1;
    juce::Component block2;
    juce::Component block3;

    juce::TextButton ButtonX;
    juce::TextButton ButtonY;

    myLookAndFeel bigKnobLAF;
    myLookAndFeel smallKnobLAF;

    std::unique_ptr<juce::ResizableCornerComponent> resizableCorner;
    std::unique_ptr<juce::ResizableBorderComponent> resizableBorder;
    juce::ComponentBoundsConstrainer constrainer;

    // Methods
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    void odFootSwClicked();
    void cabOnButtonClicked();

    // State
    bool model_loaded = false;

    // Parameter Attachments
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> bassSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> midSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> trebleSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};
