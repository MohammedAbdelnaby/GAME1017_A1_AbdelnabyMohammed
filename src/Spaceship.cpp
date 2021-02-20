#include "Spaceship.h"

Spaceship::Spaceship()
{
	TextureManager::Instance()->load("../Assets/textures/spaceShip.png", "spaceShip");
	auto size = TextureManager::Instance()->getTextureSize("spaceShip");
	setWidth(size.x);
	setHeight(size.y);
	setType(SPACESHIP);
	getTransform()->position = glm::vec2(400.f, 300.0f);
}

Spaceship::~Spaceship()
= default;

void Spaceship::draw()
{
	TextureManager::Instance()->draw("spaceShip", getTransform()->position.x, getTransform()->position.y , 90, 255, true);

}

void Spaceship::update()
{
}

void Spaceship::clean()
{
}
