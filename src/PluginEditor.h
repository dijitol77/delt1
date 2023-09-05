#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "myLookAndFeel.h"

class ProteusAudioProcessorEditor : public juce::AudioProcessorEditor,
                                    public Button::Listener,
                                    public Slider::Listener,
                                    public ComboBox::Listener
{
public:
    ProteusAudioProcessorEditor (ProteusAudioProcessor&);
    ~ProteusAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;
    void loadFromFolder();
    void resetImages();
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
    void loadModelByName(const std::string& modelName);  // Make sure this line exists
    std::string currentModelName;  // Add this line
   

private:
    ProteusAudioProcessor& processor;

   // TextButton loadButton;
    void buttonClicked(Button* button) override;
    bool isValidFormat(File configFile);
   // void loadButtonClicked();
    Image background2;

    Label modelLabel;
    Label versionLabel;
    ComboBox modelSelect;

    Slider odDriveKnob;
    Slider odDriveKnob2;
    Slider odLevelKnob;

    ImageButton cabOnButton;
    juce::FlexBox mainFlexBox;
    juce::FlexBox controlFlexBox;

    juce::Component block1;
    juce::Component block2;
    juce::Component block3;

    myLookAndFeel bigKnobLAF;
    myLookAndFeel smallKnobLAF;

    std::unique_ptr<juce::ResizableCornerComponent> resizableCorner;
    std::unique_ptr<juce::ResizableBorderComponent> resizableBorder;

    std::unique_ptr<FileChooser> myChooser;  // Add this line

    juce::ComponentBoundsConstrainer constrainer;

   // juce::TextButton placeholderSwitch;
   // juce::TextButton secondPlaceholderSwitch;

   // juce::Label loadedModelLabel;



    void sliderValueChanged(Slider* slider) override;
    AudioProcessorParameter* getParameter(const String& paramId);

    void odFootSwClicked();
    void modelSelectChanged();
    void cabOnButtonClicked();

  //  bool isPlaceholderSwitchOn = false;
  //  bool issecondPlaceholderSwitchOn = false;

    bool model_loaded = false;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProteusAudioProcessorEditor)
};
