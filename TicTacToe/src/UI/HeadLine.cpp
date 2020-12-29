#include "HeadLine.h"

#include "Application/GameStack.h"
#include "Application/GlobalResources.h"

HeadLine::HeadLine(int posx, int posy, int sizex, int sizey, std::string caption)
	: m_caption(caption)
{
	m_line.setPosition((float)posx, posy + sizey - 3.0f);
	m_line.setSize({ (float)sizex, 3.0f });

	m_text.setString(m_caption);
	m_text.setCharacterSize(18);
	m_text.setFont(*GlobalResources::Font);

	float width = m_text.getGlobalBounds().width;
	m_text.setPosition(posx + (sizex - width) / 2.0f, posy + 10.0f);
}

HeadLine::~HeadLine()
{
}

void HeadLine::Draw()
{
	GameStack::GetWindow()->draw(m_text);
	GameStack::GetWindow()->draw(m_line);
}
