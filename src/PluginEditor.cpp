
/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ProteusAudioProcessorEditor::ProteusAudioProcessorEditor (ProteusAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to


  // Load the background image for the left container
leftBackgroundImage = ImageCache::getFromMemory(BinaryData::background_on_jpg, BinaryData::background_on_jpgSize);
leftBackground.setImage(leftBackgroundImage);
leftBackground.setBounds(leftContainer.getBounds());
leftContainer.addAndMakeVisible(leftBackground);
  leftBackground.toBack();  // Send the leftBackground to the back of the leftContainer

  

// Load the background image for the right container
rightBackgroundImage = ImageCache::getFromMemory(BinaryData::background_on_jpg, BinaryData::background_on_jpgSize);
rightBackground.setImage(rightBackgroundImage);
rightBackground.setBounds(rightContainer.getBounds());
rightContainer.addAndMakeVisible(rightBackground);
  rightBackground.toBack();  // Send the leftBackground to the back of the leftContainer


    // Overall Widgets
// Add the loadButton to the leftContainer and make it visible
leftContainer.addAndMakeVisible(loadButton);

// Set the properties for the loadButton
loadButton.setButtonText("LOAD MODEL");
loadButton.addListener(this);
loadButton.toFront(false);  // Bring the loadButton to the front of the leftContainer

// Add the modelSelect to the leftContainer and make it visible
leftContainer.addAndMakeVisible(modelSelect);

// Set the properties for the modelSelect
modelSelect.setColour(juce::Label::textColourId, juce::Colours::black);
modelSelect.setScrollWheelEnabled(true);
int c = 1;
for (const auto& jsonFile : processor.jsonFiles) {
    modelSelect.addItem(jsonFile.getFileName(), c);
    c += 1;
}
modelSelect.onChange = [this] {modelSelectChanged();};

  // Repaint the leftContainer to ensure the components are drawn correctly
leftContainer.repaint();

// Initialize and configure loadButtonRight for the right container
rightContainer.addAndMakeVisible(loadButtonRight);

// Set the properties for the loadButtonRight
loadButtonRight.setButtonText("LOAD MODEL RIGHT");
loadButtonRight.addListener(this);
loadButtonRight.toFront(false);  // Bring the loadButtonRight to the front of the rightContainer

// Add the modelSelectRight to the rightContainer and make it visible
rightContainer.addAndMakeVisible(modelSelectRight);

// Set the properties for the modelSelectRight
modelSelectRight.setColour(juce::Label::textColourId, juce::Colours::black);
modelSelectRight.setScrollWheelEnabled(true);
int cRight = 1;
for (const auto& jsonFile : processor.jsonFiles) {
    modelSelectRight.addItem(jsonFile.getFileName(), cRight);
    cRight += 1;
}
modelSelectRight.onChange = [this] { modelSelectChangedRight(); };

// Repaint the rightContainer to ensure the components are drawn correctly
rightContainer.repaint();

 // font stuff

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
    leftContainer.addAndMakeVisible(odFootSw);
    odFootSw.addListener(this);
    */

 // Left Container Widgets

// cabOnButton
cabOnButton.setImages(true, true, true,
    ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
    Image(), 1.0, Colours::transparentWhite,
    ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
    0.0);
cabOnButton.setBounds(115, 233, 53, 39);  // Set the bounds first
leftContainer.addAndMakeVisible(cabOnButton);  // Then add to the parent
cabOnButton.toFront(false);  // Finally, bring to the front
cabOnButton.addListener(this);

// odDriveKnob
driveSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, odDriveKnob);

odDriveKnob.setLookAndFeel(&bigKnobLAF);
odDriveKnob.addListener(this);
odDriveKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
odDriveKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
odDriveKnob.setDoubleClickReturnValue(true, 0.5);

// odDriveKnob.setBounds(168, 242, 190, 190);  // Set the bounds first (replace x, y, width, height with the actual values)  // Set the bounds first (replace x, y, width, height with the actual values)

leftContainer.addAndMakeVisible(odDriveKnob);  // Then add to the parent
odDriveKnob.toFront(false);  // Finally, bring to the front

