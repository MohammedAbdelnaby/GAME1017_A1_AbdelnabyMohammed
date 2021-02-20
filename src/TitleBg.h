#pragma once
#ifndef __TITLEBG__
#define __TITLEBG__
#include "DisplayObject.h"
#include "TextureManager.h"
class TitleBg : public DisplayObject
{
public:
	TitleBg();
	~TitleBg();

	// Life Cycle Functions
	void draw() override;
	void update() override;
	void clean() override;
private:

};
#endif // !__TITLEBG__
