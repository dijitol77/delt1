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
    : AudioProcessorEditor (&p), audioProcessor (p), font1(15.0f), font2(15.0f)
{

// Container 1 widgets
    addAndMakeVisible(loadButton1);
    loadButton1.setButtonText("LOAD MODEL");
    loadButton1.addListener(this);

    addAndMakeVisible(modelSelect1);
    modelSelect1.setColour(juce::Label::textColourId, juce::Colours::black);
    modelSelect1.setScrollWheelEnabled(true);
    int c1 = 1;  // Renamed to c1
    for (const auto& jsonFile : processor.jsonFiles) {
        modelSelect1.addItem(jsonFile.getFileName(), c1);
        c1 += 1;
    }
    modelSelect1.onChange = [this] {modelSelect1Changed();};

    auto font1 = modelLabel1.getFont();  // Renamed to font1
    float height1 = font1.getHeight();  // Renamed to height1
    font1.setHeight(height1);
// Container 2 widgets
     addAndMakeVisible(loadButton2);
    loadButton2.setButtonText("LOAD MODEL");
    loadButton2.addListener(this);

    addAndMakeVisible(modelSelect2);
    modelSelect2.setColour(juce::Label::textColourId, juce::Colours::black);
    modelSelect2.setScrollWheelEnabled(true);
    int c2 = 1;  // Renamed to c2
    for (const auto& jsonFile : processor.jsonFiles) {
        modelSelect2.addItem(jsonFile.getFileName(), c2);  // Changed to modelSelect2
        c2 += 1;
    }
    modelSelect2.onChange = [this] {modelSelect2Changed();};  // Changed to modelSelect2
auto font2 = modelLabel2.getFont();  // Renamed to font2
    float height2 = font2.getHeight();  // Renamed to height2
    font2.setHeight(height2);
// currently for both
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
// Container 1 
// cab 1

    cabOnButton1.setImages(true, true, true,
        ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
        Image(), 1.0, Colours::transparentWhite,
        ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
        0.0);
    addAndMakeVisible(cabOnButton1);
    cabOnButton1.addListener(this);

// odDriveKnob1
    driveSlider1Attach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, odDriveKnob);
    addAndMakeVisible(odDriveKnob);
    odDriveKnob1.setLookAndFeel(&bigKnobLAF);
    odDriveKnob1.addListener(this);
    odDriveKnob1.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odDriveKnob1.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odDriveKnob1.setDoubleClickReturnValue(true, 0.5);
// odLevelKnob1
    masterSlider1Attach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MASTER1_ID, odLevelKnob1);
    addAndMakeVisible(odLevelKnob1);
    odLevelKnob1.setLookAndFeel(&smallKnobLAF);
    odLevelKnob1.addListener(this);
    odLevelKnob1.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odLevelKnob1.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odLevelKnob1.setDoubleClickReturnValue(true, 0.5);
// ampBassKnob
    bassSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, BASS_ID, ampBassKnob);    	    
    addAndMakeVisible(ampBassKnob1);
    ampBassKnob.setLookAndFeel(&smallKnobLAF);
    ampBassKnob.addListener(this);
    ampBassKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampBassKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampBassKnob.setDoubleClickReturnValue(true, 0.0);
// ampMidKnob
    midSlider1Attach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MID_ID, ampMidKnob);    
    addAndMakeVisible(ampMidKnob1);
    ampMidKnob.setLookAndFeel(&smallKnobLAF);
    ampMidKnob.addListener(this);
    ampMidKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampMidKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampMidKnob.setDoubleClickReturnValue(true, 0.0);
// ampTrebleKnob
    trebleSlider1Attach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, TREBLE_ID, ampTrebleKnob);
    addAndMakeVisible(ampTrebleKnob);
    ampTrebleKnob.setLookAndFeel(&smallKnobLAF);
    ampTrebleKnob.addListener(this);
    ampTrebleKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    ampTrebleKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    ampTrebleKnob.setDoubleClickReturnValue(true, 0.0);
// versionLabel1
    addAndMakeVisible(versionLabel1);
    versionLabel1.setText("v1.2", juce::NotificationType::dontSendNotification);
    versionLabel1.setJustificationType(juce::Justification::left);
    versionLabel1.setColour(juce::Label::textColourId, juce::Colours::white);
    versionLabel1.setFont(font1);
//

