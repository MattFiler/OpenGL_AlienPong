#pragma once

#ifndef GAMEVARS_FX_H
#define GAMEVARS_FX_H

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

#endif