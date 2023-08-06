// StateManagement.cpp

#include "StateManagement.h"
#include "PluginEditor.h"

StateManagement::StateManagement()
{
    // Constructor implementation if needed
    // From the original file, there doesn't seem to be any specific initialization for state management.
}

StateManagement::~StateManagement()
{
    // Destructor implementation if needed
    // No specific destructor code was provided in the original file.
}

void StateManagement::getStateInformation(MemoryBlock& destData, ValueTree treeState, bool fw_state, File folder, File saved_model, int current_model_index, bool cab_state)
{
    treeState.setProperty("fw_state", fw_state, nullptr);
    treeState.setProperty("folder", folder.getFullPathName(), nullptr);
    treeState.setProperty("saved_model", saved_model.getFullPathName(), nullptr);
    treeState.setProperty("current_model_index", current_model_index, nullptr);
    treeState.setProperty("cab_state", cab_state, nullptr);

    std::unique_ptr<XmlElement> xml = treeState.createXml();
    copyXmlToBinary(*xml, destData);
}

void StateManagement::setStateInformation(const void* data, int sizeInBytes, ValueTree& treeState, bool& fw_state, File& folder, File& saved_model, int& current_model_index, bool& cab_state, ProteusAudioProcessorEditor* getActiveEditor)
{
    std::unique_ptr<XmlElement> xmlState = getXmlFromBinary(data, sizeInBytes);

    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName(treeState.getType()))
        {
            treeState.replaceState(ValueTree::fromXml(*xmlState));
            fw_state = xmlState->getBoolAttribute("fw_state");
            folder = File(xmlState->getStringAttribute("folder"));
            saved_model = File(xmlState->getStringAttribute("saved_model"));
            current_model_index = xmlState->getIntAttribute("current_model_index");
            cab_state = xmlState->getBoolAttribute("cab_state");

            if (auto* editor = dynamic_cast<PluginEditor*>(getActiveEditor))
                editor->resetImages();

            if (saved_model.existsAsFile()) {
                // Load configuration from the file
                bool conditioned = false;
                bool model_loaded = false;
                int pauseVolume = 0;
                RT_LSTM LSTM;
                RT_LSTM LSTM2;
                const char* char_filename = nullptr;
                loadConfig(saved_model, conditioned, model_loaded, nullptr, pauseVolume, LSTM, LSTM2, char_filename);
            }
        }
    }
}

void StateManagement::set_ampEQ(float bass_slider, float mid_slider, float treble_slider, dsp::IIR::Filter<float>& eq4band, dsp::IIR::Filter<float>& eq4band2)
{
    // This is a placeholder. You'll need to replace with the correct filter design.
    auto coefficients = dsp::IIR::Coefficients<float>::makeLowPass(44100, bass_slider); // Example
    eq4band.setCoefficients(coefficients);
    eq4band2.setCoefficients(coefficients);
}

void StateManagement::loadConfig(File configFile, bool& conditioned, bool& model_loaded, void (*suspendProcessingFunc)(bool), int& pauseVolume, RT_LSTM& LSTM, RT_LSTM& LSTM2, const char*& char_filename)
{
    if (suspendProcessingFunc)
        suspendProcessingFunc(true);

    pauseVolume = 3;
    String path = configFile.getFullPathName();
    char_filename = path.toRawUTF8();

    LSTM.reset();
    LSTM2.reset();

    LSTM.load_json(char_filename);
    LSTM2.load_json(char_filename);

    conditioned = (LSTM.input_size != 1);
    model_loaded = true;

    if (suspendProcessingFunc)
        suspendProcessingFunc(false);
}
