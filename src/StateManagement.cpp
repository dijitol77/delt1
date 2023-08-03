#include "StateManagement.h"
#include "juce_core/juce_core.h" // Include this for the MemoryBlock class

void StateManagement::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = this->processor.treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    xml->setAttribute ("fw_state", this->processor.fw_state);
    xml->setAttribute("folder", this->processor.folder.getFullPathName().toStdString());
    xml->setAttribute("saved_model", this->processor.saved_model.getFullPathName().toStdString());
    xml->setAttribute("current_model_index", this->processor.current_model_index);
    xml->setAttribute ("cab_state", this->processor.cab_state);
    copyXmlToBinary (*xml, destData);
}

void StateManagement::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName (this->processor.treeState.state.getType()))
        {
            this->processor.treeState.replaceState (juce::ValueTree::fromXml (*xmlState));
            this->processor.fw_state = xmlState->getBoolAttribute ("fw_state");
            juce::File temp_saved_model = xmlState->getStringAttribute("saved_model");
            this->processor.saved_model = temp_saved_model;
            this->processor.cab_state = xmlState->getBoolAttribute ("cab_state");

            this->processor.current_model_index = xmlState->getIntAttribute("current_model_index");
            juce::File temp = xmlState->getStringAttribute("folder");
            this->processor.folder = temp;
            if (auto* editor = dynamic_cast<ProteusAudioProcessorEditor*> (this->processor.getActiveEditor()))
                editor->resetImages();

            if (this->processor.saved_model.existsAsFile()) {
                this->processor.loadConfig(this->processor.saved_model);
            }
         }  
    }  
}
