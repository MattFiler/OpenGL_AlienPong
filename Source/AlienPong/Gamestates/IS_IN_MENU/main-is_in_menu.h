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
#include "AlienPong/Core/namespaces.h"
#include "AlienPong/Core/GameFont/GameFont.h"
#include "AlienPong/Animation/effects.h"
#include "AlienPong/Core/PongPak/PongPak.h"

//Windows-only Resources
#ifdef _WIN32
	#include <windows.h>
	#include <mmsystem.h>
#endif

/*
IS_IN_MENU
*/

#ifndef IS_IN_MENU_H
#define IS_IN_MENU_H

class gamestateIsInMenu
{
public:
	//Deconstructor
	~gamestateIsInMenu();

	//Key Handler
	void keyHandler(ASGE::SharedEventData data);

	//Renderer
	void renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer);

	//Load Sprites
	void loadSprites(ASGE::Renderer* renderer);


private:
	ASGE::Sprite* menu_overlay_twoPlayer = nullptr; //Menu TwoPlayer overlay
	ASGE::Sprite* menu_overlay_onePlayer = nullptr; //Menu OnePlayer overlay
	ASGE::Sprite* menu_overlay_controls = nullptr; //Menu controls overlay
	ASGE::Sprite* menu_overlay_scoreboard = nullptr; //Menu scores overlay
};

#endif