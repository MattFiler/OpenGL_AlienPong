#pragma once
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>
#include "Pong/Definitions/enums/settings.h"
#include "Pong/Definitions/enums/animationState.h"
#include "Pong/Definitions/GameVars/core.h"

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
	~pongVHS();

	void renderFX();

	animationState pongfx_state;
	float time_started;
	float time_in_seconds;

private:
	GameVars_Core pong_vars;

	void loadSprites(std::shared_ptr<ASGE::Renderer> renderer);

	ASGE::Sprite* menu_background = nullptr; //Menu background
	ASGE::Sprite* menu_background_s00 = nullptr; //Menu background s00
	ASGE::Sprite* menu_background_s01 = nullptr; //Menu background s01
	ASGE::Sprite* menu_background_s02 = nullptr; //Menu background s02
	ASGE::Sprite* menu_background_s03 = nullptr; //Menu background s03
	ASGE::Sprite* menu_background_s04 = nullptr; //Menu background s04
};

#endif