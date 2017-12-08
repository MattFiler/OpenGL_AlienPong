#include "../structs.h"

#ifndef DEFINE_ALIENPONG_CORE
#define DEFINE_ALIENPONG_CORE

/*
	Set all pongVariables values
*/

//Default timers and runtime modifiers
bool pongVariables::freeze_ball = true;
bool pongVariables::reset_ball = true;
bool pongVariables::reset_paddles = true;
float pongVariables::game_timer = 0;
float pongVariables::global_game_timer = 0;
int pongVariables::cpu_speed_modifier_check = 0;
float pongVariables::cpu_speed_modifier = 2;

//Set audio checks
bool pongVariables::has_performed_startup_sound = false;

#endif