#pragma once

#ifndef GAMEVARS_CORE_H
#define GAMEVARS_CORE_H

/*
Define our generic global variables
*/
struct pongVariables 
{
	//Freeze/reset ball & paddles?
	static bool freeze_ball;
	static bool reset_ball;
	static bool reset_paddles;

	//Timers
	static float game_timer;
	static float global_game_timer;

	//CPU modifiers
	static int cpu_speed_modifier_check;
	static float cpu_speed_modifier;

	//Audio checks
	static bool has_performed_startup_sound;

	//Paddle Size
	static float paddle_height;
};

#endif