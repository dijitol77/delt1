/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProteusAudioProcessorEditor::ProteusAudioProcessorEditor(ProteusAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p),
      newAmpBassKnob(0.0f), newAmpMidKnob(0.0f), newAmpTrebleKnob(0.0f), newOdDriveKnob(0.0f)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to

    // Overall Widgets
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("LOAD MODEL");
    loadButton.addListener(this);

    addAndMakeVisible(modelSelect);
    modelSelect.setColour(juce::Label::textColourId, juce::Colours::black);
    modelSelect.setScrollWheelEnabled(true);
    int c = 1;
    for (const auto& jsonFile : processor.jsonFiles) {
        modelSelect.addItem(jsonFile.getFileName(), c);
        c += 1;
    }
    modelSelect.onChange = [this] { modelSelectChanged(); };

    auto font = modelLabel.getFont();
    float height = font.getHeight();
    font.setHeight(height);

    // Set Widget Graphics
    bigKnobLAF.setLookAndFeel(ImageCache::getFromMemory(BinaryData::big_knob_png, BinaryData::big_knob_pngSize));
    smallKnobLAF.setLookAndFeel(ImageCache::getFromMemory(BinaryData::small_knob_png, BinaryData::small_knob_pngSize));

    // Pre Amp Pedal Widgets

    /*
    // Overdrive
    odFootSw.setImages(true, true, true,
        ImageCache::getFromMemory(BinaryData::footswitch_up_png, BinaryData::footswitch_up_pngSize), 1.0, Colours::transparentWhite,
        Image(), 1.0, Colours::transparentWhite,
        ImageCache::getFromMemory(BinaryData::footswitch_down_png, BinaryData::footswitch_down_pngSize), 1.0, Colours::transparentWhite,
        0.0);
    addAndMakeVisible(odFootSw);
    odFootSw.addListener(this);
    */

    cabOnButton.setImages(true, true, true,
        ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
        Image(), 1.0, Colours::transparentWhite,
        ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
        0.0);
    addAndMakeVisible(cabOnButton);
    cabOnButton.addListener(this);

    driveSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, odDriveKnob);
    addAndMakeVisible(odDriveKnob);
    odDriveKnob.setLookAndFeel(&bigKnobLAF);
    odDriveKnob.addListener(this);
    odDriveKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odDriveKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odDriveKnob.setDoubleClickReturnValue(true, 0.5);

    masterSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MASTER_ID, odLevelKnob);
    addAndMakeVisible(odLevelKnob);
    odLevelKnob.setLookAndFeel(&smallKnobLAF);
    odLevelKnob.addListener(this);
    odLevelKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odLevelKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odLevelKnob.setDoubleClickReturnValue(true, 0.5);

    bassSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, BASS_ID, ampBassKnob);
    addAndMakeVisible(ampBassKnob);
    ampBassKnob.setLookAndFeel(&smallKnobLAF);
    ampBassKnob.addListener(this);
    ampBassKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampBassKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampBassKnob.setDoubleClickReturnValue(true, 0.0);

    midSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MID_ID, ampMidKnob);
    addAndMakeVisible(ampMidKnob);
    ampMidKnob.setLookAndFeel(&smallKnobLAF);
    ampMidKnob.addListener(this);
    ampMidKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampMidKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampMidKnob.setDoubleClickReturnValue(true, 0.0);

    trebleSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, TREBLE_ID, ampTrebleKnob);
    addAndMakeVisible(ampTrebleKnob);
    ampTrebleKnob.setLookAndFeel(&smallKnobLAF);
    ampTrebleKnob.addListener(this);
    ampTrebleKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampTrebleKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampTrebleKnob.setDoubleClickReturnValue(true, 0.0);

    addAndMakeVisible(versionLabel);
    versionLabel.setText("v1.2", juce::NotificationType::dontSendNotification);
    versionLabel.setJustificationType(juce::Justification::left);
    versionLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    versionLabel.setFont(font);

    // Set Width of Plugin GUI to 1000
    setSize(1000, 650);
    // Create Second Set of GUI Elements for the New Model
    addAndMakeVisible(newModelSelect);
    newModelSelect.setColour(juce::Label::textColourId, juce::Colours::black);
    newModelSelect.setScrollWheelEnabled(true);
    // Populate the newModelSelect ComboBox (same as modelSelect)

    // Position the GUI Elements
    positionNewModelElements();

    // ... (Existing code in the constructor)
}

void ProteusAudioProcessorEditor::positionNewModelElements()
{
    // Position the GUI Elements for the Second Model

    // Example positioning for the second model (you can adjust the positions as needed)
    int secondModelX = 500; // X position for the second model elements
    int elementHeight = 62; // Example height for the elements

    newModelSelect.setBounds(secondModelX + 52, 11, 400, 28);
    newAmpBassKnob.setBounds(secondModelX + 113, 131, 62, elementHeight);
    newAmpMidKnob.setBounds(secondModelX + 227, 131, 62, elementHeight);
    newAmpTrebleKnob.setBounds(secondModelX + 340, 131, 62, elementHeight);
    newOdDriveKnob.setBounds(secondModelX + 168, 242, 190, 190);
    newOdLevelKnob.setBounds(secondModelX + 340, 225, 62, 62);
    newCabOnButton.setBounds(secondModelX + 115, 233, 53, 39);

    resetImages();

    loadFromFolder();
}

