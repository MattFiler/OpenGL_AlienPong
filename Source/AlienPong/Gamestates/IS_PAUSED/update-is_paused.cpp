#include "main-is_paused.h"

/*
Update game
*/
void gamestateIsPaused::updateState(const ASGE::GameTime & us) 
{
	//Freeze ball on pause
	pongVariables::freeze_ball = true;
}