// Container 2 
// cab2  
    cabOnButton2.setImages(true, true, true,
        ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
        Image(), 1.0, Colours::transparentWhite,
        ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
        0.0);
    addAndMakeVisible(cabOnButton2);
    cabOnButton2.addListener(this);
// odDriveKnob2
    driveSlider2Attach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN2_ID, odDriveKnob2);
    addAndMakeVisible(odDriveKnob2);
    odDriveKnob2.setLookAndFeel(&bigKnobLAF);
    odDriveKnob2.addListener(this);
    odDriveKnob2.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odDriveKnob2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odDriveKnob2.setDoubleClickReturnValue(true, 0.5);
// odLevelKnob2
    masterSlider2Attach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MASTER2_ID, odLevelKnob2);
    addAndMakeVisible(odLevelKnob2);
    odLevelKnob2.setLookAndFeel(&smallKnobLAF);
    odLevelKnob2.addListener(this);
    odLevelKnob2.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odLevelKnob2.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odLevelKnob2.setDoubleClickReturnValue(true, 0.5);


// no second eq //


// versionLabel2
    addAndMakeVisible(versionLabel2);
    versionLabel2.setText("v1.2", juce::NotificationType::dontSendNotification);
    versionLabel2.setJustificationType(juce::Justification::left);
    versionLabel2.setColour(juce::Label::textColourId, juce::Colours::white);
    versionLabel2.setFont(font2);

// Add and make visible the duplicate container
    addAndMakeVisible(duplicateContainer);

// Size of plugin GUI
    setSize (1000, 650);
    resetImages();

    loadFromFolder();
}

ProteusAudioProcessorEditor::~ProteusAudioProcessorEditor()
{
    
    odDriveKnob1.setLookAndFeel(nullptr);
    odLevelKnob1.setLookAndFeel(nullptr);
    ampBassKnob1.setLookAndFeel(nullptr);
    ampMidKnob1.setLookAndFeel(nullptr);
    ampTrebleKnob1.setLookAndFeel(nullptr);

    odDriveKnob2.setLookAndFeel(nullptr);
    odLevelKnob2.setLookAndFeel(nullptr);
    
}

//==============================================================================
void ProteusAudioProcessorEditor::paint (Graphics& g)
{
    // Workaround for graphics on Windows builds (clipping code doesn't work correctly on Windows)
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    //if (processor.fw_state == 0) {
    //    g.drawImageAt(background_off, 0, 0);  // Debug Line: Redraw entire background image
    if (processor.fw_state == 1 && processor.conditioned == true) {
        g.drawImageAt(background_on, 0, 0);  // Debug Line: Redraw entire background image
    } else if (processor.fw_state == 1 && processor.conditioned == false) {
        g.drawImageAt(background_on_blue, 0, 0);  // Debug Line: Redraw entire background image
    }
#else
// Redraw only the clipped part of the background image

    juce::Rectangle<int> ClipRect = g.getClipBounds();
    //if (processor.fw_state == 0) {
    //    g.drawImage(background_off, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    if (processor.fw_state == 1 && processor.conditioned == true) {
        g.drawImage(background_on, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    } else if (processor.fw_state == 1 && processor.conditioned == false)
        g.drawImage(background_on_blue, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
#endif
}

void ProteusAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

//Overall Widgets 1
    loadButton1.setBounds(186, 48, 120, 24);
    modelSelect1.setBounds(52, 11, 400, 28);
    //modelLabel.setBounds(197, 2, 90, 25);
    versionLabel1.setBounds(462, 632, 60, 10);
    cabOnButton1.setBounds(115, 233, 53, 39);

    // Overdrive Widgets
    odDriveKnob1.setBounds(168, 242, 190, 190);
    odLevelKnob1.setBounds(340, 225, 62, 62);
    //odFootSw.setBounds(185, 416, 175, 160);

    ampBassKnob1.setBounds(113, 131, 62, 62);
    ampMidKnob1.setBounds(227, 131, 62, 62);
    ampTrebleKnob1.setBounds(340, 131, 62, 62);


// Position the containers
    originalContainer.setBounds(0, 0, 500, 650);
    duplicateContainer.setBounds(500, 0, getWidth() - 500, getHeight());

// Add and make visible the duplicate container
    addAndMakeVisible(duplicateContainer);

//Overall Widgets 2
    loadButton2.setBounds(186, 48, 120, 24);
    modelSelect2.setBounds(52, 11, 400, 28);
    //modelLabel.setBounds(197, 2, 90, 25);
    versionLabe2.setBounds(462, 632, 60, 10);
    cabOnButton2.setBounds(115, 233, 53, 39);

    // Overdrive Widgets
    odDriveKnob2.setBounds(168, 242, 190, 190);
    odLevelKnob2.setBounds(340, 225, 62, 62);
    //odFootSw.setBounds(185, 416, 175, 160);




// Bring the duplicate container to the front and repaint
    duplicateContainer.toFront(false);
    duplicateContainer.repaint();
}

