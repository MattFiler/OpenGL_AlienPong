#pragma once


/*

//////// PONG - Created by Matt Filer ////////
/////////////// GAME VARIABLES ///////////////

*/



class GameVars_Scores 
{
public:
	//Main void
	GameVars_Scores();

	//In-game scores
	int p1;
	int p2;

	//Scoreboard 
	int scoreboard_p1;
	int scoreboard_p2;
	int scoreboard_player;
	int scoreboard_cpu;
};

class GameVars_FX 
{
public:
	//Main void
	GameVars_FX();

	//Start/stop checkers
	bool is_performing;
	bool has_requested;
	bool has_finished_cycle;

	//Timers
	float time_started;
	float time_in_seconds;
};

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