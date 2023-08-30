/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

ProteusAudioProcessorEditor::ProteusAudioProcessorEditor (ProteusAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), block1(/* constructor arguments, if any */)
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


 
   // Debugging for Load Model Button
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("LOAD MODEL");
    loadButton.addListener(this);
    loadButton.toFront(true);
    loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    loadButton.setBounds(20, getHeight() - 50, 100, 30);
    loadButton.repaint();

  
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
   cabOnButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green); // Change color for visibility
   cabOnButton.repaint();

 // addAndMakeVisible(loadedModelLabel);
 // loadedModelLabel.setText("No Model Loaded", juce::NotificationType::dontSendNotification);
 // loadedModelLabel.setJustificationType(juce::Justification::centred);

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
  
  bool showEQ = false; // Set this to true if you want to show the EQ, false to hide it

if (showEQ) {
    bassSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, BASS_ID, ampBassKnob);
    midSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MID_ID, ampMidKnob);
    trebleSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, TREBLE_ID, ampTrebleKnob);
    
    addAndMakeVisible(ampBassKnob);
    addAndMakeVisible(ampMidKnob);
    addAndMakeVisible(ampTrebleKnob);
    
    // ... (other knob settings)
} else {
    bassSliderAttach.reset();
    midSliderAttach.reset();
    trebleSliderAttach.reset();
    
    ampBassKnob.setVisible(false);
    ampMidKnob.setVisible(false);
    ampTrebleKnob.setVisible(false);
}



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
    mainFlexBox.items.add(juce::FlexItem(loadButton).withFlex(1));
    mainFlexBox.items.add(juce::FlexItem(controlFlexBox).withFlex(4));

 // Remove these lines
// File imageFile2 = File::getCurrentWorkingDirectory().getChildFile("resources/BACK2.jpg");
// background2 = ImageFileFormat::loadFrom(imageFile2);

// Use this line to load the image from binary data
background2 = ImageCache::getFromMemory(BinaryData::BACK2_jpg, BinaryData::BACK2_jpgSize);

// Rest of your constructor code
  
  
    // === END OF UPDATES ===
 
    // Size of plugin GUI
    setSize(1121, 326); 

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
    // Get the total area available
    Rectangle<int> totalArea = getLocalBounds();

    // Divide the total area into three columns: A, B, and C
    auto colA = totalArea.removeFromLeft(totalArea.getWidth() / 3);
    auto colB = totalArea.removeFromLeft(totalArea.getWidth() / 2);
    auto colC = totalArea;

    // Divide each column into three blocks: 1, 2, and 3
    auto blockA1 = colA.removeFromTop(colA.getHeight() / 3);
    auto blockA2 = colA.removeFromTop(colA.getHeight() / 2);
    auto blockA3 = colA;

    auto blockB1 = colB.removeFromTop(colB.getHeight() / 3);
    auto blockB2 = colB.removeFromTop(colB.getHeight() / 2);
    auto blockB3 = colB;

    auto blockC1 = colC.removeFromTop(colC.getHeight() / 3);
    auto blockC2 = colC.removeFromTop(colC.getHeight() / 2);
    auto blockC3 = colC;

    // Explicitly set the bounds for Load Model button and Model Select dropdown
    loadButton.setBounds(blockA1.getX() + 10, blockA1.getY() + 10, 100, 30);
  
int modelSelectWidth = 200;  // Set the width of the modelSelect
int modelSelectHeight = 30;  // Set the height of the modelSelect

int modelSelectX = blockB1.getX() + (blockB1.getWidth() - modelSelectWidth) / 2;  // Center the modelSelect horizontally within blockB3
int modelSelectY = blockB1.getY() + 10;  // Align to the top of blockB3 with a small margin

