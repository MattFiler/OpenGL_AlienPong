#include "Game_vars.h"



/*

//////// PONG - Created by Matt Filer ////////
//////////// GAME VARIABLE HEADER ////////////

*/



/*
	Score counters
*/
GameVars_Scores::GameVars_Scores()
{
	//Set default scores
	p1 = 0;
	p2 = 0;

	scoreboard_p1 = 0;
	scoreboard_p2 = 0;
	scoreboard_player = 0;
	scoreboard_cpu = 0;
}

/*
	FX variables
*/
GameVars_FX::GameVars_FX()
{
	//Set default params for custom FX
	is_performing = false;
	has_requested = false;
	has_finished_cycle = false;
	time_started = 0.0;
	time_in_seconds = 0.07;
}

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