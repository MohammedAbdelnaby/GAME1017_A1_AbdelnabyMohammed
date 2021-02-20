#pragma once
#ifndef __SPACESHIP__
#define __SPACESHIP__
#include "DisplayObject.h"
#include "TextureManager.h"
class Spaceship : public DisplayObject
{
public:
	Spaceship();
	~Spaceship();

	// Life Cycle Functions
	void draw() override;
	void update() override;
	void clean() override;

private:
};
#endif // !__SPACESHIP__
