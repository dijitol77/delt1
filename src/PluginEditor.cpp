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

  File imageFile2 = File::getCurrentWorkingDirectory().getChildFile("Resources/BACK2.jpg");
  background2 = ImageFileFormat::loadFrom(imageFile2);
  
    // === END OF UPDATES ===
 
    // Size of plugin GUI
    setSize(500, 650);

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
        g.drawImageWithin(background2, 0, 0, getWidth(), getHeight(), RectanglePlacement::stretchToFit, false);
    } else if (processor.fw_state == 1 && processor.conditioned == false) {
        g.drawImageWithin(background_on_blue, 0, 0, getWidth(), getHeight(), RectanglePlacement::stretchToFit, false);
    }
#else
// Redraw only the clipped part of the background image

    juce::Rectangle<int> ClipRect = g.getClipBounds();
    //if (processor.fw_state == 0) {
    //    g.drawImage(background_off, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    if (processor.fw_state == 1 && processor.conditioned == true) {
        g.drawImage(background2, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    } else if (processor.fw_state == 1 && processor.conditioned == false)
        g.drawImage(background_on_blue, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
#endif
  // Add the resizable corner and set its constrainer
   // addAndMakeVisible(resizableCorner);
   // addAndMakeVisible(resizableBorder);  // Add this line
   // constrainer.setSizeLimits(500, 650, 2000, 1300);  // Set min and max sizes
}

// In your resized() method

void ProteusAudioProcessorEditor::resized()
{
    // Get the total area available
    Rectangle<int> totalArea = getLocalBounds();

    // Divide the total area into top, middle, and bottom areas
    auto topArea = totalArea.removeFromTop(totalArea.getHeight() / 3);
    auto middleArea = totalArea.removeFromTop(totalArea.getHeight() / 2);
    auto bottomArea = totalArea;

    // Top Container FlexBox for Cab Switch, Load Model button, and Model Select dropdown
    FlexBox topFlexBox;
    topFlexBox.flexDirection = FlexBox::Direction::row;
    topFlexBox.justifyContent = FlexBox::JustifyContent::spaceBetween;
    topFlexBox.items.add(FlexItem().withFlex(1));  // Placeholder for loadButton
    topFlexBox.items.add(FlexItem().withFlex(1));  // Placeholder for modelSelect
    topFlexBox.items.add(FlexItem(cabOnButton).withFlex(1));
    topFlexBox.performLayout(topArea.toFloat());

    // Explicitly set the bounds for Load Model button and Model Select dropdown
    loadButton.setBounds(20, 20, 100, 30);  // Top left
    modelSelect.setBounds(130, 20, 200, 30);  // Top left

    // Explicitly set the bounds for Cab Switch to stay top right
    cabOnButton.setBounds(getWidth() - 70, 20, 50, 50);  // Top right

    // Middle Container FlexBox for Gain
    FlexBox middleFlexBox;
    middleFlexBox.flexDirection = FlexBox::Direction::row;
    middleFlexBox.justifyContent = FlexBox::JustifyContent::center;
    middleFlexBox.items.add(FlexItem(odDriveKnob).withFlex(1));
    middleFlexBox.performLayout(middleArea.toFloat());

   // Divide the bottom area into three blocks
    auto block1Area = bottomArea.removeFromLeft(bottomArea.getWidth() / 3);
    auto block2Area = bottomArea.removeFromLeft(bottomArea.getWidth() / 2);
    auto block3Area = bottomArea;

    // Layout for Block 1
    block1.setBounds(block1Area);

    // Layout for Block 2
    block2.setBounds(block2Area);

    // Layout for Block 3
    block3.setBounds(block3Area);

   // Bottom Container FlexBox for EQ, Level, and Gain in block1Area
    FlexBox bottomFlexBox;
    bottomFlexBox.flexDirection = FlexBox::Direction::row;
    bottomFlexBox.justifyContent = FlexBox::JustifyContent::spaceAround;
    bottomFlexBox.items.add(FlexItem(ampBassKnob).withFlex(1));
    bottomFlexBox.items.add(FlexItem(ampMidKnob).withFlex(1));
    bottomFlexBox.items.add(FlexItem(ampTrebleKnob).withFlex(1));
    bottomFlexBox.items.add(FlexItem(odLevelKnob).withFlex(1));
    bottomFlexBox.items.add(FlexItem(odDriveKnob).withFlex(1));  // Add the gain dial
    bottomFlexBox.performLayout(block1Area.toFloat());  // Layout only in block1Area
  
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