// is valid
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

void ProteusAudioProcessorEditor::loadButton1Clicked()
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

        modelSelect1.clear();

        if (files.size() > 0) {
            for (auto file : files) {

                if (isValidFormat(file)) {
                    modelSelect1.addItem(file.getFileNameWithoutExtension(), processor.jsonFiles.size() + 1);
                    processor.jsonFiles.push_back(file);
                    processor.num_models += 1;
                }
            }
            if (chooser.getResult().existsAsFile()) {
                
                if (isValidFormat(chooser.getResult()) == true) {
                    modelSelect1.setText(processor.saved_model.getFileNameWithoutExtension());
                    processor.loadConfig(processor.saved_model);
                }
            }
            else {
                if (!processor.jsonFiles.empty()) {
                    modelSelect1.setSelectedItemIndex(0, juce::NotificationType::dontSendNotification);
                    modelSelect1Changed();
                }
            }
        } else {
            processor.saved_model = ""; // Clear the saved model since there's nothing in the dropdown
        }

    });
    
}

void ProteusAudioProcessorEditor::loadButton2Clicked()
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

        modelSelect1.clear();

        if (files.size() > 0) {
            for (auto file : files) {

                if (isValidFormat(file)) {
                    modelSelect2.addItem(file.getFileNameWithoutExtension(), processor.jsonFiles.size() + 1);
                    processor.jsonFiles.push_back(file);
                    processor.num_models += 1;
                }
            }
            if (chooser.getResult().existsAsFile()) {
                
                if (isValidFormat(chooser.getResult()) == true) {
                    modelSelect2.setText(processor.saved_model.getFileNameWithoutExtension());
                    processor.loadConfig(processor.saved_model);
                }
            }
            else {
                if (!processor.jsonFiles.empty()) {
                    modelSelect2.setSelectedItemIndex(0, juce::NotificationType::dontSendNotification);
                    modelSelect1Changed();
                }
            }
        } else {
            processor.saved_model = ""; // Clear the saved model since there's nothing in the dropdown
        }

    });
    
}

// load from folder 1
void ProteusAudioProcessorEditor::loadFromFolder1()
{
    processor.model_loaded = false;
    Array<File> files;
    files = processor.folder.findChildFiles(2, false, "*.json");

    processor.jsonFiles.clear();
    modelSelect1.clear();

    if (files.size() > 0) {
        for (auto file : files) {
            
            if (isValidFormat(file)) {
                modelSelect1.addItem(file.getFileNameWithoutExtension(), processor.jsonFiles.size() + 1);
                processor.jsonFiles.push_back(file);
                processor.num_models += 1;
            }
        }
        // Try to load model from saved_model, if it doesnt exist and jsonFiles is not empty, load the first model (if it exists and is valid format)
        if (!processor.jsonFiles.empty()) {
            if (processor.saved_model.existsAsFile() && isValidFormat(processor.saved_model)) {
                processor.loadConfig(processor.saved_model);
                modelSelect1.setText(processor.saved_model.getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification);
            } else {
                if (processor.jsonFiles[0].existsAsFile() && isValidFormat(processor.jsonFiles[0])) {
                    processor.loadConfig(processor.jsonFiles[0]);
                    modelSelect1.setText(processor.jsonFiles[0].getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification);
                }
            }
        }
    }
 // load button 2   
}
// load from folder 1
void ProteusAudioProcessorEditor::loadFromFolder2()
{
    processor.model_loaded = false;
    Array<File> files;
    files = processor.folder.findChildFiles(2, false, "*.json");

    processor.jsonFiles.clear();
    modelSelect2.clear();

    if (files.size() > 0) {
        for (auto file : files) {
            
            if (isValidFormat(file)) {
                modelSelect2.addItem(file.getFileNameWithoutExtension(), processor.jsonFiles.size() + 1);
                processor.jsonFiles.push_back(file);
                processor.num_models += 1;
            }
        }
        // Try to load model from saved_model, if it doesnt exist and jsonFiles is not empty, load the first model (if it exists and is valid format)
        if (!processor.jsonFiles.empty()) {
            if (processor.saved_model.existsAsFile() && isValidFormat(processor.saved_model)) {
                processor.loadConfig(processor.saved_model);
                modelSelect2.setText(processor.saved_model.getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification);
            } else {
                if (processor.jsonFiles[0].existsAsFile() && isValidFormat(processor.jsonFiles[0])) {
                    processor.loadConfig(processor.jsonFiles[0]);
                    modelSelect2.setText(processor.jsonFiles[0].getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification);
                }
            }
        }
    }
 // load button 2   
}


