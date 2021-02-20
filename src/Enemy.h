#pragma once
#ifndef __ENEMYS__
#define __DEFINE__
#include "DisplayObject.h"
#include "TextureManager.h"
class Enemy : public DisplayObject
{
public:
	Enemy(float x, float y);
	~Enemy();

	// Life Cycle Functions
	void draw() override;
	void update() override;
	void clean() override;
private:


};
#endif // !__ENEMYS__

