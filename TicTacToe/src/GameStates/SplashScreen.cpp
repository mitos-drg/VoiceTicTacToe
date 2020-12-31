#include "SplashScreen.h"

#include "Application/GameStack.h"
#include "MainMenu.h"

SplashScreen::SplashScreen(float duration)
	: m_duration(duration)
{
	m_texture.loadFromFile("./res/textures/splash.jpg");

	m_screen.setPosition({ 0, 0 });
	m_screen.setSize({ 800, 450 });
	m_screen.setTexture(&m_texture);
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::Draw()
{
	GameStack::GetWindow()->draw(m_screen);
}

void SplashScreen::Update(float deltaTime)
{
	m_duration -= deltaTime;

	if (m_duration <= 0)
	{
		m_delete = true;
		GameStack::PushState(new MainMenu());
		GameStack::GetWindow()->create(sf::VideoMode(800, 450), "Tic-Tac-Toe", sf::Style::Close | sf::Style::Titlebar);
		GameStack::GetWindow()->setVerticalSyncEnabled(true);
	}
}
