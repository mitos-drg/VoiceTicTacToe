#include "VoiceTicTacToe.h"

#include <SFML/Graphics.hpp>


namespace TicTacToe
{

	void Initialize()
	{
		sf::RenderWindow window(sf::VideoMode(800, 450), "Voice Tic-Tac-Toe", sf::Style::Close | sf::Style::Titlebar);
		window.setFramerateLimit(20);
	}

	void Run(sf::RenderWindow window)
	{
		while (window.isOpen())
		{
			// Event polling
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			// Begin the draw area
			window.clear(sf::Color(200, 200, 200, 255));

			// Draw basic components of UI

			window.display();
		}
	}
}
