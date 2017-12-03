#include "core.h"

/*
Core game variables
*/
GameVars_Core::GameVars_Core()
{
	//Default timers and runtime modifiers
	freeze_ball = true;
	game_timer = 0;
	global_game_timer = 0;
	cpu_speed_modifier_check = 0;
	cpu_speed_modifier = 2;

	//Set audio checks
	has_performed_startup_sound = false;
}