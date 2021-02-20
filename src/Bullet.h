#pragma once
#ifndef __BULLET__
#define __BULLET__
#include "DisplayObject.h"
#include "TextureManager.h"
class bullet : public DisplayObject
{
public:
	bullet(float x, float y, int r);
	~bullet();

	// Life Cycle Functions
	void draw() override;
	void update() override;
	void clean() override;
private:
	int m_rotation;

};
#endif // !__BULLET__

