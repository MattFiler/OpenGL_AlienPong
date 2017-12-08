#include "../structs.h"

#ifndef DEFINE_ALIENPONG_GAMEMODE
#define DEFINE_ALIENPONG_GAMEMODE

/*
	Set all pongGamemodes values
*/

//Default gamemodes
gamemode pongGamemodes::current_gamemode = gamemode::NO_GAMEMODE;
bool pongGamemodes::is_against_cpu = false;

#endif