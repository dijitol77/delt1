#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "myLookAndFeel.h"

class ProteusAudioProcessorEditor : public AudioProcessorEditor,
                                    public Slider::Listener,
                                    public Button::Listener, // <-- Add this line
                                    public ComboBox::Listener
{
public:
    ProteusAudioProcessorEditor (ProteusAudioProcessor&);
    ~ProteusAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    std::unique_ptr<FileChooser> myChooser;

    void loadFromFolder();
    void resetImages();
    bool isValidFormat(File configFile);

     juce::ToggleButton placeholderSwitch;
    bool isPlaceholderSwitchOn = false;

private:
    ProteusAudioProcessor& processor;

    // Global Widgets
    Label modelLabel;
    Label versionLabel;
    ComboBox modelSelect;

    // Overdrive Widgets
    Slider odDriveKnob;
    Slider odDriveKnob2;
    Slider odLevelKnob;

    Image background2;

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

    virtual void sliderValueChanged(Slider* slider) override;
    AudioProcessorParameter* getParameter(const String& paramId);
    void modelSelectChanged();
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

    bool model_loaded = false;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> bassSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> midSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> trebleSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};
