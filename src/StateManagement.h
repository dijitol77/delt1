#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>
#include "RTNeuralLSTM.h" // Change LSTMClass to RT_LSTM
#include "PluginEditor.h" // Include the header that declares ProteusAudioProcessorEditor

class StateManagement
{
public:
    StateManagement();
    ~StateManagement();

    void getStateInformation(MemoryBlock& destData, ValueTree treeState, bool fw_state, File folder, File saved_model, int current_model_index, bool cab_state);
    void setStateInformation(const void* data, int sizeInBytes, ValueTree& treeState, bool& fw_state, File& folder, File& saved_model, int& current_model_index, bool& cab_state, ProteusAudioProcessorEditor* getActiveEditor);

    void set_ampEQ(float bass_slider, float mid_slider, float treble_slider, dsp::IIR::Filter<float>& eq4band, dsp::IIR::Filter<float>& eq4band2);

    void loadConfig(File configFile, bool& conditioned, bool& model_loaded, void (*suspendProcessingFunc)(bool), int& pauseVolume, RT_LSTM& LSTM, RT_LSTM& LSTM2, const char* &char_filename); // pass 'char_filename' as a reference

private:
    // Add any private members if needed
};


