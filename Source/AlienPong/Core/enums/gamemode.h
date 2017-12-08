#pragma once

#ifndef ENUMS_GAMEMODE_H
#define ENUMS_GAMEMODE_H

/*
	Define our available gamemodes.
*/
enum class gamemode : int 
{
	NO_GAMEMODE, //Default menu state (no mode in progress)
	GAMEMODE_INFINITE, //Infinite gamemode
	GAMEMODE_TIMED, //Timed gamemode
	GAMEMODE_SCORE, //First to 5 gamemode
	GAMEMODE_CRAZY
};

#endif