// odLevelKnob
    masterSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MASTER_ID, odLevelKnob);
    leftContainer.addAndMakeVisible(odLevelKnob);
    odLevelKnob.toFront(false);
    odLevelKnob.setLookAndFeel(&smallKnobLAF);
    odLevelKnob.addListener(this);
    odLevelKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odLevelKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odLevelKnob.setDoubleClickReturnValue(true, 0.5);

// ampBassKnob
    bassSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, BASS_ID, ampBassKnob);    	    
    leftContainer.addAndMakeVisible(ampBassKnob);
    ampBassKnob.toFront(false);
    ampBassKnob.setLookAndFeel(&smallKnobLAF);
    ampBassKnob.addListener(this);
    ampBassKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampBassKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampBassKnob.setDoubleClickReturnValue(true, 0.0);

// ampMidKnob
    midSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MID_ID, ampMidKnob);    
    leftContainer.addAndMakeVisible(ampMidKnob);
    ampMidKnob.toFront(false);
    ampMidKnob.setLookAndFeel(&smallKnobLAF);
    ampMidKnob.addListener(this);
    ampMidKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampMidKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampMidKnob.setDoubleClickReturnValue(true, 0.0);

// ampTrebleKnob
    trebleSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, TREBLE_ID, ampTrebleKnob);
    leftContainer.addAndMakeVisible(ampTrebleKnob);
    ampTrebleKnob.toFront(false);
    ampTrebleKnob.setLookAndFeel(&smallKnobLAF);
    ampTrebleKnob.addListener(this);
    ampTrebleKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampTrebleKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampTrebleKnob.setDoubleClickReturnValue(true, 0.0);

// versionLabel
    leftContainer.addAndMakeVisible(versionLabel);
    versionLabel.toFront(false);
    versionLabel.setText("v1.2", juce::NotificationType::dontSendNotification);
    versionLabel.setJustificationType(juce::Justification::left);
    versionLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    versionLabel.setFont(font);

// Right Container Widgets

// odDriveKnobRight
    odDriveKnobRight.setLookAndFeel(&bigKnobLAF);
    odDriveKnobRight.addListener(this);
    odDriveKnobRight.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odDriveKnobRight.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odDriveKnobRight.setDoubleClickReturnValue(true, 0.5);
    rightContainer.addAndMakeVisible(odDriveKnobRight);
    odDriveKnobRight.toFront(false);

// Additional settings and configurations
    setSize(1000, 650);
    setResizable(true, true);
    repaint();

// Set bounds and add the left container to the main component
    addAndMakeVisible(leftContainer);
    leftContainer.setBounds(0, 0, 500, 650);

// Set bounds and add the right container to the main component
    addAndMakeVisible(rightContainer);
    rightContainer.setBounds(500, 0, 500, 650);

    leftBackground_on = ImageCache::getFromMemory(BinaryData::background_on_jpg, BinaryData::background_on_jpgSize);
    leftBackground_on_blue = ImageCache::getFromMemory(BinaryData::background_on_blue_jpg, BinaryData::background_on_blue_jpgSize);
    rightBackground_on = ImageCache::getFromMemory(BinaryData::background_on_jpg, BinaryData::background_on_jpgSize);
    rightBackground_on_blue = ImageCache::getFromMemory(BinaryData::background_on_blue_jpg, BinaryData::background_on_blue_jpgSize);

    setSize(1000, 650);  // Set initial width and height
    setResizable(true, true);

    repaint();

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

