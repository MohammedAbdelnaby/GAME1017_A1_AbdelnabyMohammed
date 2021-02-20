#include "TitleBg.h"

TitleBg::TitleBg()
{
	TextureManager::Instance()->load("../Assets/textures/TileScreen.png", "TileScreen");
	auto size = TextureManager::Instance()->getTextureSize("TileScreen");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(400.0f, 300.0f);
}

TitleBg::~TitleBg()
= default;

void TitleBg::draw()
{
	TextureManager::Instance()->draw("TileScreen", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void TitleBg::update()
{
}

void TitleBg::clean()
{
}
