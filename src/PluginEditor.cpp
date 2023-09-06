/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <algorithm>

// ... (other includes and namespace declarations)

ProteusAudioProcessorEditor::ProteusAudioProcessorEditor (ProteusAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
     // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    // Initialize the drive knob
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
    constrainer.setSizeLimits(1121, 326, 1168.5, 489);

    setConstrainer(&constrainer);  
   

    addAndMakeVisible(block1);
    addAndMakeVisible(block2);
    addAndMakeVisible(block3);


    // Initialize the ComboBox
    addAndMakeVisible(modelSelect);
    modelSelect.setColour(juce::Label::textColourId, juce::Colours::black);
    modelSelect.setScrollWheelEnabled(true);
    loadFromFolder();  // Load the initial list of models
    modelSelect.addListener(this);

    // ... (rest of your existing constructor code)

    

    auto font = modelLabel.getFont();
    float height = font.getHeight();
    font.setHeight(height);



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
   
    controlFlexBox.items.add(juce::FlexItem(odDriveKnob).withFlex(1));
    controlFlexBox.items.add(juce::FlexItem(odLevelKnob).withFlex(1));
  

    // Add Components to mainFlexBox
   // mainFlexBox.items.add(juce::FlexItem(loadButton).withFlex(1));
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
  
    modelSelect.addListener(this);

  
    loadFromFolder();
  
  // Start the timer to auto-refresh the dropdown every 5 seconds
    startTimer(5000);
   // Call resized() to set the initial layout
    resized();
}

ProteusAudioProcessorEditor::~ProteusAudioProcessorEditor()
{
    odDriveKnob.setLookAndFeel(nullptr);
    odLevelKnob.setLookAndFeel(nullptr);
   
}

//==============================================================================
void ProteusAudioProcessorEditor::paint(Graphics& g)
{
     // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

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

 

  // Set bounds for Load Model button (fixed size)


    // Center the Model Select dropdown
    int modelSelectWidth = 200;
    int modelSelectHeight = 30;
    int modelSelectX = blockB1.getX() + (blockB1.getWidth() - modelSelectWidth) / 2;
    int modelSelectY = blockB1.getY() + (blockB1.getHeight() - modelSelectHeight) / 2;
    modelSelect.setBounds(modelSelectX, modelSelectY, modelSelectWidth, modelSelectHeight);

  // For the knob
int knobWidth = blockA2.getWidth() - 20;
int knobHeight = blockA2.getHeight() - 20;
int knobX = blockA2.getX() + 10;  // 10 pixels from the left edge of blockA2
int knobY = blockA2.getY() + 10;  // 10 pixels from the top edge of blockA2
odDriveKnob.setBounds(knobX, knobY, knobWidth, knobHeight);



    // Set bounds for the resizable corner and border
    resizableCorner->setBounds(getWidth() - 16, getHeight() - 16, 16, 16);
    resizableBorder->setBounds(0, 0, getWidth(), getHeight());

    // Set bounds for the loaded model label
   // loadedModelLabel.setBounds(20, getHeight() - 80, 300, 30);
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
    // Clear the existing items
    modelSelect.clear();

    // Specify the folder path (this is just an example; replace with your actual path)
    juce::File folder("./models/");

    juce::Array<juce::File> modelFiles;
    folder.findChildFiles(modelFiles, juce::File::findFiles, false, "*.json");

    for (const auto& file : modelFiles)
    {
        modelSelect.addItem(file.getFileName(), modelSelect.getNumItems() + 1);
    }

    processor.model_loaded = false;

    // Get the directory where the models are stored
    File modelsDir = File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getChildFile("models");

    // Find all JSON files in the models directory
    Array<File> files = modelsDir.findChildFiles(File::findFiles, false, "*.json");

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

bool ProteusAudioProcessorEditor::loadModel(const juce::String& modelName)
{
    // Implement your logic to load the selected model
    // Return true if the model was successfully loaded, false otherwise
    return true;
}

void ProteusAudioProcessorEditor::timerCallback()
{
    // Refresh the list of models
    loadFromFolder();
}

// In your comboBoxChanged method
void ProteusAudioProcessorEditor::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &modelSelect)  // Changed from "comboBox" to "comboBoxThatHasChanged"
    {
        // Handle model selection
        juce::String selectedModel = modelSelect.getText();
        if (loadModel(selectedModel))
        {
            modelSelect.setColour(juce::ComboBox::backgroundColourId, juce::Colours::green);
        }
        else
        {
            // Reset the background color if the model couldn't be loaded
            modelSelect.setColour(juce::ComboBox::backgroundColourId, juce::Colours::white);
        }
        repaint();
    }

     if (comboBox == &modelSelect)
    {
        // Handle model selection
        juce::String selectedModel = modelSelect.getText();
        if (loadModel(selectedModel))
        {
            modelSelect.setColour(juce::ComboBox::backgroundColourId, juce::Colours::green);
        }
        else
        {
            // Reset the background color if the model couldn't be loaded
            modelSelect.setColour(juce::ComboBox::backgroundColourId, juce::Colours::white);
        }
    }
}


void ProteusAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
     if (slider == &odDriveKnob)
   
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
  
   
}
