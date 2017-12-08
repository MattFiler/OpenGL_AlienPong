#pragma once
#include "../enums/gamestate.h"

#ifndef ENUM_VALS_GAMESTATE_H
#define ENUM_VALS_GAMESTATE_H

/*
Define our gamestate data
*/
struct pongGamestate
{
	static gamestate current_gamestate;
	static bool show_debug_text;
	static bool has_requested_shutdown;
};

#endif