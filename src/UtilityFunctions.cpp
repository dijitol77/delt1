#include "PluginProcessor.h"

void ProteusAudioProcessor::set_ampEQ(float bass_slider, float mid_slider, float treble_slider)
{
    eq4band.setParameters(bass_slider, mid_slider, treble_slider, 0.0f);
    eq4band2.setParameters(bass_slider, mid_slider, treble_slider, 0.0f);
}

void ProteusAudioProcessor::loadConfig(File configFile)
{
    this->suspendProcessing(true);
    pauseVolume = 3;
    String path = configFile.getFullPathName();
    char_filename = path.toUTF8();

    LSTM.reset();
    LSTM2.reset();

    LSTM.load_json(char_filename);
    LSTM2.load_json(char_filename);

    if (LSTM.input_size == 1) {
        conditioned = false;
    } else {
        conditioned = true;
    }

    //saved_model = configFile;
    model_loaded = true;
    this->suspendProcessing(false);
}
