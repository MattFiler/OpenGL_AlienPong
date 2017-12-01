#include "fx.h"

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