# CMake file for VoiceChess executable

# Set source files for VoiceChess executable
set(VTTT_SOURCE 
	src/main.cpp
	
	src/Application/GameStack.h
	src/Application/GameStack.cpp
	src/Application/State.h
	src/Application/GlobalResources.h
	src/Application/GlobalResources.cpp
	
	src/Engine/TicTacToe.h
	src/Engine/TicTacToe.cpp
	src/Engine/Engine.h
	src/Engine/Engine.cpp
	
	src/GameStates/MainMenu.h
	src/GameStates/MainMenu.cpp
	src/GameStates/PlayComputer.h
	src/GameStates/PlayComputer.cpp
	src/GameStates/PlayHuman.h
	src/GameStates/PlayHuman.cpp
	src/GameStates/SplashScreen.h
	src/GameStates/SplashScreen.cpp
	
	src/UI/UIElement.h
	src/UI/Button.h
	src/UI/Button.cpp
	src/UI/Panel.h
	src/UI/Panel.cpp
	src/UI/HeadLine.h
	src/UI/HeadLine.cpp
	src/UI/BoardDisplay.h
	src/UI/BoardDisplay.cpp
	
	src/VoiceInput/SpeechRecognizer.h
	src/VoiceInput/SpeechRecognizer.cpp
	src/VoiceInput/Transcriber.h
	src/VoiceInput/Transcriber.cpp
)

# Add VoiceChess executable
add_executable(tictactoe ${VTTT_SOURCE})

# Include executable headers
target_include_directories(tictactoe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Set some project level preprocesor definitions
target_compile_definitions(tictactoe PRIVATE SFML_STATIC)
target_compile_definitions(tictactoe PRIVATE _CRT_SECURE_NO_WARNINGS)

# structure files inside IDE projects
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${VTTT_SOURCE})

# Link any required libraries
target_link_libraries(tictactoe sfml-graphics sphinxbase pocketsphinx)