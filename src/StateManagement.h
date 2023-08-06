#pragma once

#include <JuceHeader.h>
#include "RT_LSTM.h"

class StateManagement
{
public:
    StateManagement();
    ~StateManagement();

    void getStateInformation(MemoryBlock& destData, ValueTree treeState, bool fw_state, File folder, File saved_model, int current_model_index, bool cab_state, float bass_slider, float mid_slider, float treble_slider);
    void setStateInformation(const void* data, int sizeInBytes, ValueTree& treeState, bool& fw_state, File& folder, File& saved_model, int& current_model_index, bool& cab_state, float& bass_slider, float& mid_slider, float& treble_slider, ProteusAudioProcessorEditor* getActiveEditor);
    void set_ampEQ(float bass_slider, float mid_slider, float treble_slider, dsp::IIR::Filter<float>& eq4band, dsp::IIR::Filter<float>& eq4band2);
    void loadConfig(File configFile, bool& conditioned, bool& model_loaded, void (*suspendProcessingFunc)(bool), int& pauseVolume, RT_LSTM& LSTM, RT_LSTM& LSTM2, const char*& char_filename);

private:
    // Add any private members if needed
};
