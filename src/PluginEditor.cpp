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

    // Overall Widgets
  
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("LOAD MODEL");
    loadButton.addListener(this);

  addAndMakeVisible(loadButton2);
  loadButton2.setButtonText("LOAD MODEL");
  loadButton2.addListener(this);

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

   // Size of plugin GUI
    setSize (1000, 650);




     cabOnButton2.setImages(true, true, true,
        ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
        Image(), 1.0, Colours::transparentWhite,
        ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
        0.0);
    addAndMakeVisible(cabOnButton2);
    cabOnButton2.addListener(this);

    driveSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, odDriveKnob);
    addAndMakeVisible(odDriveKnob);
    odDriveKnob2.setLookAndFeel(&bigKnobLAF);
    odDriveKnob2.addListener(this);
    odDriveKnob2.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odDriveKnob2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odDriveKnob2.setDoubleClickReturnValue(true, 0.5);

    masterSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MASTER_ID, odLevelKnob);
    addAndMakeVisible(odLevelKnob);
    odLevelKnob2.setLookAndFeel(&smallKnobLAF);
    odLevelKnob2.addListener(this);
    odLevelKnob2.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odLevelKnob2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odLevelKnob2.setDoubleClickReturnValue(true, 0.5);

    bassSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, BASS_ID, ampBassKnob);    	    
    addAndMakeVisible(ampBassKnob);
    ampBassKnob2.setLookAndFeel(&smallKnobLAF);
    ampBassKnob2.addListener(this);
    ampBassKnob2.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampBassKnob2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampBassKnob2.setDoubleClickReturnValue(true, 0.0);

    midSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MID_ID, ampMidKnob);    
    addAndMakeVisible(ampMidKnob);
    ampMidKnob2.setLookAndFeel(&smallKnobLAF);
    ampMidKnob2.addListener(this);
    ampMidKnob2.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampMidKnob2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampMidKnob2.setDoubleClickReturnValue(true, 0.0);

    trebleSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, TREBLE_ID, ampTrebleKnob);
    addAndMakeVisible(ampTrebleKnob);
    ampTrebleKnob2.setLookAndFeel(&smallKnobLAF);
    ampTrebleKnob2.addListener(this);
    ampTrebleKnob2.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampTrebleKnob2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampTrebleKnob2.setDoubleClickReturnValue(true, 0.0);

    addAndMakeVisible(versionLabel);
versionLabel2.setText("v1.2", juce::NotificationType::dontSendNotification);
versionLabel2.setJustificationType(juce::Justification::left);
versionLabel2.setColour(juce::Label::textColourId, juce::Colours::white);
versionLabel2.setFont(font);

  // Inside the ProteusAudioProcessorEditor::ProteusAudioProcessorEditor() constructor in PluginEditor.cpp

// ... [Other initialization code]

// Duplicated Components Initialization:

// 1. loadButton2
loadButton2.setBounds(520, 10, 80, 30);
loadButton2.setButtonText("Load");
duplicateContainer.addAndMakeVisible(loadButton2);  // Add the button to the duplicateContainer

// 2. modelLabel2
modelLabel2.setBounds(520, 50, 100, 20);
modelLabel2.setText("Model:", dontSendNotification);
duplicateContainer.addAndMakeVisible(modelLabel2);

// 3. versionLabel2
versionLabel2.setBounds(520, 80, 100, 20);
versionLabel2.setText("Version:", dontSendNotification);
duplicateContainer.addAndMakeVisible(versionLabel2);

// 4. modelSelect2
modelSelect2.setBounds(520, 110, 150, 30);
// Add items to the combo box if needed
duplicateContainer.addAndMakeVisible(modelSelect2);

// 5. ampBassKnob2
ampBassKnob2.setBounds(520, 150, 60, 60);
// Set properties like slider style, range, and initial value here
duplicateContainer.addAndMakeVisible(ampBassKnob2);

// 6. ampMidKnob2
ampMidKnob2.setBounds(590, 150, 60, 60);
// Set properties like slider style, range, and initial value here
duplicateContainer.addAndMakeVisible(ampMidKnob2);

