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

//Windows-only Resources
#ifdef _WIN32
	#include <windows.h>
	#include <mmsystem.h>
#endif

/*
PLAYER_HAS_WON
*/

#ifndef PLAYER_HAS_WON_H
#define PLAYER_HAS_WON_H

class gamestatePlayerHasWon
{
public:
	//Deconstructor
	~gamestatePlayerHasWon();

	//Key Handler
	void keyHandler(ASGE::SharedEventData data);

	//Renderer
	void renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer);

	//Load Sprites
	void loadSprites(ASGE::Renderer* renderer);


private:
	//Pong Directions
	pongDirections pong_directions;

	//Pong Gamestate
	pongGamestate pong_gamestate;

	//Pong Players
	pongPlayers pong_players;


	ASGE::Sprite* menu_overlay_score_p1 = nullptr; //in-game SCORE screen - P1
	ASGE::Sprite* menu_overlay_score_p2 = nullptr; //in-game SCORE screen - P2
	ASGE::Sprite* menu_overlay_score_player = nullptr; //in-game SCORE screen - PLAYER
	ASGE::Sprite* menu_overlay_score_cpu = nullptr; //in-game SCORE screen - CPU
};

#endif