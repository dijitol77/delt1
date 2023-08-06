#pragma once

#include "JuceHeader.h"

// Include the headers for ProteusAudioProcessorEditor and RTNeuralLSTM
#include "PluginEditor.h"
#include "RTNeuralLSTM.h"


// Forward declaration for the editor class, assuming it's defined elsewhere.
class ProteusAudioProcessorEditor;

// Assuming you have a class or struct for LSTM operations.
class LSTMClass;

class StateManagement
{
public:
    StateManagement();
    ~StateManagement();

    void getStateInformation(MemoryBlock& destData, ValueTree treeState, bool fw_state, File folder, File saved_model, int current_model_index, bool cab_state);
    
    void setStateInformation(const void* data, int sizeInBytes, ValueTree& treeState, bool& fw_state, File& saved_model, int& current_model_index, bool& cab_state, ProteusAudioProcessorEditor* getActiveEditor);
    
    void set_ampEQ(float bass_slider, float mid_slider, float treble_slider, dsp::IIR::Filter<float>& eq4band, dsp::IIR::Filter<float>& eq4band2);
    
    void loadConfig(File configFile, bool& conditioned, bool& model_loaded, void (*suspendProcessingFunc)(bool), int& pauseVolume, LSTMClass& LSTM, LSTMClass& LSTM2);

private:
    // Add private member variables and methods here if any
};

