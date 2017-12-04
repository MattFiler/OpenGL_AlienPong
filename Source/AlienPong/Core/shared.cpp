#include "shared.h"

/**
*   Perform a game reset
*/
void pongShared::reset()
{
	//Reset points
	pongScores::p1 = 0;
	pongScores::p2 = 0;

	//Open and reset menu
	pongGamestate::current_gamestate = gamestate::IS_IN_MENU;
	pongMenuState::menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
	pongMenuState::menu_page = menuState::MENU_PAGE_1;
	pongMenuState::menu_tab = menuState::MENU_TAB_1;

	//Reset gamestates, settings & vars
	pongGamemodes::current_gamemode = gamemode::NO_GAMEMODE;
	pongGamemodes::is_against_cpu = false;
	pongVariables::game_timer = 0;
	pongVariables::freeze_ball = true;
	pongVariables::reset_ball = true;
	pongVariables::reset_paddles = true;
	pongDirections::left_paddle_moving = false;
	pongDirections::right_paddle_moving = false;
	pongDirections::ball_direction = direction::RIGHT;
	pongVariables::cpu_speed_modifier = 2;
	pongDirections::movement_angle = 0;
	pongDirections::movement_angle_raw = 0;
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
	/*
	TODO: When using vectors, calculate path between the two vectors and see if it intersects the paddle.
	Should solve the lag issue when frames skip and the ball hit isn't registered.
	*/
	if (ball_x_pos > sprite->xPos() && ball_x_pos < (sprite->xPos() + (int)settings::PADDLE_WIDTH))
	{
		if (y >(sprite->yPos() - (int)settings::BALL_SIZE) && y < (sprite->yPos() + (int)settings::PADDLE_HEIGHT))
		{
			//Play SFX
			PlaySound(TEXT("Resources_Temp\\BEEP_021.wav"), NULL, SND_ASYNC | SND_NOSTOP);
			return true;
		}
		else
		{
			return false;
		}
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
	int paddle_middle_y = paddle_bottom_y + ((int)settings::PADDLE_HEIGHT / 2);
	int paddle_top_y = paddle_bottom_y + (int)settings::PADDLE_HEIGHT;
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
		pongScores::p1 += 1;
		if (pongGamemodes::is_against_cpu)
		{
			pongPlayers::winner = player::PLAYER_HUMAN; //PLAYER
			pongScores::scoreboard_player += 1;
		}
		else
		{
			pongPlayers::winner = player::PLAYER_P1; //P1
			pongScores::scoreboard_p1 += 1;
		}
	}
	else //Right side wins
	{
		//Update points 
		pongScores::p2 += 1;
		if (pongGamemodes::is_against_cpu)
		{
			pongPlayers::winner = player::PLAYER_CPU; //CPU
			pongScores::scoreboard_cpu += 1;
		}
		else
		{
			pongPlayers::winner = player::PLAYER_P2; //P2
			pongScores::scoreboard_p2 += 1;
		}
	}

	//Reset ball & paddle position
	pongVariables::reset_ball = true;
	pongVariables::reset_paddles = true;

	//Play SFX
	PlaySound(TEXT("Resources_Temp\\BEEP_009.wav"), NULL, SND_ASYNC);

	//Reset angle
	pongDirections::movement_angle = 0;
	pongDirections::movement_angle_raw = 0;

	//Try stop paddle moving ASAP!
	pongDirections::right_paddle_moving = false;
	pongDirections::left_paddle_moving = false;

	//Update gamestate
	pongGamestate::current_gamestate = gamestate::PLAYER_HAS_WON;
}