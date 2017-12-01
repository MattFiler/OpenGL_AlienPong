#pragma once
#include "../enums/gamemode.h"

class gamemodeValues
{
public:
	gamemodeValues();

	gamemode current_gamemode;
	bool is_against_cpu;
};