// buttonClicked1
void ProteusAudioProcessorEditor::button1Clicked(juce::Button* button)
{
    //if (button == &odFootSw) {
    //    odFootSwClicked();
    if (button == &loadButton1) {
        loadButton1Clicked();
    } else if (button == &cabOnButton1) {
        cabOnButton1Clicked();
    }

}
// buttonClicked2
void ProteusAudioProcessorEditor::button2Clicked(juce::Button* button)
{
    //if (button == &odFootSw) {
    //    odFootSwClicked();
    if (button == &loadButton2) {
        loadButton2Clicked();
    } else if (button == &cabOnButton2) {
        cabOnButton2Clicked();
    }

}

void ProteusAudioProcessorEditor::odFootSw1Clicked() 
{
    //if (processor.fw_state == 0)
    //    processor.fw_state = 1;
    //else
    //    processor.fw_state = 0;
    //resetImages();
}

void ProteusAudioProcessorEditor::odFootSw2Clicked() {

    //if (processor.fw_state == 0)
    //    processor.fw_state = 1;
    //else
    //    processor.fw_state = 0;
    //resetImages();
}

void ProteusAudioProcessorEditor::cabOnButton1Clicked() 
{
    if (processor.cab_state == 0) {
        processor.cab_state = 1;
    }
    else {
        processor.cab_state = 0;
    }
    resetImages();
    repaint();
}

void ProteusAudioProcessorEditor::cabOnButton2Clicked() 
{
    if (processor.cab_state == 0) {
        processor.cab_state = 1;
    }
    else {
        processor.cab_state = 0;
    }
    resetImages();
    repaint();
}

void ProteusAudioProcessorEditor::sliderValue1Changed(Slider* slider)
{
    // Amp "1"
    if (slider == &ampBassKnob1 || slider == &ampMidKnob1 || slider == &ampTrebleKnob1) {
        processor.set_ampEQ(ampBassKnob1.getValue(), 1.getValue(), ampTrebleKnob1.getValue());
    }

}


void ProteusAudioProcessorEditor::modelSelect1Changed()
{
    const int selectedFileIndex = modelSelect1.getSelectedItemIndex();
    if (selectedFileIndex >= 0 && selectedFileIndex < processor.jsonFiles.size() && processor.jsonFiles.empty() == false) { //check if correct 
        if (processor.jsonFiles[selectedFileIndex].existsAsFile() && isValidFormat(processor.jsonFiles[selectedFileIndex])) {
            processor.loadConfig(processor.jsonFiles[selectedFileIndex]);
            processor.current_model_index = selectedFileIndex;
            processor.saved_model = processor.jsonFiles[selectedFileIndex];
        }
    }
    repaint();
}

void ProteusAudioProcessorEditor::modelSelect2Changed()
{
    const int selectedFileIndex = modelSelect2.getSelectedItemIndex();
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
    // ... [resetImages function remains unchanged]

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
    // Set On/Off cab graphic "1"
    if (processor.cab_state == 0) {
        cabOnButton1.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::cab_switch_off_png, BinaryData::cab_switch_off_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::cab_switch_off_png, BinaryData::cab_switch_off_pngSize), 1.0, Colours::transparentWhite,
            0.0);
    }
    else {
        cabOnButton1.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
            0.0);
    }

     // Set On/Off cab graphic "2"
    if (processor.cab_state == 0) {
        cabOnButton2.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::cab_switch_off_png, BinaryData::cab_switch_off_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::cab_switch_off_png, BinaryData::cab_switch_off_pngSize), 1.0, Colours::transparentWhite,
            0.0);
    }
    else {
        cabOnButton2.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::cab_switch_on_png, BinaryData::cab_switch_on_pngSize), 1.0, Colours::transparentWhite,
            0.0);
    }
}
