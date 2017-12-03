#pragma once

#ifndef ENUMS_SETTINGS_H
#define ENUMS_SETTINGS_H

/*
	Define game settings.
*/
enum class settings : int 
{
	GAMEWINDOW_MAX_WIDTH = 1024, //Game width
	GAMEWINDOW_MAX_HEIGHT = 768, //Game height

	PADDLE_HEIGHT = 150, //Paddle height
	PADDLE_WIDTH = 10, //Paddle width

	BALL_SIZE = 10, //Ball size (height & width)

	DEFAULT_ANGLE_MULTIPLIER = 2, //Maximum return angle from edge of paddle
	HIGH_ANGLE_MULTIPLIER = 3, //High variant of return angle

	DEFAULT_SPEED = 600, //Ball and paddle movement speed (paddles are this divided by two)
	HIGH_SPEED = 1000, //High speed variant

	CPU_SLOW_SPEED_REFRESH = 4, //Rate at which to update the CPU's paddle speed
	CPU_MEDIUM_SPEED_REFRESH = 3, //Slightly faster variant
	CPU_FAST_SPEED_REFRESH = 2, //Fastest variant

	CPU_MODIFIER_EASY = 4, //Maximum speed restrictor for paddle (+2.5)
	CPU_MODIFIER_MEDIUM = 3, //Faster speed variant
	CPU_MODIFIER_HARD = 2 //Fastest speed variant
};

#endif