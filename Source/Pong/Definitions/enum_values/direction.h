#pragma once
#include "../enums/direction.h"

class directionValues
{
public:
	directionValues();

	direction ball_direction;
	direction left_paddle_direction;
	direction right_paddle_direction;
	bool right_paddle_moving;
	bool left_paddle_moving;
	int movement_angle;
	int movement_angle_raw;
};