void ProteusAudioProcessorEditor::paint (Graphics& g)
{
    // Workaround for graphics on Windows builds (clipping code doesn't work correctly on Windows)
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    if (processor.fw_state == 1 && processor.conditioned == true) {
        g.drawImage(leftBackground_on, 0, 0, getWidth() / 2, getHeight(), 0, 0, leftBackground_on.getWidth(), leftBackground_on.getHeight());  // Draw for the left container
        g.drawImage(rightBackground_on, getWidth() / 2, 0, getWidth() / 2, getHeight(), 0, 0, rightBackground_on.getWidth(), rightBackground_on.getHeight());  // Draw for the right container
    } else if (processor.fw_state == 1 && processor.conditioned == false) {
        g.drawImage(leftBackground_on_blue, 0, 0, getWidth() / 2, getHeight(), 0, 0, leftBackground_on_blue.getWidth(), leftBackground_on_blue.getHeight());  // Draw for the left container
        g.drawImage(rightBackground_on_blue, getWidth() / 2, 0, getWidth() / 2, getHeight(), 0, 0, rightBackground_on_blue.getWidth(), rightBackground_on_blue.getHeight());  // Draw for the right container
    }
#else
    // Redraw only the clipped part of the background image
    juce::Rectangle<int> ClipRect = g.getClipBounds();
    if (processor.fw_state == 1 && processor.conditioned == true) {
        g.drawImage(leftBackground_on, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
        g.drawImage(rightBackground_on, ClipRect.getX() - 500, ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX() - 500, ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    } else if (processor.fw_state == 1 && processor.conditioned == false) {
        g.drawImage(leftBackground_on_blue, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
        g.drawImage(rightBackground_on_blue, ClipRect.getX() - 500, ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX() - 500, ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    }
#endif
}


void ProteusAudioProcessorEditor::resized()
{
    // Configure the mainFlexBox properties
    mainFlexBox.flexDirection = juce::FlexBox::Direction::row;

    // Configure the leftContainerFlexBox properties
    leftContainerFlexBox.flexDirection = juce::FlexBox::Direction::column;
    leftContainerFlexBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
    leftContainerFlexBox.alignItems = juce::FlexBox::AlignItems::center;

    // Configure the rightContainerFlexBox properties
    rightContainerFlexBox.flexDirection = juce::FlexBox::Direction::column;
    rightContainerFlexBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
    rightContainerFlexBox.alignItems = juce::FlexBox::AlignItems::center;

    // Add components to the leftContainerFlexBox
    leftContainerFlexBox.items.add(juce::FlexItem(leftBackground).withFlex(1.0));
    leftContainerFlexBox.items.add(juce::FlexItem(loadButton).withMargin(10).withFlex(0.1));
    leftContainerFlexBox.items.add(juce::FlexItem(modelSelect).withMargin(10).withFlex(0.1));
    leftContainerFlexBox.items.add(juce::FlexItem(versionLabel).withMargin(10).withFlex(0.1));
    leftContainerFlexBox.items.add(juce::FlexItem(cabOnButton).withMargin(10).withFlex(0.1));
    leftContainerFlexBox.items.add(juce::FlexItem(odDriveKnob).withMargin(10).withFlex(0.1));
    leftContainerFlexBox.items.add(juce::FlexItem(odLevelKnob).withMargin(10).withFlex(0.1));
    leftContainerFlexBox.items.add(juce::FlexItem(ampBassKnob).withMargin(10).withFlex(0.1));
    leftContainerFlexBox.items.add(juce::FlexItem(ampMidKnob).withMargin(10).withFlex(0.1));
    leftContainerFlexBox.items.add(juce::FlexItem(ampTrebleKnob).withMargin(10).withFlex(0.1));

    // Add components to the rightContainerFlexBox
    rightContainerFlexBox.items.add(juce::FlexItem(rightBackground).withFlex(1.0));
    rightContainerFlexBox.items.add(juce::FlexItem(odDriveKnobRight).withMargin(10).withFlex(0.1));
    rightContainerFlexBox.items.add(juce::FlexItem(loadButtonRight).withMargin(10).withFlex(0.1));
    rightContainerFlexBox.items.add(juce::FlexItem(modelSelectRight).withMargin(10).withFlex(0.1));

    // Add containers to the mainFlexBox
    juce::FlexItem leftContainerItem(leftContainer);
    leftContainerItem.withFlex(0, 1.0, leftContainer.getWidth());
    mainFlexBox.items.add(leftContainerItem);

    juce::FlexItem rightContainerItem(rightContainer);
    rightContainerItem.withFlex(0, 1.0, rightContainer.getWidth());
    mainFlexBox.items.add(rightContainerItem);

    // Perform the layout
    leftContainerFlexBox.performLayout(leftContainer.getBounds().toFloat());
    rightContainerFlexBox.performLayout(rightContainer.getBounds().toFloat());
    mainFlexBox.performLayout(getLocalBounds().toFloat());

    // Set bounds for individual components
    // left bounds
     loadButton.setBounds(186, 48, 120, 24);
    modelSelect.setBounds(52, 11, 400, 28);
    versionLabel.setBounds(462, 632, 60, 10);
    // cabOnButton.setBounds(115, 233, 53, 39);

    // Overdrive Widgets
    // odDriveKnob.setBounds(168, 242, 190, 190);
    odLevelKnob.setBounds(340, 225, 62, 62);
    
    // eq
    ampBassKnob.setBounds(113, 131, 62, 62);
    ampMidKnob.setBounds(227, 131, 62, 62);
    ampTrebleKnob.setBounds(340, 131, 62, 62);

    // right bounds
    odDriveKnobRight.setBounds(168, 242, 190, 190);
    loadButtonRight.setBounds(186, 48, 120, 24);
    modelSelectRight.setBounds(52, 11, 400, 28);

    // Set the bounds for the background images
    leftBackground.setBounds(leftContainer.getBounds());
    rightBackground.setBounds(rightContainer.getBounds());

    // Send the backgrounds to the back
    leftBackground.toBack();
    rightBackground.toBack();

    // Repaint the containers to ensure other components are drawn on top
    leftContainer.repaint();
    rightContainer.repaint();

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

void ProteusAudioProcessorEditor::loadButtonClicked()
{ 
    myChooser = std::make_unique<FileChooser> ("Select a folder to load models from",
                                               processor.folder,
                                               "*.json");
 
    auto folderChooserFlags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories | FileBrowserComponent::canSelectFiles;
 
    myChooser->launchAsync (folderChooserFlags, [this] (const FileChooser& chooser)                
    {
        if (!chooser.getResult().exists()) {
                return;
        }
        processor.model_loaded = false;
        Array<File> files;
        if (chooser.getResult().existsAsFile()) { // If a file is selected

            if (isValidFormat(chooser.getResult())) {
                processor.saved_model = chooser.getResult();
            }

            files = chooser.getResult().getParentDirectory().findChildFiles(2, false, "*.json");
            processor.folder = chooser.getResult().getParentDirectory();

        } else if (chooser.getResult().isDirectory()){ // Else folder is selected
            files = chooser.getResult().findChildFiles(2, false, "*.json");
            processor.folder = chooser.getResult();
        }
        
        processor.jsonFiles.clear();

        modelSelect.clear();

        if (files.size() > 0) {
            for (auto file : files) {

                if (isValidFormat(file)) {
                    modelSelect.addItem(file.getFileNameWithoutExtension(), processor.jsonFiles.size() + 1);
                    processor.jsonFiles.push_back(file);
                    processor.num_models += 1;
                }
            }
            if (chooser.getResult().existsAsFile()) {
                
                if (isValidFormat(chooser.getResult()) == true) {
                    modelSelect.setText(processor.saved_model.getFileNameWithoutExtension());
                    processor.loadConfig(processor.saved_model);
                }
            }
            else {
                if (!processor.jsonFiles.empty()) {
                    modelSelect.setSelectedItemIndex(0, juce::NotificationType::dontSendNotification);
                    modelSelectChanged();
                }
            }
        } else {
            processor.saved_model = ""; // Clear the saved model since there's nothing in the dropdown
        }
    });
    
}

void ProteusAudioProcessorEditor::loadButtonRightClicked()
{ 
    myChooser = std::make_unique<FileChooser> ("Select a folder to load models from",
                                               processor.folder,
                                               "*.json");
 
    auto folderChooserFlags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories | FileBrowserComponent::canSelectFiles;
 
    myChooser->launchAsync (folderChooserFlags, [this] (const FileChooser& chooser)                
    {
        if (!chooser.getResult().exists()) {
                return;
        }
        processor.model_loaded = false;
        Array<File> files;
        if (chooser.getResult().existsAsFile()) { // If a file is selected

            if (isValidFormat(chooser.getResult())) {
                processor.saved_model = chooser.getResult();
            }

            files = chooser.getResult().getParentDirectory().findChildFiles(2, false, "*.json");
            processor.folder = chooser.getResult().getParentDirectory();

        } else if (chooser.getResult().isDirectory()){ // Else folder is selected
            files = chooser.getResult().findChildFiles(2, false, "*.json");
            processor.folder = chooser.getResult();
        }
        
        processor.jsonFiles.clear();

        modelSelectRight.clear();  // Use modelSelectRight for the right container

        if (files.size() > 0) {
            for (auto file : files) {

                if (isValidFormat(file)) {
                    modelSelectRight.addItem(file.getFileNameWithoutExtension(), processor.jsonFiles.size() + 1); // Use modelSelectRight for the right container
                    processor.jsonFiles.push_back(file);
                    processor.num_models += 1;
                }
            }
            if (chooser.getResult().existsAsFile()) {
                
                if (isValidFormat(chooser.getResult()) == true) {
                    modelSelectRight.setText(processor.saved_model.getFileNameWithoutExtension()); // Use modelSelectRight for the right container
                    processor.loadConfig(processor.saved_model);
                }
            }
            else {
                if (!processor.jsonFiles.empty()) {
                    modelSelectRight.setSelectedItemIndex(0, juce::NotificationType::dontSendNotification); // Use modelSelectRight for the right container
                    modelSelectChangedRight();  // Call the function for the right container
                }
            }
        } else {
            processor.saved_model = ""; // Clear the saved model since there's nothing in the dropdown
        }
    });
  rightContainer.repaint();
}


void ProteusAudioProcessorEditor::loadFromFolder()
{
    processor.model_loaded = false;
    Array<File> files;
    files = processor.folder.findChildFiles(2, false, "*.json");

    processor.jsonFiles.clear();
    modelSelect.clear();
    modelSelectRight.clear(); // Clear the right ComboBox

    if (files.size() > 0) {
        for (auto file : files) {
            
            if (isValidFormat(file)) {
                modelSelect.addItem(file.getFileNameWithoutExtension(), processor.jsonFiles.size() + 1);
                modelSelectRight.addItem(file.getFileNameWithoutExtension(), processor.jsonFiles.size() + 1); // Add to the right ComboBox
                processor.jsonFiles.push_back(file);
                processor.num_models += 1;
            }
        }
        // Try to load model from saved_model
        if (processor.saved_model.existsAsFile() && isValidFormat(processor.saved_model)) {
            processor.loadConfig(processor.saved_model);
            modelSelect.setText(processor.saved_model.getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification);
            modelSelectRight.setText(processor.saved_model.getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification); // Set text for the right ComboBox
        } else {
            if (!processor.jsonFiles.empty()) {
                if (processor.jsonFiles[0].existsAsFile() && isValidFormat(processor.jsonFiles[0])) {
                    processor.loadConfig(processor.jsonFiles[0]);
                    modelSelect.setText(processor.jsonFiles[0].getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification);
                    modelSelectRight.setText(processor.jsonFiles[0].getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification); // Set text for the right ComboBox
                }
            }
        }
    }
}



void ProteusAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &loadButton) {
        loadButtonClicked();
    } 
    else if (button == &loadButtonRight) {
        loadButtonRightClicked();
    } 
    else if (button == &cabOnButton) {
        cabOnButtonClicked();
    }
    // Add more conditions here for other buttons as needed
}


void ProteusAudioProcessorEditor::odFootSwClicked() {
    //if (processor.fw_state == 0)
    //    processor.fw_state = 1;
    //else
    //    processor.fw_state = 0;
    //resetImages();
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

void ProteusAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    // Amp
    if (slider == &ampBassKnob || slider == &ampMidKnob || slider == &ampTrebleKnob) {
        processor.set_ampEQ(ampBassKnob.getValue(), ampMidKnob.getValue(), ampTrebleKnob.getValue());
    }
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

void ProteusAudioProcessorEditor::modelSelectChangedRight()
{
    const int selectedFileIndex = modelSelectRight.getSelectedItemIndex();
    if (selectedFileIndex >= 0 && selectedFileIndex < processor.jsonFiles.size() && processor.jsonFiles.empty() == false) {
        if (processor.jsonFiles[selectedFileIndex].existsAsFile() && isValidFormat(processor.jsonFiles[selectedFileIndex])) {
            processor.loadConfig(processor.jsonFiles[selectedFileIndex]);
            // You can add additional logic here if needed for the right container
        }
    }
    repaint();
}


void ProteusAudioProcessorEditor::resetImages()
{
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
