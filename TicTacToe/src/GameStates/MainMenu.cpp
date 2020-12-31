#include "MainMenu.h"

#include <iostream>

#include "Application/GameStack.h"

#include "PlayComputer.h"
#include "PlayHuman.h"

#include "UI/Button.h"
#include "UI/HeadLine.h"
#include "UI/Panel.h"
#include "UI/BoardDisplay.h"

MainMenu::MainMenu()
{
	m_guiElements.push_back(new Panel({ 475, 25 }, { 300.0f, 400.0f }, { 0x11, 0x66, 0x11, 0xff }));

	m_guiElements.push_back(new HeadLine(480, 30, 290, 36, "Play with:"));

	m_oponentBtn = new Button(525, 70, 200, 36, "Computer", [this](Button* caller) { 
		m_oponentBtn->SetSelected(false);
		m_playComputer = true;
		m_oponentBtn = caller;
		m_oponentBtn->SetSelected(true);
		});
	m_guiElements.push_back(m_oponentBtn);

	m_guiElements.push_back(new Button(525, 110, 200, 36, "Human", [this](Button* caller) { 
		m_oponentBtn->SetSelected(false);
		m_playComputer = false;
		m_oponentBtn = caller;
		m_oponentBtn->SetSelected(true);
		}));

	m_guiElements.push_back(new HeadLine(480, 150, 290, 36, "Play on:"));

	m_difficultyBtn = new Button(525, 190, 200, 36, "Easy mode", [this](Button* caller) { 
		m_difficultyBtn->SetSelected(false);
		m_difficultyMode = 2;
		m_difficultyBtn = caller;
		m_difficultyBtn->SetSelected(true);
		});
	m_guiElements.push_back(m_difficultyBtn);

	m_guiElements.push_back(new Button(525, 230, 200, 36, "Normal mode", [this](Button* caller) {
		m_difficultyBtn->SetSelected(false);
		m_difficultyMode = 4;
		m_difficultyBtn = caller;
		m_difficultyBtn->SetSelected(true);
		}));

	m_guiElements.push_back(new Button(525, 270, 200, 36, "Hard mode", [this](Button* caller) { 
		m_difficultyBtn->SetSelected(false);
		m_difficultyMode = 6;
		m_difficultyBtn = caller;
		m_difficultyBtn->SetSelected(true);
		}));

	m_guiElements.push_back(new Button(525, 350, 200, 36, "START THE GAME!", [this](Button* caller) {
		if (m_playComputer)
			GameStack::PushState(new PlayComputer(m_difficultyMode, true));
		else
			GameStack::PushState(new PlayHuman());
		}));
	
	m_oponentBtn->SetSelected(true);
	m_difficultyBtn->SetSelected(true);

	m_board = new TTTBoard();
	m_board->fields[0] = TTTPlayer::Circle;
	m_board->fields[1] = TTTPlayer::Cross;
	m_board->fields[2] = TTTPlayer::Cross;

	m_board->fields[3] = TTTPlayer::Cross;
	m_board->fields[4] = TTTPlayer::Circle;
	m_board->fields[5] = TTTPlayer::Circle;

	m_board->fields[6] = TTTPlayer::Circle;
	m_board->fields[7] = TTTPlayer::Cross;
	m_board->fields[8] = TTTPlayer::Cross;

	m_guiElements.push_back(new BoardDisplay(25, 25, 400, 400, m_board));
}

MainMenu::~MainMenu()
{
	for (UIElement* item : m_guiElements)
		delete item;

	delete m_board;
}

void MainMenu::Draw()
{
	for (auto item : m_guiElements)
		item->Draw();
}

void MainMenu::Update(float deltaTime)
{
	for (auto item : m_guiElements)
		item->Update(deltaTime);
}
