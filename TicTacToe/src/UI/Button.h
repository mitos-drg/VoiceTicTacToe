#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>

#include <string>
#include <functional>

#include "UIElement.h"

/* Simple UI button object with single callback. */
class Button : public UIElement
{
public:
	Button(int posx, int posy, int sizex, int sizey, std::string caption, std::function<void(Button*)> callback);
	~Button();

	/**
		Draws control to the screen
	*/
	void Draw();
	/**
		Updates state of this button
	*/
	void Update(float deltaTime);

	void SetSelected(bool selected) { m_selected = selected; }
	void SetActive(bool active) { m_isActive = active; }

	void SetRect(int posx, int posy, int sizex, int sizey);
	void SetCaption(std::string caption, sf::Font& font, unsigned int size);
	void SetColors(sf::Color& bg, sf::Color& fg, sf::Color& selected, sf::Color& hoovered);

private:
	std::string m_caption;
	sf::IntRect m_rect;

	sf::RectangleShape m_shape;
	sf::Text m_text;

	sf::Color m_backgroud = { 0x33, 0x33, 0x33, 0xff };
	sf::Color m_foreground = { 0xdd, 0xdd, 0xdd, 0xff };

	sf::Color m_selectedBackground = { 0x33, 0xaa, 0x33, 0xff };
	sf::Color m_hooveredForeground = { 0x99, 0x99, 0xee, 0xff };

	bool m_isPressed = false, m_isHoovered = false, m_isActive = true, m_selected = false;

	std::function<void(Button*)> m_callback;
};