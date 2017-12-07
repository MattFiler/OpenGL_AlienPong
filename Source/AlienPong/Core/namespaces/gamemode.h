#pragma once
#include "../enums/gamemode.h"

#ifndef ENUM_VALS_GAMEMODE_H
#define ENUM_VALS_GAMEMODE_H

/*
Define our gamemode data
*/
namespace pongGamemodes
{
	extern gamemode current_gamemode;
	extern bool is_against_cpu;
}

#endif