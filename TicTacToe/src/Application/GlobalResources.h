#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Engine/TicTacToe.h"

class GlobalResources
{
public:
	/* Font object for use in application */
	static sf::Font* Font;

	/* Texture of circle */
	static sf::Texture* CircleTexture;
	/* Texture of cross */
	static sf::Texture* CrossTexture;
	/* Texture of playing board */
	static sf::Texture* BoardTexture;
};