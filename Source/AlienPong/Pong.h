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
	//PongPAK (file handler)
	PongPAK pong_filehandler;

	//Global effects
	pongVHS pong_vhs;

	//Gamestates
	gamestateIsGameOver pong_gamestate_gameover;
	gamestateIsInLoadscreen pong_gamestate_loadscreen;
	gamestateIsInMenu pong_gamestate_menu;
	gamestateIsPaused pong_gamestate_paused;
	gamestateIsPlaying pong_gamestate_playing;
	gamestatePlayerHasWon pong_gamestate_scored;


	//Engine functions
	void keyHandler(ASGE::SharedEventData data);
	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;

	//Engine Values
	bool exit = false;
	int  key_callback_id = -1;

	//Asset loader (through PongPAK)
	void loadAssets();


	ASGE::Sprite* menu_background = nullptr; //Menu background
	ASGE::Sprite* monitor_overlay = nullptr;  //monitor overlay effect
};

#endif