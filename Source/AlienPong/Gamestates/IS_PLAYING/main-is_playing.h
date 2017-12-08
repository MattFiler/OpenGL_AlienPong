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
#include "AlienPong/Core/structs.h"
#include "AlienPong/Animation/effects.h"
#include "AlienPong/Core/GameFont/GameFont.h"
#include "AlienPong/Core/shared.h"

//Windows-only Resources
#ifdef _WIN32
	#include <windows.h>
	#include <mmsystem.h>
#endif

/*
IS_PLAYING
*/

#ifndef IS_PLAYING_H
#define IS_PLAYING_H

class gamestateIsPlaying
{
public:
	//Deconstructor
	~gamestateIsPlaying();

	//Key Handler
	void keyHandler(ASGE::SharedEventData data);

	//Renderer
	void renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer);

	//Updater
	void updateState(const ASGE::GameTime & us);

	//Load sprites
	void loadSprites(ASGE::Renderer* renderer);


private:
	//Shared
	pongShared pong_shared;

	//Pong Directions
	pongDirections pong_directions;

	//Pong Variables
	pongVariables pong_variables;

	//Pong Scores
	pongScores pong_scores;

	//Pong Gamestate
	pongGamestate pong_gamestate;

	//Pong Gamemodes
	pongGamemodes pong_gamemode;

	//Pong Animation State
	pongAnimationState pong_animation;


	ASGE::Sprite* paddle1 = nullptr; //Paddle 1
	ASGE::Sprite* paddle2 = nullptr; //Paddle 2
	ASGE::Sprite* ball1 = nullptr; //Ball

	ASGE::Sprite* menu_overlay_mode_regular = nullptr; //in-game MODE overlay regular
	ASGE::Sprite* menu_overlay_mode_timed = nullptr; //in-game MODE overlay timed
	ASGE::Sprite* menu_overlay_mode_score = nullptr; //in-game MODE overlay score
	ASGE::Sprite* menu_overlay_score_box = nullptr; //in-game score box overlay
};

#endif