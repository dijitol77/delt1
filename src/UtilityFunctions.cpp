#include "PluginProcessor.h"
#include "UtilityFunctions.h"
#include "juce_core/juce_core.h" // Include this for the File class

void ProteusAudioProcessor::loadConfig(juce::File configFile)
{
    this->suspendProcessing(true);
    pauseVolume = 3;
    juce::String path = configFile.getFullPathName();
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
