#include "BoardDisplay.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Application/GameStack.h"
#include "Application/GlobalResources.h"

BoardDisplay::BoardDisplay(int posx, int posy, int sizex, int sizey, TTTBoard* board)
	: m_positions(), m_rect(posx, posy, sizex, sizey), m_board(board)
{
	m_boardColor = { 30, 120, 90, 255 };
	m_circleColor = { 15,45, 200,255 };
	m_crossColor = { 200,45,15,255 };

	m_boardArea.setPosition(posx, posy);
	m_boardArea.setSize({ (float)sizex, (float)sizey });
	m_boardArea.setTexture(GlobalResources::BoardTexture);
	m_boardArea.setFillColor(m_boardColor);

	m_circleSprite.setSize({ sizex * 0.3f, sizey * 0.3f });
	m_circleSprite.setTexture(GlobalResources::CircleTexture);
	m_circleSprite.setFillColor(m_circleColor);

	m_crossSprite.setSize({ sizex * 0.3f, sizey * 0.3f });
	m_crossSprite.setTexture(GlobalResources::CrossTexture);
	m_crossSprite.setFillColor(m_crossColor);

	m_positions[0] = { posx + sizex * 0.01f, posy + sizey * 0.01f };
	m_positions[1] = { posx + sizex * 0.3375f, posy + sizey * 0.01f };
	m_positions[2] = { posx + sizex * 0.675f, posy + sizey * 0.01f };

	m_positions[3] = { posx + sizex * 0.01f, posy + sizey * 0.3375f };
	m_positions[4] = { posx + sizex * 0.3375f, posy + sizey * 0.3375f };
	m_positions[5] = { posx + sizex * 0.675f, posy + sizey * 0.3375f };

	m_positions[6] = { posx + sizex * 0.01f, posy + sizey * 0.675f };
	m_positions[7] = { posx + sizex * 0.3375f, posy + sizey * 0.675f };
	m_positions[8] = { posx + sizex * 0.675f, posy + sizey * 0.675f };

	m_line.setSize({ (float)m_rect.width * 1.1f, 10.0f });
}

BoardDisplay::~BoardDisplay()
{
}

void BoardDisplay::Draw()
{
	sf::RenderWindow* window = GameStack::GetWindow();

	window->draw(m_boardArea);

	for (int i = 0; i < 9; ++i)
	{
		if (m_board->fields[i] == TTTPlayer::Circle)
		{
			m_circleSprite.setPosition(m_positions[i]);
			window->draw(m_circleSprite);
		}
		else if (m_board->fields[i] == TTTPlayer::Cross)
		{
			m_crossSprite.setPosition(m_positions[i]);
			window->draw(m_crossSprite);
		}
	}

	/*if (!m_hasWinBoard)
	{
		if ((m_board->circles & winMask[0]) || (m_board->crosses & winMask[0])) // 0 1 2
		{
			m_line.setPosition(m_rect.left + (float)m_rect.width * 0.1f, m_rect.top + m_rect.height * 0.175f);
			m_line.setRotation(0);
			m_hasWinBoard = true;
		}
		else if ((m_board->circles & winMask[1]) || (m_board->crosses & winMask[1])) // 0 3 6
		{
			m_line.setPosition(m_rect.left + (float)m_rect.width * 0.175f, m_rect.top + m_rect.height * 0.1f);
			m_line.setRotation(90);
			m_hasWinBoard = true;
		}
		else if ((m_board->circles & winMask[2]) || (m_board->crosses & winMask[2])) // 0 4 8
		{
			m_line.setPosition(m_rect.left + (float)m_rect.width * 0.1f, m_rect.top + m_rect.height * 0.1f);
			m_line.setSize({ (float)m_rect.width * 1.1f * 1.41f, 10.0f });
			m_line.setRotation(45);
			m_hasWinBoard = true;
		}
		else if ((m_board->circles & winMask[3]) || (m_board->crosses & winMask[3])) // 1 4 7
		{
			m_line.setPosition(m_rect.left + (float)m_rect.width * 0.525f, m_rect.top + m_rect.height * 0.1f);
			m_line.setRotation(90);
			m_hasWinBoard = true;
		}
		else if ((m_board->circles & winMask[4]) || (m_board->crosses & winMask[4])) // 3 4 5
		{
			m_line.setPosition(m_rect.left + (float)m_rect.width * 0.1f, m_rect.top + m_rect.height * 0.525f);
			m_line.setRotation(0);
			m_hasWinBoard = true;
		}
		else if ((m_board->circles & winMask[5]) || (m_board->crosses & winMask[5])) // 2 4 6
		{
			m_line.setPosition(m_rect.left + (float)m_rect.width * 0.9f, m_rect.top + m_rect.height * 0.9f);
			m_line.setRotation(-45);
			m_line.setSize({ (float)m_rect.width * 1.1f * 1.41f, 10.f });
			m_hasWinBoard = true;
		}
		else if ((m_board->circles & winMask[6]) || (m_board->crosses & winMask[6])) // 2 5 8
		{
			m_line.setPosition(m_rect.left + (float)m_rect.width * 0.825f, m_rect.top + m_rect.height * 0.1f);
			m_line.setRotation(90);
			m_hasWinBoard = true;
		}
		else if ((m_board->circles & winMask[7]) || (m_board->crosses & winMask[7])) // 6 7 8
		{
			m_line.setPosition(m_rect.left + (float)m_rect.width * 0.1f, m_rect.top + m_rect.height * 0.825f);
			m_line.setRotation(0);
			m_hasWinBoard = true;
		}
	}
	if (m_hasWinBoard)
	{
		window->draw(m_line);
	}*/
}

void BoardDisplay::Update(float deltaTime)
{
}
