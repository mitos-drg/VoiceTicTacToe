#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>

#include <string>

#include "UIElement.h"

/* UI headline element, just to abstract this from states. */
class HeadLine : public UIElement
{
public:
	HeadLine(int posx, int posy, int sizex, int sizey, std::string caption);
	~HeadLine() override;

	/**
		Draws control to the screen
	*/
	void Draw() override;
	/**
		Returns whether this button was pressed in current frame
	*/
	void Update(float deltaTime) override {}

private:
	std::string m_caption;

	sf::RectangleShape m_line;
	sf::Text m_text;

	sf::Color m_color = { 0x22, 0x22, 0x22, 0xff };
};