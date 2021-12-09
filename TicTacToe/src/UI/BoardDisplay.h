#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "UIElement.h"
#include "Engine/TicTacToe.h"

/* User Interface element displaying tic tac toe board. */
class BoardDisplay : public UIElement
{
public:
	BoardDisplay(int posx, int posy, int sizex, int sizey, TTTBoard* board);
	~BoardDisplay();

	void Draw() override;
	void Update(float deltaTime) override;

	void SetBoard(TTTBoard* board) { m_board = board; }

private:
	TTTBoard* m_board;
	bool m_hasWinBoard = false;

	sf::IntRect m_rect;
	sf::RectangleShape m_boardArea;
	sf::RectangleShape m_crossSprite;
	sf::RectangleShape m_circleSprite;
	sf::RectangleShape m_line;

	sf::Color m_circleColor;
	sf::Color m_crossColor;
	sf::Color m_boardColor;

	sf::Vector2f m_positions[9];
};