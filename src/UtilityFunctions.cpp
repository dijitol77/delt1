#include "PluginProcessor.h"
#include "UtilityFunctions.h"
#include "juce_core/juce_core.h" // Include this for the File class

UtilityFunctions::UtilityFunctions(ProteusAudioProcessor& p) : processor(p) {}

void UtilityFunctions::loadConfig(juce::File configFile)
{
    processor.suspendProcessing(true);
    processor.pauseVolume = 3;
    juce::String path = configFile.getFullPathName();
    processor.char_filename = path.toUTF8();

    processor.LSTM.reset();
    processor.LSTM2.reset();

    processor.LSTM.load_json(processor.char_filename);
    processor.LSTM2.load_json(processor.char_filename);

    if (processor.LSTM.input_size == 1) {
        processor.conditioned = false;
    } else {
        processor.conditioned = true;
    }

    //processor.saved_model = configFile;
    processor.model_loaded = true;
    processor.suspendProcessing(false);
}
