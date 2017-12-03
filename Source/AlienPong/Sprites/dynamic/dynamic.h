#pragma once

//Engine Resources
#include <Engine/OGLGame.h>
#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>
#include <Engine/Renderer.h>

//Extra Resources
#include <string>

//AlienPong Resources
#include "AlienPong/Core/enums.h"

//Windows-only Resources
#ifdef _WIN32
	#include <windows.h>
	#include <mmsystem.h>
#endif

/*
Dynamic Sprites
*/

#ifndef DYNAMIC_SPRITES
#define DYNAMIC_SPRITES

class spritesDynamic
{
public:
	spritesDynamic();
	~spritesDynamic();

	void loadSprites(ASGE::Renderer* renderer);

	ASGE::Sprite* paddle1 = nullptr; //Paddle 1
	ASGE::Sprite* paddle2 = nullptr; //Paddle 2
	ASGE::Sprite* ball1 = nullptr; //Ball
};

#endif