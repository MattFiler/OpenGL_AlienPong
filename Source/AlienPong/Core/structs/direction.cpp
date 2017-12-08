#include "../structs.h"

#ifndef DEFINE_ALIENPONG_DIRECTION
#define DEFINE_ALIENPONG_DIRECTION

/*
	Set all pongDirections values
*/

//Directions
direction pongDirections::ball_direction = direction::RIGHT;
direction pongDirections::left_paddle_direction = direction::NO_DIRECTION;
direction pongDirections::right_paddle_direction = direction::NO_DIRECTION;

//Moving?
bool pongDirections::right_paddle_moving = false;
bool pongDirections::left_paddle_moving = false;

//Angles
int pongDirections::movement_angle = 0;
int pongDirections::movement_angle_raw = 0;

#endif