modelSelect.setBounds(modelSelectX, modelSelectY, modelSelectWidth, modelSelectHeight);


 // Recalculate blockA2's dimensions
    auto rowA = totalArea.removeFromTop(totalArea.getHeight() / 3);
    auto blockA1 = rowA.removeFromLeft(rowA.getWidth() / 3);
    auto blockA2 = rowA.removeFromLeft(rowA.getWidth() / 2);
    auto blockA3 = rowA;

    // Set the knob's dimensions relative to blockA2
    int knobWidth = blockA2.getWidth() * 0.8;  // 80% of blockA2's width
    int knobHeight = blockA2.getHeight() * 0.8;  // 80% of blockA2's height

    // Set the knob's position relative to blockA2
    int knobX = blockA2.getX() + blockA2.getWidth() - knobWidth - 10;  // 10 pixels from the right edge of blockA2
    int knobY = blockA2.getY() + (blockA2.getHeight() - knobHeight) / 2;  // Vertically centered in blockA2

    // Update the knob's bounds
    odDriveKnob.setBounds(knobX, knobY, knobWidth, knobHeight);





  // Explicitly set the bounds for the switch
    int switchWidth = 45;  // Set the width of the switch
    int switchHeight = 45;  // Set the height of the switch
    int switchX = blockC1.getX() + (blockC1.getWidth() - switchWidth) / 2;  // Center the switch horizontally within blockC1
    int switchY = blockC1.getY() + (blockC1.getHeight() - switchHeight) / 2;  // Center the switch vertically within blockC1
    cabOnButton.setBounds(switchX, switchY, switchWidth, switchHeight);


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

void ProteusAudioProcessorEditor::loadButtonClicked()
{ 
    DBG("loadButtonClicked() called");  // Debugging Step: Log when the function is called

    myChooser = std::make_unique<FileChooser> ("Select a folder to load models from",
                                               processor.folder,
                                               "*.json");
 
    auto folderChooserFlags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories | FileBrowserComponent::canSelectFiles;
 
    myChooser->launchAsync (folderChooserFlags, [this] (const FileChooser& chooser)                
    {
        DBG("Inside launchAsync()");  // Debugging Step: Log when inside the launchAsync()

        if (!chooser.getResult().exists()) {
                DBG("No result exists");  // Debugging Step: Log when no result exists
                return;
        }

        processor.model_loaded = false;
        Array<File> files;

        if (chooser.getResult().existsAsFile()) { // If a file is selected
            DBG("File selected");  // Debugging Step: Log when a file is selected

            if (isValidFormat(chooser.getResult())) {
                processor.saved_model = chooser.getResult();
            }

            files = chooser.getResult().getParentDirectory().findChildFiles(2, false, "*.json");
            processor.folder = chooser.getResult().getParentDirectory();

        } else if (chooser.getResult().isDirectory()){ // Else folder is selected
            DBG("Directory selected");  // Debugging Step: Log when a directory is selected
            files = chooser.getResult().findChildFiles(2, false, "*.json");
            processor.folder = chooser.getResult();
        }
        
        processor.jsonFiles.clear();
        modelSelect.clear();

        if (files.size() > 0) {
            DBG("Files found");  // Debugging Step: Log when files are found
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
            DBG("No valid files found");  // Debugging Step: Log when no valid files are found
            processor.saved_model = ""; // Clear the saved model since there's nothing in the dropdown
        }
    });
}


void ProteusAudioProcessorEditor::loadFromFolder()
{
    processor.model_loaded = false;
    Array<File> files;
    files = processor.folder.findChildFiles(2, false, "*.json");

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
        // Try to load model from saved_model, if it doesnt exist and jsonFiles is not empty, load the first model (if it exists and is valid format)
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


void ProteusAudioProcessorEditor::buttonClicked(juce::Button* button)
{
 
    if (button == &loadButton) {
        loadButtonClicked();
    } else if (button == &cabOnButton) {
        cabOnButtonClicked();
    }
}

void ProteusAudioProcessorEditor::odFootSwClicked() {
 
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
    if (ampBassKnob.isVisible() && ampMidKnob.isVisible() && ampTrebleKnob.isVisible()) {
        if (slider == &ampBassKnob || slider == &ampMidKnob || slider == &ampTrebleKnob) {
            processor.set_ampEQ(ampBassKnob.getValue(), ampMidKnob.getValue(), ampTrebleKnob.getValue());
        }
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
