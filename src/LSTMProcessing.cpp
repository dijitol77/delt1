#include "LSTMProcessing.h"

void processWithLSTM(RT_LSTM& lstm, float* channelData, int numSamples) {
    for (int i = 0; i < numSamples; ++i) {
        channelData[i] = lstm.forward(channelData[i]);
    }
}
