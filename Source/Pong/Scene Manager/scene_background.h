#pragma once
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>
#include <Engine/Renderer.h>
#include "Pong/Definitions/enums/settings.h"
#include <memory>

/*
	// PONG REWORK 3 //

	---SCENE MANAGER
	Handle background elements
*/

#ifndef SCENE_BACKGROUND_H
#define SCENE_BACKGROUND_H

class sceneBackground
{
public:
	sceneBackground();
	~sceneBackground();

	void loadSprites(ASGE::Renderer* renderer);

	ASGE::Sprite* menu_background = nullptr; //Menu background
	ASGE::Sprite* menu_background_s00 = nullptr; //Menu background s00
	ASGE::Sprite* menu_background_s01 = nullptr; //Menu background s01
	ASGE::Sprite* menu_background_s02 = nullptr; //Menu background s02
	ASGE::Sprite* menu_background_s03 = nullptr; //Menu background s03
	ASGE::Sprite* menu_background_s04 = nullptr; //Menu background s04
};

#endif