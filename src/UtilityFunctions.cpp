#include "UtilityFunctions.h"
#include "juce_core/juce_core.h"

// Constructor
UtilityFunctions::UtilityFunctions(ProteusAudioProcessor& p) : processor(p) {}

// Public member functions
void UtilityFunctions::loadConfig(juce::File configFile)
{
    juce::String path = configFile.getFullPathName();
    processor.char_filename = path.toUTF8();

    processor.resetLSTM();
    processor.resetLSTM2();

    processor.loadLSTM(processor.char_filename);
    processor.loadLSTM2(processor.char_filename);

    if (processor.LSTM != nullptr && processor.LSTM->input_size == 1) {
        processor.conditioned = false;
    } else {
        processor.conditioned = true;
    }

    processor.model_loaded = true;
}
