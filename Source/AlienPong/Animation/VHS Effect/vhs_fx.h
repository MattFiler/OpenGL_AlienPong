#pragma once

//Engine Definitions
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>

//Game definitions
#include "AlienPong/Core/enums.h"
#include "AlienPong/Core/GameVars.h"
#include "AlienPong/Sprites/sprites.h"

#ifndef VHS_FX_H
#define VHS_FX_H

/*
	// PONG REWORK 3 //

	---ANIMATION
	Handle our VHS effect.
*/

class pongVHS
{
public:
	pongVHS(); 

	void renderFX();

	animationState pongfx_state;
	float time_started;
	float time_in_seconds;

private:
	GameVars_Core pong_vars;
	spritesStatic pong_sprite_static;
};

#endif