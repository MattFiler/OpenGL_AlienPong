#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Engine/Platform.h>
#include "AlienPong/Pong.h"

#ifndef DEFINE_ALL_VALUES
#define DEFINE_ALL_VALUES

/*
Define default global values
*/


/* pongVariables */

//Default timers and runtime modifiers
bool pongVariables::freeze_ball = true;
bool pongVariables::reset_ball = true;
float pongVariables::game_timer = 0;
float pongVariables::global_game_timer = 0;
int pongVariables::cpu_speed_modifier_check = 0;
float pongVariables::cpu_speed_modifier = 2;

//Set audio checks
bool pongVariables::has_performed_startup_sound = false;


/* pongDirections */

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


/* pongGamemodes */

//Default gamemodes
gamemode pongGamemodes::current_gamemode = gamemode::NO_GAMEMODE;
bool pongGamemodes::is_against_cpu = false;


/* pongGamestate */

//Default gamestate
gamestate pongGamestate::current_gamestate = gamestate::IS_IN_LOADSCREEN;


/* pongPlayers */

//Default winner
player pongPlayers::winner = player::PLAYER_NULL;


/* pongScores */

//In-game Scores
int pongScores::p1 = 0;
int pongScores::p2 = 0;

//Scoreboard Scores
int pongScores::scoreboard_p1 = 0;
int pongScores::scoreboard_p2 = 0;
int pongScores::scoreboard_player = 0;
int pongScores::scoreboard_cpu = 0;


/* pongFX */

//Start/stop checkers
bool pongFX::is_performing = false;
bool pongFX::has_requested = false;
bool pongFX::has_finished_cycle = false;

//Timers
float pongFX::time_started = 0.0;
float pongFX::time_in_seconds = 0.07;


/* pongMenuState */

//Menu pages and tabs
menuState pongMenuState::menu_page = menuState::MENU_PAGE_1;
menuState pongMenuState::menu_tab = menuState::MENU_TAB_1;

//Menu selections
menuOption pongMenuState::menu_option = menuOption::MENU_OPTION_PVP_INFINITE;


/* pongBall */

//Main ball
float pongBall::x_position = 0;
float pongBall::y_position = 0;


/* pongPaddle */

//Paddle 1
float pongPaddle::paddle1_x_position = 0;
float pongPaddle::paddle1_y_position = 0;

//Paddle 2
float pongPaddle::paddle2_x_position = 0;
float pongPaddle::paddle2_y_position = 0;

#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	Pong game;
	if (game.init())
	{
		return game.run();
	}

	// game failed to initialise
	else
	{
		return -1;
	}
}