#pragma once

#ifndef ENUMS_GAMESTATE_H
#define ENUMS_GAMESTATE_H

/*
	Define all gamestates.
*/
enum class gamestate : int 
{
	IS_IN_LOADSCREEN, //In initial loadscreen
	IS_IN_MENU, //In main menu
	IS_PLAYING, //In-game
	IS_PAUSED, //Paused
	PLAYER_HAS_WON, //Player scored a point
	IS_GAME_OVER //Player has won
};

#endif