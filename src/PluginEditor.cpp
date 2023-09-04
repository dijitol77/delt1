/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <algorithm>

ProteusAudioProcessorEditor::ProteusAudioProcessorEditor (ProteusAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), block1(/* constructor arguments, if any */),
      isPlaceholderSwitchOn(false), issecondPlaceholderSwitchOn(false)  // Initialize here
{
    // Existing code...
    resizableCorner = std::make_unique<juce::ResizableCornerComponent>(this, &constrainer);
    resizableBorder = std::make_unique<juce::ResizableBorderComponent>(this, &constrainer);

    addAndMakeVisible(resizableCorner.get());
    addAndMakeVisible(resizableBorder.get());

    constrainer.setFixedAspectRatio(1121.0 / 326.0);  
    // Set the fixed aspect ratio
    setSize(1121, 326);  
    // Set the initial size

    // Set the constrainer's minimum and maximum sizes
    // Minimum size set to 700x200, maximum size set to 1400x400
    constrainer.setSizeLimits(1121, 326, 1168.5, 489);
    setConstrainer(&constrainer);  
    // Add this line

    addAndMakeVisible(block1);
    addAndMakeVisible(block2);
    addAndMakeVisible(block3);


    addAndMakeVisible(modelSelect);
    modelSelect.setColour(juce::Label::textColourId, juce::Colours::black);
    modelSelect.setScrollWheelEnabled(true);
    int c = 1;
    for (const auto& jsonFile : processor.jsonFiles) {
        modelSelect.addItem(jsonFile.getFileName(), c);
        c += 1;
    }
    modelSelect.onChange = [this] {modelSelectChanged();};

    auto font = modelLabel.getFont();
    float height = font.getHeight();
    font.setHeight(height);

    // Debugging for Switch
    cabOnButton.setImages(true, true, true,
        ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
        Image(), 1.0, Colours::transparentWhite,
        ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
        0.0);
    addAndMakeVisible(cabOnButton);
    cabOnButton.addListener(this);
    cabOnButton.toFront(true);
    cabOnButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    cabOnButton.repaint();

    addAndMakeVisible(placeholderSwitch);
    placeholderSwitch.setButtonText("Switch");
    placeholderSwitch.addListener(this);
    placeholderSwitch.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);

    addAndMakeVisible(secondPlaceholderSwitch);
    secondPlaceholderSwitch.setButtonText("Second Switch");
    secondPlaceholderSwitch.addListener(this);
    secondPlaceholderSwitch.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);



    // Set Widget Graphics
    bigKnobLAF.setLookAndFeel(ImageCache::getFromMemory(BinaryData::big_knob_png, BinaryData::big_knob_pngSize));
    smallKnobLAF.setLookAndFeel(ImageCache::getFromMemory(BinaryData::small_knob_png, BinaryData::small_knob_pngSize));

// Setup odDriveKnob
driveSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, odDriveKnob);
addAndMakeVisible(odDriveKnob);
odDriveKnob.setLookAndFeel(&bigKnobLAF);
odDriveKnob.addListener(this);
odDriveKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
odDriveKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
odDriveKnob.setDoubleClickReturnValue(true, 0.5);

// Check if odDriveKnob is visible, if not make it visible
if (!odDriveKnob.isVisible()) {
    odDriveKnob.setVisible(true);
}

// Manually set the position of odDriveKnob at the top-left corner
odDriveKnob.setBounds(0, 0, 100, 100);  // x, y, width, height

// Call repaint on odDriveKnob to refresh its appearance
odDriveKnob.repaint();

// Hide odLevelKnob
odLevelKnob.setVisible(false);

// Re-setup odLevelKnob (it will remain hidden)
masterSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MASTER_ID, odLevelKnob);
// Do NOT call addAndMakeVisible for odLevelKnob here
odLevelKnob.setLookAndFeel(&smallKnobLAF);
odLevelKnob.addListener(this);
odLevelKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
odLevelKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
odLevelKnob.setDoubleClickReturnValue(true, 0.5);
  






    addAndMakeVisible(versionLabel);
    versionLabel.setText("v1.2", juce::NotificationType::dontSendNotification);
    versionLabel.setJustificationType(juce::Justification::left);
    versionLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    versionLabel.setFont(font);

