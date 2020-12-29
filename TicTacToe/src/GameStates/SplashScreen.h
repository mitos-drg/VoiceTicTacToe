#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Application/State.h"

/*
	Displays application splash screen for given duration.
	(Hey, promotion is important!)
*/
class SplashScreen : public State
{
public:
	SplashScreen(float duration);
	~SplashScreen() override;

	void Draw() override;
	void Update(float deltaTime) override;

private:
	float m_duration;

	sf::RectangleShape m_screen;
	sf::Texture m_texture;
};