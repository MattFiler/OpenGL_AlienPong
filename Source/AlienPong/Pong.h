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
#include "AlienPong/Core/GameFont/GameFont.h"
#include "AlienPong/Animation/effects.h"
#include "AlienPong/Gamestates/gamestates.h"
#include "AlienPong/Core/PongPAK/PongPAK.h"

//Windows-only Resources
#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#endif

struct GameFont;

/*

//////// PONG - Created by Matt Filer ////////
//////////////// GAME HEADER /////////////////

*/

#ifndef GAME_H
#define GAME_H

class Pong :
	public ASGE::OGLGame
{
public:
	Pong();
	~Pong();
	virtual bool init() override;

private:
	//Global enum values
	directionValues pong_direction;
	gamemodeValues pong_gamemode;
	gamestateValues pong_gamestate;
	player pong_player;

	//Global generic values
	GameVars_FX pong_fx;
	GameVars_Core pong_vars;
	GameVars_Scores pong_points;

	//PongPAK (file handler)
	PongPAK pong_filehandler;

	//Global effects
	pongVHS pong_vhs;

	//Engine functions
	void keyHandler(ASGE::SharedEventData data);
	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;

	//Engine Values
	bool exit = false;
	int  key_callback_id = -1;

	//Asset loader (through PongPAK)
	void loadAssets();
};

#endif