#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProteusAudioProcessorEditor::ProteusAudioProcessorEditor(ProteusAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be

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

    auto font = modelSelect.getFont();
    float height = font.getHeight();
    font.setHeight(height);

    // Set Widget Graphics
    bigKnobLAF.setLookAndFeel(juce::ImageCache::getFromMemory(BinaryData::big_knob_png, BinaryData::big_knob_pngSize));
    smallKnobLAF.setLookAndFeel(juce::ImageCache::getFromMemory(BinaryData::small_knob_png, BinaryData::small_knob_pngSize));

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
        juce::ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, juce::Colours::transparentWhite,
        juce::Image(), 1.0, juce::Colours::transparentWhite,
        juce::ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, juce::Colours::transparentWhite,
        0.0);
    addAndMakeVisible(cabOnButton);
    cabOnButton.addListener(this);

    // Initialize GUI elements for the first model
    odDriveKnobAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, odDriveKnob);
    addAndMakeVisible(odDriveKnob);
    odDriveKnob.setLookAndFeel(&bigKnobLAF);
    odDriveKnob.addListener(this);
    odDriveKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odDriveKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odDriveKnob.setDoubleClickReturnValue(true, 0.5);

    masterSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MASTER_ID, odLevelKnob);
    addAndMakeVisible(odLevelKnob);
    odLevelKnob.setLookAndFeel(&smallKnobLAF);
    odLevelKnob.addListener(this);
    odLevelKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odLevelKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odLevelKnob.setDoubleClickReturnValue(true, 0.5);

    bassSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, BASS_ID, ampBassKnob);
    addAndMakeVisible(ampBassKnob);
    ampBassKnob.setLookAndFeel(&smallKnobLAF);
    ampBassKnob.addListener(this);
    ampBassKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampBassKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampBassKnob.setDoubleClickReturnValue(true, 0.0);

    midSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MID_ID, ampMidKnob);
    addAndMakeVisible(ampMidKnob);
    ampMidKnob.setLookAndFeel(&smallKnobLAF);
    ampMidKnob.addListener(this);
    ampMidKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampMidKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampMidKnob.setDoubleClickReturnValue(true, 0.0);

    // Example initialization for ampTrebleKnob
    ampTrebleKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    ampTrebleKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    ampTrebleKnob.setPopupDisplayEnabled(true, false, this);
    ampTrebleKnob.setTextValueSuffix(" Treble");
    ampTrebleKnob.setValue(0.5); // Example initial value
    addAndMakeVisible(ampTrebleKnob);
    ampTrebleKnob.setLookAndFeel(&smallKnobLAF);
    ampTrebleKnob.addListener(this);
    ampTrebleKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampTrebleKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampTrebleKnob.setDoubleClickReturnValue(true, 0.0);

    // Example initialization for versionLabel
    versionLabel.setText("Version 1.0.0", juce::NotificationType::dontSendNotification);
    versionLabel.setFont(juce::Font(14.0f, juce::Font::plain));
    versionLabel.setJustificationType(juce::Justification::centred);
    // Example initialization for versionLabel
    versionLabel.setText("Version 1.0.0", juce::NotificationType::dontSendNotification);
    versionLabel.setFont(juce::Font(14.0f, juce::Font::plain));
    versionLabel.setJustificationType(juce::Justification::centred);
    // Example initialization for versionLabel
    versionLabel.setText("Version 1.0.0", juce::NotificationType::dontSendNotification);
    versionLabel.setFont(juce::Font(14.0f, juce::Font::plain));
    versionLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(versionLabel);
    versionLabel.setText("v1.2", juce::NotificationType::dontSendNotification);
    versionLabel.setJustificationType(juce::Justification::left);
    versionLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    versionLabel.setFont(font);

    // Set Width of Plugin GUI to 1000
    setSize(1000, 650);

    // Initialize newModelSelect
    newModelSelect.addItem("Default Model", 1);
    newModelSelect.setSelectedId(1);
    newModelSelect.onChange = [this]() { newModelSelectChanged(); };
    addAndMakeVisible(newModelSelect);
    newModelSelect.setColour(juce::Label::textColourId, juce::Colours::black);
    newModelSelect.setScrollWheelEnabled(true);
    int d = 1;
    for (const auto& jsonFile : processor.jsonFiles) {
        newModelSelect.addItem(jsonFile.getFileName(), d);
        d += 1;
    }
    newModelSelect.onChange = [this] { newModelSelectChanged(); };

    // Position the GUI Elements
    positionElements();

    // Connect the sliders to the processor parameters
    ampTrebleKnobAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "ampTreble", ampTrebleKnob);
    newAmpBassKnobAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "newAmpBass", newAmpBassKnob);
    newAmpMidKnobAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "newAmpMid", newAmpMidKnob);
    newAmpTrebleKnobAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "newAmpTreble", newAmpTrebleKnob);
    newOdDriveKnobAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "newOdDrive", newOdDriveKnob);
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
void ProteusAudioProcessorEditor::paint(juce::Graphics& g)
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
    // ...
    // Resizing code for existing GUI elements
    // ...

    // Position the new GUI elements for the second model
    positionNewModelElements();
}

