#include "PluginProcessor.h"
#include "PluginEditor.h"

LeftContainer::LeftContainer(ProteusAudioProcessor& p) : processor(p)
{
    // Initialize your components here
    addAndMakeVisible(loadButton);
    addAndMakeVisible(modelSelect);
    addAndMakeVisible(odDriveKnob);
    // ... other components
}

void LeftContainer::paint(Graphics& g)
{
    // Paint background and other stuff
    g.fillAll(Colours::black);
}

void LeftContainer::resized()
{
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::column;
    fb.items.add(FlexItem(loadButton).withFlex(1));
    fb.items.add(FlexItem(modelSelect).withFlex(1));
    fb.items.add(FlexItem(odDriveKnob).withFlex(1));
    // ... add other components
    fb.performLayout(getLocalBounds());
}

RightContainer::RightContainer(ProteusAudioProcessor& p) : LeftContainer(p)
{
    // You can add specific initialization for RightContainer if needed
}

ProteusAudioProcessorEditor::ProteusAudioProcessorEditor (ProteusAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), leftContainer(p), rightContainer(p)
{
    setSize (1000, 650);
    addAndMakeVisible(leftContainer);
    addAndMakeVisible(rightContainer);
}

ProteusAudioProcessorEditor::~ProteusAudioProcessorEditor()
{
}

void ProteusAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void ProteusAudioProcessorEditor::resized()
{
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::row;
    fb.items.add(FlexItem(leftContainer).withFlex(1));
    fb.items.add(FlexItem(rightContainer).withFlex(1));
    fb.performLayout(getLocalBounds());
}
