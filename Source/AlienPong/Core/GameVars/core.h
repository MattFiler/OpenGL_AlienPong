#pragma once

#ifndef GAMEVARS_CORE_H
#define GAMEVARS_CORE_H

class GameVars_Core
{
public:
	//Main void
	GameVars_Core();

	//Freeze ball?
	bool freeze_ball;

	//Timers
	float game_timer;
	float global_game_timer;

	//CPU modifiers
	int cpu_speed_modifier_check;
	float cpu_speed_modifier;

	//Audio checks
	bool has_performed_startup_sound;
};

#endif