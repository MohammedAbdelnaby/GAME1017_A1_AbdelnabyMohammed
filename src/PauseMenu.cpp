#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
	TextureManager::Instance()->load("../Assets/textures/PauseMenu.BMP", "PauseMenu");
	auto size = TextureManager::Instance()->getTextureSize("PauseMenu");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(400.0f, 300.0f);
	setType(PAUSEMENU);
	m_pResume = new Button("../Assets/textures/restartButton.png", "restartButton", RESUME_BUTTON);
	m_pResume->getTransform()->position = glm::vec2(400.0f, 300.0f);
	m_pResume->addEventListener(CLICK, [&]()-> void
	{
		setPaused(false);
	});
}

PauseMenu::~PauseMenu()
= default;

void PauseMenu::draw()
{
	if (m_Ispaused)
	{
		TextureManager::Instance()->draw("PauseMenu", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
		m_pResume->draw();
	}
}

void PauseMenu::update()
{
	if (m_Ispaused)
	{
		m_pResume->update();
	}
}

void PauseMenu::clean()
{
}

void PauseMenu::setPaused(bool paused)
{
	m_Ispaused = paused;
}

bool PauseMenu::getPaused()
{
	return m_Ispaused;
}
