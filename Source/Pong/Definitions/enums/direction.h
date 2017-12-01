#pragma once

#ifndef ENUMS_DIRECTION_H
#define ENUMS_DIRECTION_H

/* 
	Define our movement motivation directions.
*/
enum class direction : int
{
	NO_DIRECTION, //Default movement state

	UP, //Motivated movement up
	DOWN, //Motivated movement down
	LEFT, //Motivated movement left
	RIGHT //Motivated movement right
};

#endif