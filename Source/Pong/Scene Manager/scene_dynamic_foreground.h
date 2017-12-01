#pragma once
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>
#include <Engine/Renderer.h>
#include "Pong/Definitions/enums/settings.h"
#include <memory>

/*
	// PONG REWORK 3 //

	---SCENE MANAGER
	Handle dynamic foreground elements
*/

#ifndef SCENE_DYN_FOREGROUND_H
#define SCENE_DYN_FOREGROUND_H

class sceneDynamicForeground
{
public:
	sceneDynamicForeground();
	~sceneDynamicForeground();

	void loadSprites(ASGE::Renderer* renderer);

	ASGE::Sprite* paddle1 = nullptr; //Paddle 1
	ASGE::Sprite* paddle2 = nullptr; //Paddle 2
	ASGE::Sprite* ball1 = nullptr; //Ball
};

#endif