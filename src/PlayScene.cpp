#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
	for (int i = 0; i < m_pbullet.size(); i++)
	{
		addChild(m_pbullet[i]);
	}
	for (int i = 0; i < m_pEnemybullet.size(); i++)
	{
		addChild(m_pEnemybullet[i]);
	}
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	if(m_pPauseMenu->getPaused())
	{ 
		m_pPauseMenu->update();
		return;
	}
	updateDisplayList();
	m_pBg->getTransform()->position.x -= 5;
	m_pBg2->getTransform()->position.x -= 5;
	for (int i = 0; i < m_pbullet.size(); i++)
	{
		m_pbullet[i]->getTransform()->position.x += 10;
	}
	for (int i = 0; i < m_pbullet.size(); i++)
	{
		if (m_pbullet[i] != nullptr)
		{
			if (m_pbullet[i]->getTransform()->position.x >= 900)
			{
				removeChild(m_pbullet[i]);
				m_pbullet[i] = nullptr;
				m_pbullet.erase(m_pbullet.begin() + i);
				m_pbullet.shrink_to_fit();
				break;
			}
		}
	}
	if (m_pBg->getTransform()->position.x <= -(m_pBg->getWidth()/2))
	{
		m_pBg->getTransform()->position.x = 400;
		m_pBg2->getTransform()->position.x = 1200;
	}
	enemytimer--;
	if (enemytimer <=-50)
	{
		m_pEnemys.push_back(new Enemy(1000.0f, rand() % 500 + 100));
		enemytimer = 60;
		if (m_pEnemys.size() != 0)
		{
			for (int i = 0; i < m_pEnemys.size(); i++)
			{
				addChild(m_pEnemys[i]);
			}
		}
	}
	if (m_pEnemys.size() != 0)
	{
		for (int i = 0; i < m_pEnemys.size(); i++)
		{
			m_pEnemys[i]->getTransform()->position.x -= 5;
		}
	}
	EnemyshotCoolDown--;
	if (m_pEnemys.size() != 0)
	{
		if (EnemyshotCoolDown <= -40)
		{
			EnemyshotCoolDown = 40;
			for (int i = 0; i < m_pEnemys.size(); i++)
			{
				m_pEnemybullet.push_back(new bullet(m_pEnemys[i]->getTransform()->position.x - 40.0f, m_pEnemys[i]->getTransform()->position.y, 180));
				SoundManager::Instance().playSound("enemyShot", 0, -1);

			}
		}
	}
	for (int i = 0; i < m_pEnemybullet.size(); i++)
	{
		m_pEnemybullet[i]->getTransform()->position.x -= 6;
	}
	for (int i = 0; i < m_pEnemys.size(); i++)
	{
		if (m_pEnemys[i] != nullptr)
		{
			if (m_pEnemys[i]->getTransform()->position.x <= -100)
			{
				removeChild(m_pEnemys[i]);
				m_pEnemys[i] = nullptr;
				m_pEnemys.erase(m_pEnemys.begin() + i);
				m_pEnemys.shrink_to_fit();
				break;
			}
		}
	}
	for (int i = 0; i < m_pEnemybullet.size(); i++)
	{
		if (m_pEnemybullet[i] != nullptr)
		{
			if (m_pEnemybullet[i]->getTransform()->position.x <= -100)
			{
				removeChild(m_pEnemybullet[i]);
				m_pEnemybullet[i] = nullptr;
				m_pEnemybullet.erase(m_pEnemybullet.begin() + i);
				m_pEnemybullet.shrink_to_fit();
				break;
			}
		}
	}
	for (int i = 0; i < m_pbullet.size(); i++)
	{
		for (int j = 0; j < m_pEnemys.size(); j++)
		{
			if (CollisionManager::AABBCheck(m_pbullet[i], m_pEnemys[j]))
			{
				removeChild(m_pbullet[i]);
				m_pbullet[i] = nullptr;
				m_pbullet.erase(m_pbullet.begin() + i);
				m_pbullet.shrink_to_fit();


				removeChild(m_pEnemys[i]);
				m_pEnemys[i] = nullptr;
				m_pEnemys.erase(m_pEnemys.begin() + i);
				m_pEnemys.shrink_to_fit();
				SoundManager::Instance().playSound("enemyDeath", 0, 0);
				std::cout << "YOU KILLED AN ENEMY" << std::endl;

			}
		}
	}
	if (m_pSpaceShip != nullptr)
	{
		for (int j = 0; j < m_pEnemybullet.size(); j++)
		{
			if (CollisionManager::AABBCheck(m_pSpaceShip, m_pEnemybullet[j]))
			{
				removeChild(m_pSpaceShip);
				m_pSpaceShip = nullptr;


				removeChild(m_pEnemybullet[j]);
				m_pEnemybullet[j] = nullptr;
				m_pEnemybullet.erase(m_pEnemybullet.begin() + j);
				m_pEnemybullet.shrink_to_fit();

				TheGame::Instance()->changeSceneState(END_SCENE);
				SoundManager::Instance().playSound("playerDeath", 0, 0);

			}
		}
	}
}

