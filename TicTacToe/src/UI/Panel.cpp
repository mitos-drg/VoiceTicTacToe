#include "Panel.h"

#include "Application/GameStack.h"

Panel::Panel(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	m_shape.setPosition(position);
	m_shape.setSize(size);
	m_shape.setFillColor(color);
}

Panel::~Panel()
{
}

void Panel::Draw()
{
	GameStack::GetWindow()->draw(m_shape);
}

void Panel::Update(float deltaTime)
{
}
