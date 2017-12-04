#pragma once

//Engine Resources
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>

//Extra Resources
#include <string>

//AlienPong Resources
#include "AlienPong/Core/enums.h"
#include "AlienPong/Core/enum_values.h"
#include "AlienPong/Core/GameVars.h"

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
};

#endif