void ProteusAudioProcessorEditor::positionElements()
{
    // ...
    // Positioning code for existing GUI elements
    // ...

    // Position the new GUI elements for the second model
    int xPos = 100;
    int yPos = 100;
    int knobWidth = 100;
    int knobHeight = 100;

    // Set positions and sizes for existing GUI elements
    // ...

    // Position the new GUI elements for the second model
    positionNewModelElements(xPos, yPos, knobWidth, knobHeight);





    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //Overall Widgets
    loadButton.setBounds(186, 48, 120, 24);
    modelSelect.setBounds(52, 11, 400, 28);
    //modelLabel.setBounds(197, 2, 90, 25);
    versionLabel.setBounds(462, 632, 60, 10);
    cabOnButton.setBounds(115, 233, 53, 39);

    // Overdrive Widgets
    odDriveKnob.setBounds(168, 242, 190, 190);
    odLevelKnob.setBounds(340, 225, 62, 62);
    //odFootSw.setBounds(185, 416, 175, 160);

    ampBassKnob.setBounds(113, 131, 62, 62);
    ampMidKnob.setBounds(227, 131, 62, 62);
    ampTrebleKnob.setBounds(340, 131, 62, 62);

    // Position the GUI Elements for the Second Model
    positionNewModelElements();
}

void ProteusAudioProcessorEditor::positionNewModelElements(int xPos, int yPos, int knobWidth, int knobHeight)
{
    // Define the position for the GUI elements of the second model
    // ...

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
    newOdDriveKnob.setDoubleClickReturnValue(true, 0.0);
}

void ProteusAudioProcessorEditor::loadButtonClicked()
{
    auto selectedModel = modelSelect.getSelectedItemIndex();
    if (selectedModel > 0)
    {
        processor.loadModel(selectedModel - 1); // Adjusting for 0-based index
        updateVisibility();
        resized();
    }
}

void ProteusAudioProcessorEditor::modelSelectChanged()
{
    auto selectedModel = modelSelect.getSelectedItemIndex();
    if (selectedModel > 0)
    {
        processor.loadModel(selectedModel - 1); // Adjusting for 0-based index
        updateVisibility();
        resized();
    }
    repaint();
}

void ProteusAudioProcessorEditor::newModelSelectChanged()
{
    auto selectedNewModel = newModelSelect.getSelectedItemIndex();
    if (selectedNewModel > 0)
    {
        processor.loadNewModel(selectedNewModel - 1); // Adjusting for 0-based index
        updateVisibility();
        resized();
    }
}

void ProteusAudioProcessorEditor::updateVisibility()
{
    bool isFirstModelSelected = (modelSelect.getSelectedItemIndex() > 0);
    // Set the visibility of GUI elements based on selected models
    odDriveKnob.setVisible(isFirstModelSelected);
    odLevelKnob.setVisible(isFirstModelSelected);
    ampBassKnob.setVisible(isFirstModelSelected);
    ampMidKnob.setVisible(isFirstModelSelected);
    ampTrebleKnob.setVisible(isFirstModelSelected);

    bool isNewModelSelected = (newModelSelect.getSelectedItemIndex() > 0);
    // Set the visibility of GUI elements for the second model
    newAmpBassKnob.setVisible(isNewModelSelected);
    newAmpMidKnob.setVisible(isNewModelSelected);
    newAmpTrebleKnob.setVisible(isNewModelSelected);
    newOdDriveKnob.setVisible(isNewModelSelected);
}

void ProteusAudioProcessorEditor::odFootSwClicked()
{
    // ... (Code to handle OD footswitch click)
}

// ... (Implement other button click handlers)

void ProteusAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &modelSelect)
    {
        modelSelectChanged();
    }
    else if (comboBoxThatHasChanged == &newModelSelect)
    {
        newModelSelectChanged();
    }
}

// ... (Implement other listener methods)

bool isValidFormat(const juce::File& file)
{
    return file.hasFileExtension(".json");
}