ProteusAudioProcessorEditor::~ProteusAudioProcessorEditor()
{
    odDriveKnob.setLookAndFeel(nullptr);
    odLevelKnob.setLookAndFeel(nullptr);
    ampBassKnob.setLookAndFeel(nullptr);
    ampMidKnob.setLookAndFeel(nullptr);
    ampTrebleKnob.setLookAndFeel(nullptr);
}

//==============================================================================
void ProteusAudioProcessorEditor::paint(Graphics& g)
{
    // Workaround for graphics on Windows builds (clipping code doesn't work correctly on Windows)
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    //if (processor.fw_state == 0) {
    //    g.drawImageAt(background_off, 0, 0);  // Debug Line: Redraw entire background image
    if (processor.fw_state == 1 && processor.conditioned == true) {
        g.drawImageAt(background_on, 0, 0);  // Debug Line: Redraw entire background image
    }
    else if (processor.fw_state == 1 && processor.conditioned == false) {
        g.drawImageAt(background_on_blue, 0, 0);  // Debug Line: Redraw entire background image
    }
#else
    // Redraw only the clipped part of the background image
    juce::Rectangle<int> ClipRect = g.getClipBounds();
    //if (processor.fw_state == 0) {
    //    g.drawImage(background_off, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    if (processor.fw_state == 1 && processor.conditioned == true) {
        g.drawImage(background_on, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    }
    else if (processor.fw_state == 1 && processor.conditioned == false) {
        g.drawImage(background_on_blue, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    }
#endif
}

void ProteusAudioProcessorEditor::resized()
{
    // New GUI Element Positions
    int xPos = 100;
    int yPos = 100;
    int knobWidth = 100;
    int knobHeight = 100;

    // Set positions and sizes for existing GUI elements
    // ...

    // Position the new GUI elements for the second model
    positionNewModelElements(xPos, yPos, knobWidth, knobHeight);
}

void ProteusAudioProcessorEditor::positionNewModelElements(int xPos, int yPos, int knobWidth, int knobHeight)
{
    // Define the position for the GUI elements of the second model

    // Set the position of newAmpBassKnob
    newAmpBassKnob.setBounds(xPos, yPos, knobWidth, knobHeight);
    addAndMakeVisible(newAmpBassKnob);
    newAmpBassKnob.setLookAndFeel(&smallKnobLAF);
    newAmpBassKnob.addListener(this);
    newAmpBassKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    newAmpBassKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    newAmpBassKnob.setDoubleClickReturnValue(true, 0.0);

    // Set the position of newAmpMidKnob
    newAmpMidKnob.setBounds(xPos, yPos, knobWidth, knobHeight);
    addAndMakeVisible(newAmpMidKnob);
    newAmpMidKnob.setLookAndFeel(&smallKnobLAF);
    newAmpMidKnob.addListener(this);
    newAmpMidKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    newAmpMidKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    newAmpMidKnob.setDoubleClickReturnValue(true, 0.0);

    // Set the position of newAmpTrebleKnob
    newAmpTrebleKnob.setBounds(xPos, yPos, knobWidth, knobHeight);
    addAndMakeVisible(newAmpTrebleKnob);
    newAmpTrebleKnob.setLookAndFeel(&smallKnobLAF);
    newAmpTrebleKnob.addListener(this);
    newAmpTrebleKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    newAmpTrebleKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    newAmpTrebleKnob.setDoubleClickReturnValue(true, 0.0);

    // Set the position of newOdDriveKnob
    newOdDriveKnob.setBounds(xPos, yPos, knobWidth, knobHeight);
    addAndMakeVisible(newOdDriveKnob);
    newOdDriveKnob.setLookAndFeel(&bigKnobLAF);
    newOdDriveKnob.addListener(this);
    newOdDriveKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    newOdDriveKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    newOdDriveKnob.setDoubleClickReturnValue(true, 0.5);

    // Set the positions of other GUI elements for the second model
    // ... (Add your implementation here)
}


void ProteusAudioProcessorEditor::resetImages()
{
    // Load pedal switch images
    Image cab_on = ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize);
    Image cab_off = ImageCache::getFromMemory(BinaryData::cab_switch_off_png, BinaryData::cab_switch_off_pngSize);
    cabOnButton.setImages(true, true, true, cab_on, 1.0, Colours::transparentWhite,
        cab_off, 1.0, Colours::transparentWhite,
        cab_on, 1.0, Colours::transparentWhite,
        0.0);
}
    repaint();
    /*
    if (processor.fw_state == 0) {
        odFootSw.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::footswitch_up_png, BinaryData::footswitch_up_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::footswitch_up_png, BinaryData::footswitch_up_pngSize), 1.0, Colours::transparentWhite,
            0.0);
    }
    else {
        odFootSw.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::footswitch_down_png, BinaryData::footswitch_down_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::footswitch_down_png, BinaryData::footswitch_down_pngSize), 1.0, Colours::transparentWhite,
            0.0);
    }
    */
    // Set On/Off cab graphic
    if (processor.cab_state == 0) {
        cabOnButton.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::cab_switch_off_png, BinaryData::cab_switch_off_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::cab_switch_off_png, BinaryData::cab_switch_off_pngSize), 1.0, Colours::transparentWhite,
            0.0);
    }
    else {
        cabOnButton.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
            0.0);
    }
}
