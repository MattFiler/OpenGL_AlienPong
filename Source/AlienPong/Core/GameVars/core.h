#pragma once

#ifndef GAMEVARS_CORE_H
#define GAMEVARS_CORE_H

namespace pongVariables 
{
	//Freeze/reset ball?
	extern bool freeze_ball;
	extern bool reset_ball;

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