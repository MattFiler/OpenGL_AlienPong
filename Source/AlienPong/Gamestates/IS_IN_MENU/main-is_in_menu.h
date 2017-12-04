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
#include "AlienPong/Sprites/sprites.h"

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
	//Key Handler
	void keyHandler(ASGE::SharedEventData data);

	//Renderer
	void renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer);

	//Updater
	void updateState(const ASGE::GameTime & us);


private:
	//Global generic values
	GameVars_FX pong_fx;
	GameVars_Scores pong_points;

	//Global effects
	pongVHS pong_vhs;

	//Sprites
	spritesStatic pong_sprite_static;
	spritesDynamic pong_sprite_dynamic;
};

#endif