// StateManagement.h

#pragma once

#include "JuceHeader.h"

class StateManagement
{
public:
    StateManagement();
    ~StateManagement();

    void getStateInformation(MemoryBlock& destData, ValueTree treeState, /* other necessary variables */);
    void setStateInformation(const void* data, int sizeInBytes, ValueTree& treeState, /* other necessary variables */);
    
    void set_ampEQ(float bass_slider, float mid_slider, float treble_slider, /* any other necessary variables */);
    void loadConfig(File configFile, /* any other necessary variables */);

private:
    // Add private member variables and methods here if any
};

