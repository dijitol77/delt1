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
    int d = 1;
    for (const auto& jsonFile : processor.jsonFiles) {
        newModelSelect.addItem(jsonFile.getFileName(), d);
        d += 1;
    }
    newModelSelect.onChange = [this] { newModelSelectChanged(); };

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
    // Load pedal switch images
    Image cab_on = ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize);
    Image cab_off = ImageCache::getFromMemory(BinaryData::cab_switch_off_png, BinaryData::cab_switch_off_pngSize);
    cabOnButton.setImages(true, true, true, cab_on, 1.0, Colours::transparentWhite,
        cab_off, 1.0, Colours::transparentWhite,
        cab_on, 1.0, Colours::transparentWhite, 0.0);
        0.0);
    repaint();
    /*
    if (processor.fw_state == 0) {
        background_off = ImageCache::getFromMemory(BinaryData::background_off_png, BinaryData::background_off_pngSize);
        repaint();
    }
    else if (processor.fw_state == 1 && processor.conditioned == true) {
        background_on = ImageCache::getFromMemory(BinaryData::background_on_png, BinaryData::background_on_pngSize);
        repaint();
    }
    else if (processor.fw_state == 1 && processor.conditioned == false) {
        background_on_blue = ImageCache::getFromMemory(BinaryData::background_on_blue_png, BinaryData::background_on_blue_pngSize);
        repaint();
    }
    */
}

void ProteusAudioProcessorEditor::loadFromFolder()
{
    // This method is used to load the models from a folder. It first clears the current models and then scans the folder for .json files.
    // Each valid .json file is added to the model selection ComboBox.
    // If a previously saved model exists, it is loaded. Otherwise, the first model in the folder is loaded.

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
        if (processor.saved_model.existsAsFile() && isValidFormat(processor.saved_model)) {
            processor.loadConfig(processor.saved_model);
            modelSelect.setText(processor.saved_model.getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification);
        } else {
            if (!processor.jsonFiles.empty()) {
                if (processor.jsonFiles[0].existsAsFile() && isValidFormat(processor.jsonFiles[0])) {
                    processor.loadConfig(processor.jsonFiles[0]);
                    modelSelect.setText(processor.jsonFiles[0].getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification);
                }
            }
        }
    }
}

void ProteusAudioProcessorEditor::buttonClicked(Button* button)
{
    // This method handles the button clicks. In the Proteus implementation, it checks which button was clicked and calls the appropriate method.
    // For example, if the loadButton was clicked, it calls the loadButtonClicked() method.

    if (button == &loadButton) {
        loadButtonClicked();
    } else if (button == &cabOnButton) {
        cabOnButtonClicked();
    }
}

void ProteusAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    // This method handles the slider value changes. In the Proteus implementation, it checks which slider was changed and updates the corresponding parameter in the processor.

    if (slider == &ampBassKnob || slider == &ampMidKnob || slider == &ampTrebleKnob) {
        processor.set_ampEQ(ampBassKnob.getValue(), ampMidKnob.getValue(), ampTrebleKnob.getValue());
    }
}

void ProteusAudioProcessorEditor::newModelSelectChanged()
{
    // This method handles the changes in the model selection ComboBox. In the Proteus implementation, it loads the selected model and updates the GUI elements accordingly.

    const int selectedFileIndex = newModelSelect.getSelectedItemIndex();
    if (selectedFileIndex >= 0 && selectedFileIndex < processor.jsonFiles.size() && processor.jsonFiles.empty() == false) {
        if (processor.jsonFiles[selectedFileIndex].existsAsFile() && isValidFormat(processor.jsonFiles[selectedFileIndex])) {
            processor.loadConfig(processor.jsonFiles[selectedFileIndex]);
            processor.current_model_index = selectedFileIndex;
            processor.saved_model = processor.jsonFiles[selectedFileIndex];
        }
    }
    repaint();
}
