#pragma once
#include "../enums/gamemode.h"

#ifndef ENUM_VALS_GAMEMODE_H
#define ENUM_VALS_GAMEMODE_H

/*
Define our gamemode data
*/
struct pongGamemodes
{
	static gamemode current_gamemode;
	static bool is_against_cpu;
};

#endif