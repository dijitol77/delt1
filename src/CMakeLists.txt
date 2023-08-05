#add_subdirectory(headless)

target_sources(Proteus PRIVATE
	myLookAndFeel.cpp
	myLookAndFeel.h
	PluginEditor.cpp
	PluginEditor.h
	PluginProcessor.cpp
        PluginProcessor.h
    	// PluginProcessorInit.cpp
    	// AudioProcessing.cpp
        // AudioProcessing.h
    	// MidiProcessing.cpp
     	// MidiProcessing.h
    	//  Programs.cpp
     	// Programs.h
    	// StateManagement.cpp
        // StateManagement.h
    	// EditorCreation.cpp
        // EditorCreation.h
    	// UtilityFunctions.cpp
        // UtilityFunctions.h
	RTNeuralLSTM.cpp
	RTNeuralLSTM.h
        CabSim.h
        Eq4Band.cpp
        Eq4Band.h
)

#target_precompile_headers(Proteus PRIVATE pch.h)

