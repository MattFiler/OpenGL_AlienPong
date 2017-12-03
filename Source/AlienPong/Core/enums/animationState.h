#pragma once

#ifndef ENUMS_ANIMSTATE_H
#define ENUMS_ANIMSTATE_H

/*
	Define our animation states.
*/
enum class animationState : int
{
	IS_IDLE, //Default state
	HAS_BEEN_REQUESTED, //State when called
	IS_PERFORMING, //State when performing
	HAS_FINISHED //State when completed
};

#endif