#pragma once

#ifndef ENUMS_PLAYER_H
#define ENUMS_PLAYER_H

/*
	Define our player types.
*/
enum class player : int 
{
	PLAYER_NULL, //Null player for game load

	PLAYER_P1, //Player 1 (PVP Left Side)
	PLAYER_P2, //Player 2 (PVP Right Side)

	PLAYER_HUMAN, //Human (CVP Left Side)
	PLAYER_CPU //Computer (CVP Right Side)
};

#endif