#pragma once

#include <SFML/Graphics/Text.hpp>

#include <vector>

#include "Application/State.h"
#include "UI/UIElement.h"
#include "Engine/Engine.h"

/*
	Game state responsible for human vs computer game.
*/
class PlayComputer : public State
{
public:
	PlayComputer(int difficulty, bool humanStarts);
	~PlayComputer();

	void Draw() override;
	void Update(float deltaTime) override;

private:
	std::vector<UIElement*> m_guiElements;
	sf::Text m_gameoverText;

	TTTEngine m_engine;

	int m_difficulty;
	int m_gameState = 0;
	bool m_isHumanTurn = true;
};