#pragma once
#include "../enums/direction.h"

#ifndef ENUM_VALS_DIRECTION_H
#define ENUM_VALS_DIRECTION_H

/*
Define our direction data
*/
namespace pongDirections
{
	extern direction ball_direction;
	extern direction left_paddle_direction;
	extern direction right_paddle_direction;

	extern bool right_paddle_moving;
	extern bool left_paddle_moving;

	extern int movement_angle;
	extern int movement_angle_raw;
}

#endif