#pragma once

//Engine Resources
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>

//Extra Resources
#include <string>

//AlienPong Resources
#include "AlienPong/Core/enums.h"
#include "AlienPong/Core/structs.h"

//Windows-only Resources
#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#endif

#ifndef SHARED_H
#define SHARED_H

/*
Shared classes
*/
class pongShared
{
public:
	//Reset game
	void reset();

	//Hit detection
	bool isTouchingPaddle(const ASGE::Sprite* sprite, float x, float y, std::string spriteName) const;

	//Calculate return angles
	int calculateReturnAngle(const ASGE::Sprite* paddle, bool include_reverses, const ASGE::Sprite* ball1) const;

	//Has hit edge?
	bool hasHitEdge(std::string edgeName, const ASGE::Sprite* ball1) const;

	//Handle winner
	void handleWin(std::string winner_name);


private:
	//Pong Scores
	pongScores pong_scores;

	//Pong Gamestate
	pongGamestate pong_gamestate;

	//Pong Gamemode
	pongGamemodes pong_gamemode;

	//Pong Menu State
	pongMenuState pong_menu_state;

	//Pong Variables
	pongVariables pong_variables;

	//Pong Directions
	pongDirections pong_directions;

	//Pong Players
	pongPlayers pong_players;
};

#endif