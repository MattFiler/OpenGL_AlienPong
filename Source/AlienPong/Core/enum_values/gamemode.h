#pragma once
#include "../enums/gamemode.h"

#ifndef ENUM_VALS_GAMEMODE_H
#define ENUM_VALS_GAMEMODE_H

class gamemodeValues
{
public:
	gamemodeValues();

	gamemode current_gamemode;
	bool is_against_cpu;
};

#endif