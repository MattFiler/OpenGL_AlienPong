#include "../structs.h"

#ifndef DEFINE_ALIENPONG_GAMESTATE
#define DEFINE_ALIENPONG_GAMESTATE

/*
Set all pongGamestate values
*/

//Default gamestate
gamestate pongGamestate::current_gamestate = gamestate::IS_IN_LOADSCREEN;

//Show debug text?
bool pongGamestate::show_debug_text = false; //Do not enable on final build.

//User wants to close?
bool pongGamestate::has_requested_shutdown = false;

#endif