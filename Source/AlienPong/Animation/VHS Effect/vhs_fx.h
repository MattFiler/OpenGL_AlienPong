#pragma once

//Engine Definitions
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>

//Game definitions
#include "AlienPong/Core/enums.h"
#include "AlienPong/Core/enum_values.h"
#include "AlienPong/Core/GameVars.h"

#ifndef VHS_FX_H
#define VHS_FX_H

//Pong VHS animation
class pongVHS
{
public:
	~pongVHS(); 

	void loadSprites(ASGE::Renderer* renderer);
	void renderFX(ASGE::Renderer* renderer);


private:
	ASGE::Sprite* menu_background_s00 = nullptr; //Menu background s00
	ASGE::Sprite* menu_background_s01 = nullptr; //Menu background s01
	ASGE::Sprite* menu_background_s02 = nullptr; //Menu background s02
	ASGE::Sprite* menu_background_s03 = nullptr; //Menu background s03
	ASGE::Sprite* menu_background_s04 = nullptr; //Menu background s04
};

#endif