#pragma once
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>
#include <Engine/Renderer.h>
#include "Pong/Definitions/enums/settings.h"
#include <memory>

/*
	// PONG REWORK 3 //

	---SCENE MANAGER
	Handle foreground element
*/

#ifndef SCENE_FOREGROUND_H
#define SCENE_FOREGROUND_H

class sceneForeground
{
public:
	sceneForeground();
	~sceneForeground();

	void loadSprites(std::shared_ptr<ASGE::Renderer> renderer);

	ASGE::Sprite* monitor_overlay = nullptr;  //monitor overlay effect
};

#endif