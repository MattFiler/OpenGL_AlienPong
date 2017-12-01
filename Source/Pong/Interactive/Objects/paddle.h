#pragma once
#include <Engine/OGLGame.h>
#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include "Pong/Definitions/enums/direction.h"
#include "Pong/Definitions/GameVars/core.h"
#include "Pong/Definitions/enum_values/gamemode.h"

/*
	// PONG REWORK 3 //

	---INTERACTIVE
	Handle our paddles.
*/

#ifndef INT_PADDLE_H
#define INT_PADDLE_H

class pongPaddles
{
public:
	pongPaddles();

	bool left_paddle_moving;
	direction left_paddle_direction;

	bool right_paddle_moving;
	direction right_paddle_direction;
private:
	GameVars_Core pong_vars;
	gamemodeValues gamemode;
};

#endif