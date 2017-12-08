#include "shared.h"

/**
*   Perform a game reset
*/
void pongShared::reset()
{
	//Reset points
	pong_scores.p1 = 0;
	pong_scores.p2 = 0;

	//Open and reset menu
	pong_gamestate.current_gamestate = gamestate::IS_IN_MENU;
	pong_menu_state.menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
	pong_menu_state.menu_page = menuState::MENU_PAGE_1;
	pong_menu_state.menu_tab = menuState::MENU_TAB_1;

	//Reset gamestates, settings & vars
	pong_gamemode.current_gamemode = gamemode::NO_GAMEMODE;
	pong_gamemode.is_against_cpu = false;
	pong_variables.game_timer = 0;
	pong_variables.freeze_ball = true;
	pong_variables.reset_ball = true;
	pong_variables.reset_paddles = true;
	pong_directions.left_paddle_moving = false;
	pong_directions.right_paddle_moving = false;
	pong_directions.ball_direction = direction::RIGHT;
	pong_variables.cpu_speed_modifier = 2;
	pong_directions.movement_angle = 0;
	pong_directions.movement_angle_raw = 0;

	//Reset Crazy gamemode
	pong_variables.paddle_height = (int)settings::PADDLE_HEIGHT;
}


/**
*   Checks to see if ball is touching paddle
*/
bool pongShared::isTouchingPaddle(const ASGE::Sprite* sprite, float x, float y, std::string spriteName) const
{
	//Auto-correct ball's X position for right paddle
	float ball_x_pos = x;
	if (spriteName == "RightPaddle")
	{
		ball_x_pos += (int)settings::BALL_SIZE;
	}

	//See if we hit any area on the paddle
	if ((ball_x_pos > sprite->xPos() && ball_x_pos < (sprite->xPos() + (int)settings::PADDLE_WIDTH)) &&
		(y >(sprite->yPos() - (int)settings::BALL_SIZE) && y < (sprite->yPos() + pong_variables.paddle_height)))
	{
		//Play SFX
		PlaySound(TEXT("Resources_Temp\\BEEP_021.wav"), NULL, SND_ASYNC | SND_NOSTOP);
		return true;
	}

	return false;
}


/**
*   Calculate the angle to return the ball at
*/
int pongShared::calculateReturnAngle(const ASGE::Sprite* paddle, bool include_reverses, const ASGE::Sprite* ball1) const
{
	//Save Y vals
	int paddle_bottom_y = paddle->yPos();
	int paddle_middle_y = paddle_bottom_y + (pong_variables.paddle_height / 2);
	int paddle_top_y = paddle_bottom_y + pong_variables.paddle_height;
	int ball_bottom_y = ball1->yPos();
	int ball_middle_y = ball_bottom_y + ((int)settings::BALL_SIZE / 2);
	int ball_top_y = ball_bottom_y + (int)settings::BALL_SIZE;

	//Values to set later
	int distance_to_middle_from_middle = 0;
	int return_angle = 0;

	//Check if we hit below (or on) the middle of the paddle
	bool hit_below_bottom = false;
	for (int i = 0; i < 11; i++)
	{
		if (ball_bottom_y + i <= paddle_middle_y)
		{
			hit_below_bottom = true;
		}
	}

	//Vary directions based on hit location
	if (hit_below_bottom == false)
	{
		distance_to_middle_from_middle = ball_middle_y - paddle_middle_y; //work out distance to middle of paddle from above
		return_angle = distance_to_middle_from_middle * (int)settings::DEFAULT_ANGLE_MULTIPLIER; //use angle multiplier for return angle
	}
	else
	{
		distance_to_middle_from_middle = paddle_middle_y - ball_middle_y; //work out distance to middle of paddle from below
		return_angle = distance_to_middle_from_middle * (int)settings::DEFAULT_ANGLE_MULTIPLIER; //use angle multiplier for return angle
		if (include_reverses)
		{
			return_angle *= -1; //reverse the direction up/down
		}
	}

	//Return the angle
	return return_angle;
}


/**
*   Checks to see if ball is touching the top or bottom of the screen
*/
bool pongShared::hasHitEdge(std::string edgeName, const ASGE::Sprite* ball1) const
{
	//Touching left?
	if (edgeName == "Left")
	{
		if (ball1->xPos() - (int)settings::BALL_SIZE <= 0)
		{
			return true; //Hit
		}
	}

	//Touching right?
	if (edgeName == "Right")
	{
		if (ball1->xPos() >= (int)settings::GAMEWINDOW_MAX_WIDTH)
		{
			return true; //Hit
		}
	}

	//Touching top?
	if (edgeName == "Top")
	{
		if (ball1->yPos() <= 0)
		{
			return true; //Hit
		}
	}

	//Touching bottom?
	if (edgeName == "Bottom")
	{
		if (ball1->yPos() + (int)settings::BALL_SIZE >= (int)settings::GAMEWINDOW_MAX_HEIGHT)
		{
			return true; //Hit
		}
	}

	return false;
}


/**
*   Scripts for win
*/
void pongShared::handleWin(std::string winner_name)
{
	if (winner_name == "p1") //Left side wins
	{
		//Update points 
		pong_scores.p1 += 1;
		if (pong_gamemode.is_against_cpu)
		{
			pong_players.winner = player::PLAYER_HUMAN; //PLAYER
			pong_scores.scoreboard_player += 1;
		}
		else
		{
			pong_players.winner = player::PLAYER_P1; //P1
			pong_scores.scoreboard_p1 += 1;
		}
	}
	else //Right side wins
	{
		//Update points 
		pong_scores.p2 += 1;
		if (pong_gamemode.is_against_cpu)
		{
			pong_players.winner = player::PLAYER_CPU; //CPU
			pong_scores.scoreboard_cpu += 1;
		}
		else
		{
			pong_players.winner = player::PLAYER_P2; //P2
			pong_scores.scoreboard_p2 += 1;
		}
	}

	//Reset ball & paddle position
	pong_variables.reset_ball = true;
	pong_variables.reset_paddles = true;

	//Play SFX
	PlaySound(TEXT("Resources_Temp\\BEEP_009.wav"), NULL, SND_ASYNC);

	//Reset Crazy gamemode
	pong_variables.paddle_height = (int)settings::PADDLE_HEIGHT;

	//Reset angle
	pong_directions.movement_angle = 0;
	pong_directions.movement_angle_raw = 0;

	//Try stop paddle moving ASAP!
	pong_directions.right_paddle_moving = false;
	pong_directions.left_paddle_moving = false;

	//Update gamestate
	pong_gamestate.current_gamestate = gamestate::PLAYER_HAS_WON;
}