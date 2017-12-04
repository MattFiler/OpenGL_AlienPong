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
#include "AlienPong/Core/enum_values.h"
#include "AlienPong/Core/GameVars.h"
#include "AlienPong/Animation/effects.h"

//Windows-only Resources
#ifdef _WIN32
	#include <windows.h>
	#include <mmsystem.h>
#endif

/*
IS_PAUSED
*/

#ifndef IS_PAUSED_H
#define IS_PAUSED_H

class gamestateIsPaused
{
public:
	//Deconstructor
	~gamestateIsPaused();

	//Key Handler
	void keyHandler(ASGE::SharedEventData data);

	//Renderer
	void renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer);

	//Updater
	void updateState(const ASGE::GameTime & us);

	//Load Sprites
	void loadSprites(ASGE::Renderer* renderer);


private:
	//Global effects
	pongVHS pong_vhs;


	ASGE::Sprite* menu_overlay_paused = nullptr; //in-game PAUSE screen
};

#endif