// === START OF UPDATES ===
    // Initialize FlexBox Properties
    mainFlexBox.flexDirection = juce::FlexBox::Direction::column;
    mainFlexBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;

    controlFlexBox.flexDirection = juce::FlexBox::Direction::row;
    controlFlexBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;

    // Add Components to controlFlexBox
    controlFlexBox.items.add(juce::FlexItem(versionLabel).withFlex(1));
    controlFlexBox.items.add(juce::FlexItem(cabOnButton).withFlex(1));
    controlFlexBox.items.add(juce::FlexItem(odDriveKnob).withFlex(1));
    controlFlexBox.items.add(juce::FlexItem(odLevelKnob).withFlex(1));
    controlFlexBox.items.add(juce::FlexItem(ampBassKnob).withFlex(1));
    controlFlexBox.items.add(juce::FlexItem(ampMidKnob).withFlex(1));
    controlFlexBox.items.add(juce::FlexItem(ampTrebleKnob).withFlex(1));

    // Add Components to mainFlexBox
   // mainFlexBox.items.add(juce::FlexItem(loadButton).withFlex(1));
    mainFlexBox.items.add(juce::FlexItem(controlFlexBox).withFlex(4));

    // Use this line to load the image from binary data
    background2 = ImageCache::getFromMemory(BinaryData::BACK2_jpg, BinaryData::BACK2_jpgSize);

    // Size of plugin GUI
    setSize(1121, 326); 

    modelSelect.addListener(this);

    loadFromFolder();

    // Call resized() to set the initial layout
    resized();
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
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    if (processor.fw_state == 1 && processor.conditioned == true) {
        g.drawImageWithin(background2, 0, 0, getWidth(), getHeight(), RectanglePlacement::stretchToFit, false);
    } else if (processor.fw_state == 1 && processor.conditioned == false) {
        g.drawImageWithin(background2, 0, 0, getWidth(), getHeight(), RectanglePlacement::stretchToFit, false);
    }
