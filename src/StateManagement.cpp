#include "StateManagement.h"
#include "juce_core/juce_core.h" // Include this for the MemoryBlock class

void StateManagement::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = processor.treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    xml->setAttribute ("fw_state", processor.fw_state);
    xml->setAttribute("folder", processor.folder.getFullPathName().toStdString());
    xml->setAttribute("saved_model", processor.saved_model.getFullPathName().toStdString());
    xml->setAttribute("current_model_index", processor.current_model_index);
    xml->setAttribute ("cab_state", processor.cab_state);
    copyXmlToBinary (*xml, destData);
}

void StateManagement::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName (processor.treeState.state.getType()))
        {
            processor.treeState.replaceState (ValueTree::fromXml (*xmlState));
            processor.fw_state = xmlState->getBoolAttribute ("fw_state");
            File temp_saved_model = xmlState->getStringAttribute("saved_model");
            processor.saved_model = temp_saved_model;
            processor.cab_state = xmlState->getBoolAttribute ("cab_state");

            processor.current_model_index = xmlState->getIntAttribute("current_model_index");
            File temp = xmlState->getStringAttribute("folder");
            processor.folder = temp;
            if (auto* editor = dynamic_cast<ProteusAudioProcessorEditor*> (processor.getActiveEditor()))
                editor->resetImages();

            if (processor.saved_model.existsAsFile()) {
                processor.loadConfig(processor.saved_model);
            }
         }  
    }  
}
