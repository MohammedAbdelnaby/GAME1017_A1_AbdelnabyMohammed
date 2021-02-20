#include "Enemy.h"

Enemy::Enemy(float x, float y)
{
	TextureManager::Instance()->load("../Assets/textures/enemy.png", "enemy");
	auto size = TextureManager::Instance()->getTextureSize("enemy");
	setWidth(size.x);
	setHeight(size.y);
	setType(ENEMY);
	getTransform()->position = glm::vec2(x, y);
}

Enemy::~Enemy()
{
	std::cout << "De-allocating Enemy at " << &(*this) << std::endl;
}

void Enemy::draw()
{
	TextureManager::Instance()->draw("enemy", getTransform()->position.x, getTransform()->position.y, 270, 255, true);
}

void Enemy::update()
{
	
}

void Enemy::clean()
{
}
