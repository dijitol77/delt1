#pragma once
#include "PluginProcessor.h"
#include "juce_audio_plugin_client/juce_audio_plugin_client.h" // Include this for the JucePlugin_WantsMidiInput, etc.

class MidiProcessing
{
public:
    // Constructor and Destructor if needed

    // Declare member functions here
    void processMidi(juce::MidiBuffer& midiMessages);
    bool acceptsMidi() const;
    bool producesMidi() const;
    bool isMidiEffect() const;

private:
    // You can include any private member variables or functions here if needed
};

void MidiProcessing::processMidi(juce::MidiBuffer& midiMessages)
{
    // MIDI Processing
    MidiBuffer processedMidi;
    int time;
    MidiMessage m;
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        if (m.isNoteOn())
            m = MidiMessage::noteOn (m.getChannel(), m.getNoteNumber(), (uint8)127);
        else if (m.isNoteOff())
            m = MidiMessage::noteOff (m.getChannel(), m.getNoteNumber(), (uint8)0);
        else if (m.isAftertouch())
            m = MidiMessage::aftertouchChange (m.getChannel(), m.getNoteNumber(), m.getAfterTouchValue());
        else if (m.isPitchWheel())
            m = MidiMessage::pitchWheel (m.getChannel(), m.getPitchWheelValue());
        else if (m.isController())
            m = MidiMessage::controllerEvent (m.getChannel(), m.getControllerNumber(), m.getControllerValue());

        processedMidi.addEvent (m, time);
    }

    midiMessages.clear();
    midiMessages = processedMidi;
}

bool MidiProcessing::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiProcessing::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiProcessing::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}