void PlayScene::clean()
{
	for (int i = 0; i < m_pbullet.size(); i++)
	{
		removeChild(m_pbullet[i]);
		m_pbullet[i] = nullptr;
	}
	m_pbullet.shrink_to_fit();
	m_pbullet.clear();
	for (int i = 0; i < m_pEnemys.size(); i++)
	{
		removeChild(m_pEnemys[i]);
		m_pEnemys[i] = nullptr;
	}
	m_pEnemys.shrink_to_fit();
	m_pEnemys.clear();
	for (int i = 0; i < m_pEnemybullet.size(); i++)
	{
		removeChild(m_pEnemybullet[i]);
		m_pEnemybullet[i] = nullptr;
	}
	m_pEnemybullet.shrink_to_fit();
	m_pEnemybullet.clear();
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();
	if (m_pSpaceShip != nullptr)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pSpaceShip->getTransform()->position.x -= 5;
		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pSpaceShip->getTransform()->position.x += 5;
		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_pSpaceShip->getTransform()->position.y -= 5;
		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
		{
			m_pSpaceShip->getTransform()->position.y += 5;
		}
		shotCoolDown--;
		if ((EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE)))
		{
			if (shotCoolDown <= -10)
			{
				shotCoolDown = 10;
				m_pbullet.push_back(new bullet(m_pSpaceShip->getTransform()->position.x + 40.0f, m_pSpaceShip->getTransform()->position.y, 0));
				SoundManager::Instance().playSound("shot", 0, 0);

			}
		}
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		if (shotCoolDown <= -10)
		{
			shotCoolDown = 10;
			std::cout << "Paused" << std::endl;
			if (m_pPauseMenu->getPaused())
			{
				std::cout << " NOT Paused" << std::endl;
				m_pPauseMenu->setPaused(false);
			}
			else
			{
				std::cout << "Paused" << std::endl;
				m_pPauseMenu->setPaused(true);
			}
		}
	}

}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	m_pBg = new Background();
	m_pBg->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pBg);

	m_pBg2 = new Background();
	m_pBg2->getTransform()->position = glm::vec2(1200.0f, 300.0f);
	addChild(m_pBg2);

	m_pSpaceShip = new Spaceship();
	m_pSpaceShip->getTransform()->position = glm::vec2(200.0f, 300.0f);
	addChild(m_pSpaceShip);


	SoundManager::Instance().load("../Assets/audio/shot.mp3", "shot", SOUND_SFX);
	SoundManager::Instance().setSoundVolume(10);

	SoundManager::Instance().load("../Assets/audio/enemyDeath.mp3", "enemyDeath", SOUND_SFX);
	SoundManager::Instance().setSoundVolume(10);

	SoundManager::Instance().load("../Assets/audio/enemyShot.mp3", "enemyShot", SOUND_SFX);
	SoundManager::Instance().setSoundVolume(10);

	SoundManager::Instance().load("../Assets/audio/playerDeath.mp3", "playerDeath", SOUND_SFX);
	SoundManager::Instance().setSoundVolume(10);

	SoundManager::Instance().load("../Assets/audio/Queen.mp3", "Queen", SOUND_MUSIC);
	SoundManager::Instance().setMusicVolume(100);
	SoundManager::Instance().playMusic("Queen", 0);

	m_pPauseMenu = new PauseMenu();
	addChild(m_pPauseMenu);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}