#include "RT_LSTM.h" // Include the correct header for RT_LSTM
#include "UtilityFunctions.h"
#include "PluginProcessor.h"

// Constructor
UtilityFunctions::UtilityFunctions(ProteusAudioProcessor& p) : processor(p) {}

// Public member functions
void UtilityFunctions::loadConfig(juce::File configFile)
{
    juce::String path = configFile.getFullPathName();
    processor.char_filename = path.toUTF8();

    processor.resetLSTM();
    processor.resetLSTM2();

    processor.loadLSTM();
    processor.loadLSTM2();

    if (processor.getLSTM() != nullptr && processor.getLSTM().input_size == 1)
    {
        processor.conditioned = false;
    }
    else
    {
        processor.conditioned = true;
    }

    processor.model_loaded = true;
}
