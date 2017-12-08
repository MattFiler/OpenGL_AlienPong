#pragma once
#include "../enums/direction.h"

#ifndef ENUM_VALS_DIRECTION_H
#define ENUM_VALS_DIRECTION_H

/*
Define our direction data
*/
struct pongDirections
{
	static direction ball_direction;
	static direction left_paddle_direction;
	static direction right_paddle_direction;

	static bool right_paddle_moving;
	static bool left_paddle_moving;

	static int movement_angle;
	static int movement_angle_raw;
};

#endif