#include "main-is_paused.h"

/*
Update game
*/
void gamestateIsPaused::updateState(const ASGE::GameTime & us) 
{
	//Freeze ball on pause
	pong_variables.freeze_ball = true;

	//Stop paddles moving
	pong_directions.left_paddle_moving = false;
	pong_directions.right_paddle_moving = false;
}