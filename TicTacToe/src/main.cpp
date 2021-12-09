/**
	Voice Tic-Tac-Toe game created by Mitos 2020
	
	
*/

// Libraries headers includes
#include <SFML/Window/Event.hpp>

// Project headers includes
#include "Application/GameStack.h"
#include "Application/State.h"

/**
	The program entry point
*/
int main(int argc, char* argv[])
{
	GameStack::Init();
	State* state;

	sf::Event event;
	sf::Clock clock;
	sf::Time deltaTime;

	GameStack::GetSpeechRecognizer()->StartListening();

	while (GameStack::GetWindow()->isOpen())
	{
		deltaTime = clock.restart();
		while (GameStack::GetWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				GameStack::GetWindow()->close();
		}

		GameStack::GetWindow()->clear({ 0x1f, 0x1f, 0x1f, 0xff });

		GameStack::GetSpeechRecognizer()->ProcessSpeech(deltaTime.asMilliseconds());

		state = GameStack::GetState();
		state->Update(deltaTime.asSeconds());
		state->Draw();
		
		GameStack::GetWindow()->display();
	}

	GameStack::Clean();

	return 0;
}