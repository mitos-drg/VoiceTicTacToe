#include "PlayComputer.h"

#include <string>

#include "Application/GameStack.h"
#include "Application/GlobalResources.h"
#include "Engine/TicTacToe.h"

#include "UI/Panel.h"
#include "UI/BoardDisplay.h"
#include "UI/Button.h"

#include "VoiceInput/Transcriber.h"

PlayComputer::PlayComputer(int difficulty, bool humanStarts)
	: m_engine(TTTPlayer::Cross), m_difficulty(difficulty), m_isHumanTurn(humanStarts)
{
	m_guiElements.push_back(new Panel({ 475, 25 }, { 300.0f, 400.0f }, { 0x11, 0x66, 0x11, 0xff }));
	m_guiElements.push_back(new BoardDisplay(25, 25, 400, 400, m_engine.GetBoard()));

	m_guiElements.push_back(new Button(525, 70, 200, 36, "Restart", [this](Button* caller) {
		m_delete = true;
		GameStack::PushState(new PlayComputer(m_difficulty, true));
		}));

	m_guiElements.push_back(new Button(525, 130, 200, 36, "Return to menu", [this](Button* caller) {
		m_delete = true;
		}));
}

PlayComputer::~PlayComputer()
{
	for (UIElement* item : m_guiElements)
		delete item;
}

void PlayComputer::Draw()
{
	for (auto item : m_guiElements)
		item->Draw();

	if (m_gameState != 0)
	{
		GameStack::GetWindow()->draw(m_gameoverText);
	}
}

void PlayComputer::Update(float deltaTime)
{
	for (auto item : m_guiElements)
		item->Update(deltaTime);

	if (m_gameState == 0)
	{
		if (m_isHumanTurn)
		{	/** Commented for debug purposes*/
			bool cmdReturned;
			const char* command = GameStack::GetSpeechRecognizer()->GetHypothesis(cmdReturned);
			if (cmdReturned)
			{
				TTTMove playerMove = Transcriber::Transcribe(command);
				if (m_engine.CheckMove(playerMove))
				{
					m_gameState = m_engine.PerformMove(playerMove);
					m_isHumanTurn = false;
				}
			}
		}
		else
		{
			TTTMove computerMove = m_engine.GetBestMove(m_difficulty);
			m_gameState = m_engine.PerformMove(computerMove);
			m_isHumanTurn = true;
		}

		if (m_gameState == 1)
		{
			m_gameoverText.setFont(*GlobalResources::Font);
			m_gameoverText.setCharacterSize(60);
			m_gameoverText.setString("CIRCLE WON!");
			m_gameoverText.setPosition({ 40.0f, 175.0f });
		}
		else if (m_gameState == 2)
		{
			m_gameoverText.setFont(*GlobalResources::Font);
			m_gameoverText.setCharacterSize(60);
			m_gameoverText.setString("CROSS WON!");
			m_gameoverText.setPosition({ 60.0f, 175.0f });
		}
		else if (m_gameState == 3)
		{
			m_gameoverText.setFont(*GlobalResources::Font);
			m_gameoverText.setCharacterSize(90);
			m_gameoverText.setString("DRAW!");
			m_gameoverText.setPosition({ 110.0f, 165.0f });
		}
	}
}
