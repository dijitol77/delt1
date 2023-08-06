// StateManagement.h

#pragma once

#include "JuceHeader.h"

class StateManagement
{
public:
    StateManagement();
    ~StateManagement();

    void getStateInformation(MemoryBlock& destData);
    void setStateInformation(const void* data, int sizeInBytes);
    void set_ampEQ(float bass_slider, float mid_slider, float treble_slider);
    void loadConfig(File configFile);

private:
    // Add private member variables and methods here if any
};
