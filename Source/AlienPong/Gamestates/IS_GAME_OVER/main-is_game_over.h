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
IS_GAME_OVER
*/

#ifndef IS_GAME_OVER_H
#define IS_GAME_OVER_H

class gamestateIsGameOver
{
public:
	//Deconstructor
	~gamestateIsGameOver();

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


	ASGE::Sprite* menu_overlay_win_p1 = nullptr; //in-game WIN screen - P1
	ASGE::Sprite* menu_overlay_win_p2 = nullptr; //in-game WIN screen - P2
	ASGE::Sprite* menu_overlay_win_player = nullptr; //in-game WIN screen - PLAYER
	ASGE::Sprite* menu_overlay_win_cpu = nullptr; //in-game WIN screen - CPU
	ASGE::Sprite* menu_overlay_win_draw = nullptr; //in-game WIN screen - DRAW
};

#endif