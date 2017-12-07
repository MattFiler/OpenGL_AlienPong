#pragma once

#ifndef GAMEVARS_CORE_H
#define GAMEVARS_CORE_H

/*
Define our generic global variables
*/
namespace pongVariables 
{
	//Freeze/reset ball & paddles?
	extern bool freeze_ball;
	extern bool reset_ball;
	extern bool reset_paddles;

	//Timers
	extern float game_timer;
	extern float global_game_timer;

	//CPU modifiers
	extern int cpu_speed_modifier_check;
	extern float cpu_speed_modifier;

	//Audio checks
	extern bool has_performed_startup_sound;
}

#endif