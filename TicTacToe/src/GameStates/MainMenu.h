#pragma once

#include "Application/State.h"
#include "UI/UIElement.h"
#include "UI/Button.h"
#include "Engine/TicTacToe.h"

/*
	The game main menu state class.
*/
class MainMenu : public State
{
public:
	MainMenu();
	~MainMenu() override;

	void Draw() override;
	void Update(float deltaTime) override;

private:
	std::vector<UIElement*> m_guiElements;

	int m_difficultyMode = 2;
	bool m_playComputer = true;

	Button* m_oponentBtn;
	Button* m_difficultyBtn;

	TTTBoard* m_board;
};