#pragma once
#include "scene_background.h"
#include "scene_dynamic_foreground.h"
#include "scene_static_foreground.h"
#include "scene_foreground.h"

#ifndef SCENE_H
#define SCENE_H

class sceneManager
{
public:
	sceneManager();
	~sceneManager();

	void renderBackground(ASGE::Renderer* renderer, ASGE::Sprite* menu_background);
	void renderLoadscreen();
	void renderMenuPage1();
	void renderMenuPage2();
	void renderInGame();
	void renderPauseMenu();
	void renderScoreScreen();

private:
	sceneBackground background;
	sceneStaticForeground static_foreground;
	sceneDynamicForeground dynamic_foreground;
	sceneForeground foreground;
};

#endif