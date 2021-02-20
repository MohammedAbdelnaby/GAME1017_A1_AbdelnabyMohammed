#include "Bullet.h"

bullet::bullet(float x, float y, int r) :m_rotation(r)
{
	TextureManager::Instance()->load("../Assets/textures/spr_missile_half.png", "bullet");
	auto size = TextureManager::Instance()->getTextureSize("bullet");
	setWidth(size.x);
	setHeight(size.y);
	setType(BULLET);
	getTransform()->position = glm::vec2(x, y);
}

bullet::~bullet()
{
	std::cout << "De-allocating bullet at " << &(*this) << std::endl;
}

void bullet::draw()
{
	TextureManager::Instance()->draw("bullet", getTransform()->position.x, getTransform()->position.y, m_rotation, 255, true);

}

void bullet::update()
{
}

void bullet::clean()
{
}
