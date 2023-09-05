#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "myLookAndFeel.h"

//==============================================================================
/**
*/
class ProteusAudioProcessorEditor : public juce::AudioProcessorEditor,
                                    public juce::Button::Listener,
                                    public juce::Slider::Listener,
                                    public juce::ComboBox::Listener
{
public:
    ProteusAudioProcessorEditor (ProteusAudioProcessor&);
    ~ProteusAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void loadFromFolder();
    void resetImages();
    bool isValidFormat(juce::File configFile);

    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

private:
    void initializeComponents();
    void modelSelectChanged();

    ProteusAudioProcessor& processor;

    juce::Label modelLabel;
    juce::Label versionLabel;
    juce::ComboBox modelSelect;

    juce::Slider ampBassKnob;
    juce::Slider ampMidKnob;
    juce::Slider ampTrebleKnob;
    juce::Slider odDriveKnob;
    juce::Slider odLevelKnob;

    juce::TextButton cabOnButton;

    juce::FlexBox mainFlexBox;
    juce::FlexBox controlFlexBox;
    juce::Label loadedModelLabel;

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

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bassSliderAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> midSliderAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> trebleSliderAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;

    juce::Image background2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};
