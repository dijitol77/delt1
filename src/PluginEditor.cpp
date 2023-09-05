#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <algorithm>

// Constants for fixed sizes and aspect ratios
constexpr double FixedAspectRatio = 1121.0 / 326.0;
constexpr int MinWidth = 1121;
constexpr int MinHeight = 326;
constexpr int MaxWidth = 1168;
constexpr int MaxHeight = 489;

ProteusAudioProcessorEditor::ProteusAudioProcessorEditor (ProteusAudioProcessor& p)
    : AudioProcessorEditor(&p),
      processor(p),
      block1(/* constructor arguments, if any */),
      resizableCorner(std::make_unique<juce::ResizableCornerComponent>(this, &constrainer)),
      resizableBorder(std::make_unique<juce::ResizableBorderComponent>(this, &constrainer))
{
    // Set up resizable components
    addAndMakeVisible(resizableCorner.get());
    addAndMakeVisible(resizableBorder.get());
    constrainer.setFixedAspectRatio(FixedAspectRatio);
    constrainer.setSizeLimits(MinWidth, MinHeight, MaxWidth, MaxHeight);
    setConstrainer(&constrainer);
    setSize(MinWidth, MinHeight);

    // Initialize and add other components
    initializeComponents();
}

ProteusAudioProcessorEditor::~ProteusAudioProcessorEditor()
{
    odDriveKnob.setLookAndFeel(nullptr);
    odLevelKnob.setLookAndFeel(nullptr);
}

void ProteusAudioProcessorEditor::initializeComponents()
{
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
    addAndMakeVisible(versionLabel);
    versionLabel.setText("v1.2", juce::NotificationType::dontSendNotification);
    versionLabel.setJustificationType(juce::Justification::left);
    versionLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    versionLabel.setFont(font);
    background2 = ImageCache::getFromMemory(BinaryData::BACK2_jpg, BinaryData::BACK2_jpgSize);
    setSize(1121, 326);
    modelSelect.addListener(this);

    setSize (400, 300);

    odDriveKnob.setSliderStyle(Slider::Rotary);
    odDriveKnob.setRange(0.0, 1.0, 0.01);
    odDriveKnob.setValue(0.5);
    odDriveKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible(&odDriveKnob);

    // Initialize the attachment
    odDriveAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, "drive", odDriveKnob);

    // ... rest of your code
    loadFromFolder();
    resized();
}

void ProteusAudioProcessorEditor::paint(Graphics& g)
{
      // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}
    if (processor.fw_state == 1 && processor.conditioned == true) {
        g.drawImageWithin(background2, 0, 0, getWidth(), getHeight(), RectanglePlacement::stretchToFit, false);
    } else if (processor.fw_state == 1 && processor.conditioned == false) {
        g.drawImageWithin(background2, 0, 0, getWidth(), getHeight(), RectanglePlacement::stretchToFit, false);
    }
}

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
    int modelSelectWidth = 200;
    int modelSelectHeight = 30;
    int modelSelectX = blockB1.getX() + (blockB1.getWidth() - modelSelectWidth) / 2;
    int modelSelectY = blockB1.getY() + (blockB1.getHeight() - modelSelectHeight) / 2;
    modelSelect.setBounds(modelSelectX, modelSelectY, modelSelectWidth, modelSelectHeight);
    int knobWidth = blockA2.getWidth() - 20;
    int knobHeight = blockA2.getHeight() - 20;
    int knobX = blockA2.getX() + 10;
    int knobY = blockA2.getY() + 10;
    // odDriveKnob.setBounds(knobX, knobY, knobWidth, knobHeight);
     odDriveKnob.setBounds(20, 20, 100, 100);  // Explicitly set bounds
    resizableCorner->setBounds(getWidth() - 16, getHeight() - 16, 16, 16);
    resizableBorder->setBounds(0, 0, getWidth(), getHeight());
    loadedModelLabel.setBounds(20, getHeight() - 80, 300, 30);
}

bool ProteusAudioProcessorEditor::isValidFormat(File configFile)
{
    // Your existing isValidFormat code
    return true;
}

void ProteusAudioProcessorEditor::loadFromFolder()
{
    processor.model_loaded = false;
    File modelsDir = File::getSpecialLocation(File::currentExecutableFile).getParentDirectory().getChildFile("models");
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

void ProteusAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    // Empty for now
}

void ProteusAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    // Empty for now
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
}

void ProteusAudioProcessorEditor::modelSelectChanged()
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

void ProteusAudioProcessorEditor::resetImages()
{
    repaint();
}
