#pragma once

#include <SFML/Graphics.hpp>

#include <stack>

#include "State.h"
#include "VoiceInput/SpeechRecognizer.h"

class GameStack
{
public:
	/*
		Function that initialize all global objects for Voice Tic-Tac-Toe application.
		Call it once on the application start-up.
	*/
	static void Init();
	/*
		Cleans all global objects, which remain.
	*/
	static void Clean();

	/*
		Returns the top-most state from the game stack (the current state of finite state machine).
	*/
	static State* GetState();

	/* Returns pointer to the application window. */
	static sf::RenderWindow* GetWindow() { return Window; }
	/* Returns pointer to the SpeechRecognizer object. */
	static SpeechRecognizer* GetSpeechRecognizer() { return SpeechRecognitionEngine; }

	/* Adds new state on top of game stack. */
	static void PushState(State* newState);

private:
	static std::stack<State*> StateMachine;
	static sf::RenderWindow* Window;
	static SpeechRecognizer* SpeechRecognitionEngine;
};