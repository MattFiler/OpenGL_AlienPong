#pragma once
#include <Engine/OGLGame.h>

#ifdef _WIN32
	#include <windows.h>
	#include <mmsystem.h>
#endif

/*
	// PONG REWORK 3 //

	---INTERACTIVE
	UI interaction sound effects.
*/

#ifndef INT_UISFX_H
#define INT_UISFX_H

class pongUISFX
{
public:
	pongUISFX();
	void pongUISFX::playSound(int sound_id);
};

#endif