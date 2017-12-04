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
IS_IN_LOADSCREEN
*/

#ifndef IS_IN_LOADSCREEN_H
#define IS_IN_LOADSCREEN_H

class gamestateIsInLoadscreen
{
public:
	//Deconstructor
	~gamestateIsInLoadscreen();

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


	ASGE::Sprite* menu_overlay_loading = nullptr; //Menu loading overlay
	ASGE::Sprite* menu_overlay_loading_s0 = nullptr; //Menu loading overlay S0
	ASGE::Sprite* menu_overlay_loading_s1 = nullptr; //Menu loading overlay S1
	ASGE::Sprite* menu_overlay_loading_s2 = nullptr; //Menu loading overlay S2
	ASGE::Sprite* menu_overlay_loading_s3 = nullptr; //Menu loading overlay S3
	ASGE::Sprite* menu_overlay_loading_s4 = nullptr; //Menu loading overlay S4
	ASGE::Sprite* menu_overlay_loading_s5 = nullptr; //Menu loading overlay S5
};

#endif