// 7. ampTrebleKnob2
ampTrebleKnob2.setBounds(660, 150, 60, 60);
// Set properties like slider style, range, and initial value here
duplicateContainer.addAndMakeVisible(ampTrebleKnob2);

// 8. odDriveKnob2
odDriveKnob2.setBounds(520, 220, 60, 60);
// Set properties like slider style, range, and initial value here
duplicateContainer.addAndMakeVisible(odDriveKnob2);

// 9. odLevelKnob2
odLevelKnob2.setBounds(590, 220, 60, 60);
// Set properties like slider style, range, and initial value here
duplicateContainer.addAndMakeVisible(odLevelKnob2);

// 10. cabOnButton2
cabOnButton2.setBounds(520, 290, 60, 60);
// Set properties like button image, toggle state, etc. here
duplicateContainer.addAndMakeVisible(cabOnButton2);

// ... [Rest of the constructor code]


    resetImages();

    loadFromFolder();
}

// ... [Rest of the file remains unchanged]


ProteusAudioProcessorEditor::~ProteusAudioProcessorEditor()
{
    odDriveKnob.setLookAndFeel(nullptr);
    odLevelKnob.setLookAndFeel(nullptr);
    ampBassKnob.setLookAndFeel(nullptr);
    ampMidKnob.setLookAndFeel(nullptr);
    ampTrebleKnob.setLookAndFeel(nullptr);


     odDriveKnob2.setLookAndFeel(nullptr);
    odLevelKnob2.setLookAndFeel(nullptr);
    ampBassKnob2.setLookAndFeel(nullptr);
    ampMidKnob2.setLookAndFeel(nullptr);
    ampTrebleKnob2.setLookAndFeel(nullptr);
}

void ProteusAudioProcessorEditor::paint (Graphics& g)
{
    // Workaround for graphics on Windows builds (clipping code doesn't work correctly on Windows)
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    // Draw the background first
    if (processor.fw_state == 1 && processor.conditioned == true) {
        g.drawImageAt(background_on, 0, 0);  // Debug Line: Redraw entire background image
    } else if (processor.fw_state == 1 && processor.conditioned == false) {
        g.drawImageAt(background_on_blue, 0, 0);  // Debug Line: Redraw entire background image
    }

    // Draw the background for the duplicate container
    g.setOrigin(500, 0);  // Shift the origin to the start of the duplicate container
    g.drawImageAt(background_on, 0, 0);  // Draw the different background image

    // Redraw only the clipped part of the background image
    juce::Rectangle<int> ClipRect = g.getClipBounds();
    if (processor.fw_state == 1 && processor.conditioned == true) {
        g.drawImage(background_on, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    } else if (processor.fw_state == 1 && processor.conditioned == false) {
        g.drawImage(background_on_blue, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    }
#endif

void ProteusAudioProcessorEditor::resized()
{
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

  // Size of plugin GUI
    setSize (1000, 650);  // Double the width

   // Position the containers
    originalContainer.setBounds(0, 0, 500, 650);
    duplicateContainer.setBounds(500, 0, getWidth() - 500, getHeight());

    // Add and make visible the duplicate container
    addAndMakeVisible(duplicateContainer);

     //Overall Widgets2
    loadButton2.setBounds(186, 48, 120, 24);
    modelSelect2.setBounds(52, 11, 400, 28);
    //modelLabel.setBounds(197, 2, 90, 25);
    versionLabel2.setBounds(462, 632, 60, 10);
    cabOnButton2.setBounds(115, 233, 53, 39);

    // Overdrive Widgets2
    odDriveKnob2.setBounds(168, 242, 190, 190);
    odLevelKnob2.setBounds(340, 225, 62, 62);
    //odFootSw.setBounds(185, 416, 175, 160);

    ampBassKnob2.setBounds(113, 131, 62, 62);
    ampMidKnob2.setBounds(227, 131, 62, 62);
    ampTrebleKnob2.setBounds(340, 131, 62, 62);

   // Bring the duplicate container to the front and repaint
    duplicateContainer.toFront(false);
    duplicateContainer.repaint();
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
    //if (button == &odFootSw) {
    //    odFootSwClicked();
    if (button == &loadButton) {
        loadButtonClicked();
    } else if (button == &cabOnButton) {
        cabOnButtonClicked();
    }
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
