#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "UIElement.h"

/* UI panel, basically just to abstract this from states. */
class Panel : public UIElement
{
public:
	Panel(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	~Panel();

	/**
		Draws control to the screen
	*/
	void Draw();
	/**
		Updates state of this button
	*/
	void Update(float deltaTime);

private:
	sf::RectangleShape m_shape;
};