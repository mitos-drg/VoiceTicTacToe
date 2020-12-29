#include "Button.h"

#include <SFML/Window.hpp>

#include "Application/GameStack.h"
#include "Application/GlobalResources.h"

Button::Button(int posx, int posy, int sizex, int sizey, std::string caption, std::function<void(Button*)> callback)
	: m_caption(caption), m_rect(posx, posy, sizex, sizey), m_callback(callback)
{
	m_shape.setPosition((float)posx, (float)posy);
	m_shape.setSize({ (float)sizex, (float)sizey });

	m_text.setString(m_caption);
	m_text.setCharacterSize(18);
	m_text.setFont(*GlobalResources::Font);

	float width = m_text.getGlobalBounds().width;
	m_text.setPosition(posx + (sizex - width)/2.0f, posy + 7);
}

Button::~Button()
{
}

void Button::Draw()
{
	sf::RenderWindow* context = GameStack::GetWindow();

	// Check whether button is hoovered and set apropiete colors
	if (m_isActive)
	{
		m_text.setFillColor(m_isHoovered ? m_hooveredForeground : m_foreground);
		m_shape.setFillColor(m_selected || m_isPressed ? m_selectedBackground : m_backgroud);
	}

	context->draw(m_shape);
	context->draw(m_text);
}

void Button::Update(float deltaTime)
{
	if (m_isActive)
	{
		m_isHoovered = m_rect.contains(sf::Mouse::getPosition(*GameStack::GetWindow()));
		if (m_isHoovered)
		{
			if (!m_isPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_isPressed = true;
				m_callback(this);
			}
		}
		
		if (m_isPressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_isPressed = false;
		}
	}
}

void Button::SetRect(int posx, int posy, int sizex, int sizey)
{
	m_shape.setPosition((float)posx, (float)posy);
	m_shape.setSize({ (float)sizex, (float)sizey });

	sf::FloatRect bounds = m_text.getLocalBounds();
	m_text.setPosition(posx + (sizex - bounds.width) / 2.0f, posy + 7);
}

void Button::SetCaption(std::string caption, sf::Font& font, unsigned int size)
{
	m_text.setString(m_caption);
	m_text.setCharacterSize(size);
	m_text.setFont(font);
}

void Button::SetColors(sf::Color& bg, sf::Color& fg, sf::Color& selected, sf::Color& hoovered)
{
	m_backgroud = bg;
	m_foreground = fg;
	m_selectedBackground = selected;
	m_hooveredForeground = hoovered;
}
