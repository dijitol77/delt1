#include "PluginProcessor.h" // Include this first
#include "UtilityFunctions.h" // Then this
#include "juce_core/juce_core.h" // Include this for the File class

void UtilityFunctions::loadConfig(juce::File configFile) {
    // Check if the file exists
    if (!configFile.exists()) {
        // Handle the error, e.g., by logging an error message and returning
        std::cerr << "Error: Config file does not exist: " << configFile.getFullPathName() << std::endl;
        return;
    }

    // Check if the file is in the correct format (e.g., if it's a JSON file)
    if (configFile.getFileExtension() != ".json") {
        // Handle the error, e.g., by logging an error message and returning
        std::cerr << "Error: Config file is not a JSON file: " << configFile.getFullPathName() << std::endl;
        return;
    }

    // If the file exists and is in the correct format, proceed with loading it
    // ...
}


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
