#add_subdirectory(headless)

target_sources(Proteus PRIVATE
	myLookAndFeel.cpp
	myLookAndFeel.h
	PluginEditor.cpp
	PluginEditor.h
	PluginProcessor.cpp
    	PluginProcessorInit.cpp
    	AudioProcessing.cpp
    	MidiProcessing.cpp
    	Programs.cpp
    	StateManagement.cpp
    	EditorCreation.cpp
    	UtilityFunctions.cpp
    	PluginCreation.cpp
	PluginProcessor.h
	RTNeuralLSTM.cpp
	RTNeuralLSTM.h
        CabSim.h
        Eq4Band.cpp
        Eq4Band.h
)

#target_precompile_headers(Proteus PRIVATE pch.h)

