#include "direction.h"

directionValues::directionValues()
{
	ball_direction = direction::RIGHT;
	left_paddle_direction = direction::NO_DIRECTION;
	right_paddle_direction = direction::NO_DIRECTION;
	right_paddle_moving = false;
	left_paddle_moving = false;
	movement_angle = 0;
	movement_angle_raw = 0;
}