#else
    juce::Rectangle<int> ClipRect = g.getClipBounds();
    if (processor.fw_state == 1 && processor.conditioned == true) {
        g.drawImage(background2, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    } else if (processor.fw_state == 1 && processor.conditioned == false) {
        g.drawImage(background2, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    }
#endif
}

// In your resized() method

void ProteusAudioProcessorEditor::resized()
{
    auto totalArea = getLocalBounds();
    
    auto colA = totalArea.removeFromLeft(totalArea.getWidth() / 3);
    auto colB = totalArea.removeFromLeft(totalArea.getWidth() / 2);
    auto colC = totalArea;

    auto blockA1 = colA.removeFromTop(colA.getHeight() / 3);
    auto blockA2 = colA.removeFromTop(colA.getHeight() / 2);
    auto blockA3 = colA;

    auto blockB1 = colB.removeFromTop(colB.getHeight() / 3);
    auto blockB2 = colB.removeFromTop(colB.getHeight() / 2);
    auto blockB3 = colB;

    auto blockC1 = colC.removeFromTop(colC.getHeight() / 3);
    auto blockC2 = colC.removeFromTop(colC.getHeight() / 2);
    auto blockC3 = colC;

 

    // Center the Model Select dropdown
    int modelSelectWidth = 200;
    int modelSelectHeight = 30;
    int modelSelectX = blockB1.getX() + (blockB1.getWidth() - modelSelectWidth) / 2;
    int modelSelectY = blockB1.getY() + (blockB1.getHeight() - modelSelectHeight) / 2;
    modelSelect.setBounds(modelSelectX, modelSelectY, modelSelectWidth, modelSelectHeight);

 // Calculate the relative offsets based on blockA2's dimensions for odDriveKnob
    int knobOffsetX = blockA2.getWidth() * 0.31;
    int knobOffsetY = blockA2.getHeight() * 0.37;

    // Calculate the size and position for odDriveKnob
    int knobWidth = blockA2.getWidth() - 20;
    int knobHeight = blockA2.getHeight() - 20;
    int knobX = blockA2.getX() + 10 + knobOffsetX;
    int knobY = blockA2.getY() + 10 + knobOffsetY;

    // Set bounds for odDriveKnob
    odDriveKnob.setBounds(knobX, knobY, knobWidth, knobHeight);

    // Calculate the relative offsets based on blockA3's dimensions for placeholderSwitch
    int switchOffsetX = blockA3.getWidth() * 0.05;  // 5% of blockA3's width for the switch
    int switchOffsetY = blockA3.getHeight() * 0;  // 0% of blockA3's height for the switch

    // Set bounds for placeholderSwitch with different dimensions
    int switchWidth = 50;  // Smaller width
    int switchHeight = 20;  // Smaller height
    int switchX = blockA3.getX() + 10 + switchOffsetX;
    int switchY = blockA3.getY() + switchOffsetY;

    placeholderSwitch.setBounds(switchX, switchY, switchWidth, switchHeight);

    // Calculate the relative offsets based on blockC3's dimensions for the second switch
    int secondSwitchOffsetX = blockC3.getWidth() * 0.52;  // 5% of blockC3's width for the switch
    int secondSwitchOffsetY = blockC3.getHeight() * 0.1;  // 0% of blockC3's height for the switch

    // Set bounds for the second switch with different dimensions
    int secondSwitchWidth = 50;  // Smaller width
    int secondSwitchHeight = 20;  // Smaller height
    int secondSwitchX = blockC3.getX() + 10 + secondSwitchOffsetX;
    int secondSwitchY = blockC3.getY() + secondSwitchOffsetY;

    secondPlaceholderSwitch.setBounds(secondSwitchX, secondSwitchY, secondSwitchWidth, secondSwitchHeight);

    // ... (existing code)

    placeholderSwitch.setBounds(switchX, switchY, switchWidth, switchHeight);

    // ... (remaining code remains unchanged)

    cabOnButton.setBounds(blockC1.reduced(10));   

    // Set bounds for the resizable corner and border
    resizableCorner->setBounds(getWidth() - 16, getHeight() - 16, 16, 16);
    resizableBorder->setBounds(0, 0, getWidth(), getHeight());

    // Set bounds for the loaded model label
    loadedModelLabel.setBounds(20, getHeight() - 80, 300, 30);
}



bool ProteusAudioProcessorEditor::isValidFormat(File configFile)
{
    // Read in the JSON file
    String path = configFile.getFullPathName();
    const char* char_filename = path.toUTF8();

    std::ifstream i2(char_filename);
    nlohmann::json weights_json;
    i2 >> weights_json;

    int hidden_size_temp = 0;
    std::string network = "";

    // Check that the hidden_size and unit_type fields exist and are correct
    if (weights_json.contains("/model_data/unit_type"_json_pointer) == true && weights_json.contains("/model_data/hidden_size"_json_pointer) == true) {
        // Get the input size of the JSON file
        int input_size_json = weights_json["/model_data/hidden_size"_json_pointer];
        std::string network_temp = weights_json["/model_data/unit_type"_json_pointer];

        network = network_temp;
        hidden_size_temp = input_size_json;
    } else {
        return false;
    }
    
    if (hidden_size_temp == 40 && network == "LSTM") {
        return true;
    } else {
        return false;
    }
}


void ProteusAudioProcessorEditor::loadFromFolder()
{
    processor.model_loaded = false;

    // Get the directory where the models are stored
    File modelsDir = File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getChildFile("models");

    // Find all JSON files in the models directory
    Array<File> files = modelsDir.findChildFiles(File::findFiles, false, "*.json");

    processor.jsonFiles.clear();
    modelSelect.clear();

    // Populate the modelSelect ComboBox and jsonFiles array
    if (files.size() > 0) {
        for (auto file : files) {
            if (isValidFormat(file)) {
                modelSelect.addItem(file.getFileNameWithoutExtension(), processor.jsonFiles.size() + 1);
                processor.jsonFiles.push_back(file);
                processor.num_models += 1;
            }
        }

        // Try to load model from saved_model, if it doesn't exist and jsonFiles is not empty, load the first model (if it exists and is a valid format)
        if (!processor.jsonFiles.empty()) {
            if (processor.saved_model.existsAsFile() && isValidFormat(processor.saved_model)) {
                processor.loadConfig(processor.saved_model);
                modelSelect.setText(processor.saved_model.getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification);
            } else {
                if (processor.jsonFiles[0].existsAsFile() && isValidFormat(processor.jsonFiles[0])) {
                    processor.loadConfig(processor.jsonFiles[0]);
                    modelSelect.setText(processor.jsonFiles[0].getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification);
                }
            }
        }
    }
}


void ProteusAudioProcessor::loadModelByName(const std::string& modelName)
{
    // Implement the function here
    // return true; // or false, depending on your implementation

    processor.setModelName(modelName);  // Call the setter function in ProteusAudioProcessor
    // Add any additional GUI logic here
  
    // Your logic to load the model based on its name
    // This could involve reading a file from a specific directory
    File modelDirectory("/models");
    File modelFile = modelDirectory.getChildFile(modelName + ".extension");

    if (modelFile.exists())
    {
        // Load the model from the file
        // Return true if successful
        return true;
    }
    else
    {
        // Return false if the model could not be loaded
        return false;
    }
}

void ProteusAudioProcessorEditor::buttonClicked(juce::Button* button)
{

   if (button == &loadButton)
    {
        loadModelByName("someModelName");  // Replace "someModelName" with the actual model name
    }
     if (button == &cabOnButton) {
        cabOnButtonClicked();
    }

  if (button == &placeholderSwitch)
    {
        isPlaceholderSwitchOn = !isPlaceholderSwitchOn; // Toggle the state

        if (isPlaceholderSwitchOn)
        {
            placeholderSwitch.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
        }
        else
        {
            placeholderSwitch.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
        }
    }
   if (button == &secondPlaceholderSwitch)
    {
        issecondPlaceholderSwitchOn = !issecondPlaceholderSwitchOn; // Toggle the state

        if (issecondPlaceholderSwitchOn)
        {
            secondPlaceholderSwitch.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
        }
        else
        {
            secondPlaceholderSwitch.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
        }
    }

}

void ProteusAudioProcessorEditor::odFootSwClicked() {
 
}

// In PluginProcessor.cpp
void ProteusAudioProcessor::setModelName(const std::string& modelName)
{
    currentModelName = modelName;
    // Add any additional logic to update the processor based on the model name
}

void ProteusAudioProcessorEditor::cabOnButtonClicked() {
    if (processor.cab_state == 0) {
        processor.cab_state = 1;
    }
    else {
        processor.cab_state = 0;
    }
    resetImages();
    repaint();
}

void ProteusAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) 
{
    if (comboBoxThatHasChanged == &modelSelect)
    {
        const int selectedFileIndex = modelSelect.getSelectedItemIndex();
        if (selectedFileIndex >= 0 && selectedFileIndex < processor.jsonFiles.size() && !processor.jsonFiles.empty()) {
            if (processor.jsonFiles[selectedFileIndex].existsAsFile() && isValidFormat(processor.jsonFiles[selectedFileIndex])) {
                processor.loadConfig(processor.jsonFiles[selectedFileIndex]);
                processor.current_model_index = selectedFileIndex;
                processor.saved_model = processor.jsonFiles[selectedFileIndex];
            }
        }
        repaint();
    }
    // You can add more conditions here if you have other ComboBoxes
    // ...
}




void ProteusAudioProcessorEditor::modelSelectChanged()
{
    const int selectedFileIndex = modelSelect.getSelectedItemIndex();
    if (selectedFileIndex >= 0 && selectedFileIndex < processor.jsonFiles.size() && processor.jsonFiles.empty() == false) { //check if correct 
        if (processor.jsonFiles[selectedFileIndex].existsAsFile() && isValidFormat(processor.jsonFiles[selectedFileIndex])) {
            processor.loadConfig(processor.jsonFiles[selectedFileIndex]);
            processor.current_model_index = selectedFileIndex;
            processor.saved_model = processor.jsonFiles[selectedFileIndex];
        }
    }
    repaint();
}

// ... (rest of your existing methods)

void ProteusAudioProcessorEditor::resetImages()
{
    repaint();
  
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
