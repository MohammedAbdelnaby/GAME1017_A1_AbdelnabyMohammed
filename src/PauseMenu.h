#pragma once
#ifndef __PAUSEMENU__
#define __PAUSEMENU__
#include "Button.h"
#include "DisplayObject.h"
#include "TextureManager.h"
class PauseMenu  : public DisplayObject
{
public:
	PauseMenu();
	~PauseMenu();
	void draw() override;
	void update() override;
	void clean() override;
	void setPaused(bool paused);
	bool getPaused();
private:
	bool m_Ispaused = false;
	Button* m_pResume;
};
#endif /* DEFINED (__PAUSEMENU__) */