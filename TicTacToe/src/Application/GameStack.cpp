#include "GameStack.h"

#include <SFML/Graphics.hpp>

#include "GlobalResources.h"
#include "GameStates/SplashScreen.h"

std::stack<State*> GameStack::StateMachine;
sf::RenderWindow* GameStack::Window;
SpeechRecognizer* GameStack::SpeechRecognitionEngine;

void GameStack::Init()
{
	// Create game window
	Window = new sf::RenderWindow(sf::VideoMode(800, 450), "Tic-Tac-Toe", sf::Style::None);
	Window->setVerticalSyncEnabled(true);

	SpeechRecognitionEngine = new SpeechRecognizer();

	// Create and load all global resources
	GlobalResources::Font = new sf::Font();
	GlobalResources::Font->loadFromFile("../res/consola.ttf");

	GlobalResources::CircleTexture = new sf::Texture();
	GlobalResources::CircleTexture->loadFromFile("../res/textures/circle.png");

	GlobalResources::CrossTexture = new sf::Texture();
	GlobalResources::CrossTexture->loadFromFile("../res/textures/cross.png");

	GlobalResources::BoardTexture = new sf::Texture();
	GlobalResources::BoardTexture->loadFromFile("../res/textures/board.png");

	// Create and add SplashScreen Layer to start application
	PushState(new SplashScreen(1.0f));
}

void GameStack::Clean()
{
	while (!StateMachine.empty())
	{
		delete StateMachine.top();
		StateMachine.pop();
	}
}

State* GameStack::GetState()
{
	// Update states list
	while (!StateMachine.empty() && StateMachine.top()->IsDelete())
	{
		delete StateMachine.top();
		StateMachine.pop();
	}

	// Return current top state
	return StateMachine.top();
}

void GameStack::PushState(State* newState)
{
	StateMachine.push(newState);
}
