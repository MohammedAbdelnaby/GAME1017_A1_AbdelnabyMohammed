#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "BackGround.h"
#include "Spaceship.h"
#include <vector>
#include "Bullet.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include <sstream> 
#include <iomanip> 
#include "PauseMenu.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	glm::vec2 m_mousePosition;
	Background* m_pBg;
	Background* m_pBg2;
	Spaceship* m_pSpaceShip;
	std::vector<bullet*> m_pbullet;
	std::vector<Enemy*> m_pEnemys;
	int enemytimer = 60;
	int shotCoolDown = 10;
	std::vector<bullet*> m_pEnemybullet;
	int EnemyshotCoolDown = 40;
	PauseMenu* m_pPauseMenu;

};

#endif /* defined (__PLAY_SCENE__) */