#pragma once

#ifndef GAMEVARS_FX_H
#define GAMEVARS_FX_H

namespace pongFX
{
	//Start/stop checkers
	extern bool is_performing;
	extern bool has_requested;
	extern bool has_finished_cycle;

	//Timers
	extern float time_started;
	extern float time_in_seconds;
}

#endif