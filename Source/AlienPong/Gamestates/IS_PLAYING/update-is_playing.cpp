#include "main-is_playing.h"

//TODO, convert all ->xPos() and ->yPos() to ball->xPos() and pongBall::y_position


/*
Update game
*/
void gamestateIsPlaying::updateState(const ASGE::GameTime & us) {
	//Get current ball position
	auto x_pos = ball1->xPos();
	auto y_pos = ball1->yPos();

	//Reset ball if requested
	if (pongVariables::reset_ball == true)
	{
		ball1->xPos(((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - ((int)settings::BALL_SIZE / 2));
		ball1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::BALL_SIZE / 2));
	}

	/* BALL COLLISION DETECTION */
	//See if we're touching the LEFT paddle
	if (isTouchingPaddle(paddle1, x_pos, y_pos, "LeftPaddle"))
	{
		pongDirections::ball_direction = direction::RIGHT;
		pongDirections::movement_angle = calculateReturnAngle(paddle1, true);
		pongDirections::movement_angle_raw = calculateReturnAngle(paddle1, false);
	}
	//See if we're touching the RIGHT paddle
	if (isTouchingPaddle(paddle2, x_pos, y_pos, "RightPaddle"))
	{
		pongDirections::ball_direction = direction::LEFT;
		pongDirections::movement_angle = calculateReturnAngle(paddle2, true);
		pongDirections::movement_angle_raw = calculateReturnAngle(paddle2, false);
	}
	//See if we're touching the TOP of the window
	if (hasHitEdge("Top") || hasHitEdge("Bottom"))
	{
		pongDirections::movement_angle *= -1; //Swap angle on touch of top or bottom
	}

	/* BALL MOVEMENT */
	//Movement direction
	if (pongDirections::ball_direction == direction::LEFT)
	{
		//Set X position
		x_pos -= ((int)settings::DEFAULT_SPEED - pongDirections::movement_angle_raw) * (us.delta_time.count() / 1000.f); //speed - angle to account for vertical velocity
	}
	else
	{
		//Set X position
		x_pos += ((int)settings::DEFAULT_SPEED - pongDirections::movement_angle_raw) * (us.delta_time.count() / 1000.f); //speed - angle to account for vertical velocity
	}
	//Apply movement angle
	y_pos += pongDirections::movement_angle * (us.delta_time.count() / 1000.f);
	if (!pongVariables::freeze_ball)
	{
		//Update X position of ball
		ball1->xPos(x_pos);

		//Update Y position of ball
		ball1->yPos(y_pos);
	}
	else
	{
		//Freeze ball if requested
		ball1->xPos(ball1->xPos());
		ball1->yPos(ball1->yPos());
	}

	/* HANDLE WINS */
	//See if we're touching the LEFT of the window
	if (hasHitEdge("Left"))
	{
		//Player 2 wins
		handleWin("p2");
	}
	//See if we're touching the RIGHT of the window
	if (hasHitEdge("Right"))
	{
		//Player 1 wins
		handleWin("p1");
	}

	/* CPU PLAYER */
	if (pongGamemodes::is_against_cpu)
	{
		if (ball1->yPos() > (paddle2->yPos() + ((int)settings::BALL_SIZE * 3)) && ball1->yPos() < (paddle2->yPos() + (int)settings::PADDLE_HEIGHT - ((int)settings::BALL_SIZE * 3)))
		{
			pongDirections::right_paddle_moving = false;
		}
		else
		{
			//Ball is out of paddle range, move to it
			pongDirections::right_paddle_moving = true;
			if (ball1->yPos() > paddle2->yPos())
			{
				pongDirections::right_paddle_direction = direction::DOWN;
			}
			if (ball1->yPos() < (paddle2->yPos() + (int)settings::PADDLE_HEIGHT - ((int)settings::BALL_SIZE * 3)))
			{
				pongDirections::right_paddle_direction = direction::UP;
			}
		}
	}

	/* PADDLE MOVEMENT */
	//Left Paddle
	if (pongDirections::left_paddle_moving)
	{
		if (pongDirections::left_paddle_direction == direction::UP)
		{
			//Update Y position of paddle UP
			paddle1->yPos(paddle1->yPos() - ((int)settings::DEFAULT_SPEED / 2)  * (us.delta_time.count() / 1000.f));
		}
		else
		{
			//Update Y position of paddle DOWN
			paddle1->yPos(paddle1->yPos() + ((int)settings::DEFAULT_SPEED / 2)  * (us.delta_time.count() / 1000.f));
		}
	}
	//Right Paddle
	if (pongDirections::right_paddle_moving)
	{
		//Bespoke speed modifier for CPU movement (if human player, we default to 2)
		if (int(pongVariables::game_timer) % (int)settings::CPU_SLOW_SPEED_REFRESH == 0 && pongGamemodes::is_against_cpu)
		{
			if (pongVariables::cpu_speed_modifier_check != int(pongVariables::game_timer))
			{
				pongVariables::cpu_speed_modifier = (rand() % (int)settings::CPU_MODIFIER_EASY) + 2.5;
				pongVariables::cpu_speed_modifier_check = int(pongVariables::game_timer);
			}
		}
		if (pongDirections::right_paddle_direction == direction::UP)
		{
			//Update Y position of paddle UP
			paddle2->yPos(paddle2->yPos() - ((int)settings::DEFAULT_SPEED / pongVariables::cpu_speed_modifier)  * (us.delta_time.count() / 1000.f));
		}
		else
		{
			//Update Y position of paddle DOWN
			paddle2->yPos(paddle2->yPos() + ((int)settings::DEFAULT_SPEED / pongVariables::cpu_speed_modifier)  * (us.delta_time.count() / 1000.f));
		}
	}
}


/**
*   Checks to see if ball is touching paddle
*/
bool gamestateIsPlaying::isTouchingPaddle(const ASGE::Sprite* sprite, float x, float y, std::string spriteName) const
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
int gamestateIsPlaying::calculateReturnAngle(const ASGE::Sprite* paddle, bool include_reverses) const
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
bool gamestateIsPlaying::hasHitEdge(std::string edgeName) const
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
void gamestateIsPlaying::handleWin(std::string winner_name)
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

	//Reset ball position
	ball1->xPos(((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - ((int)settings::BALL_SIZE / 2));
	ball1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::BALL_SIZE / 2));

	//Reset paddle positions
	paddle1->xPos(100);
	paddle1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));
	paddle2->xPos((int)settings::GAMEWINDOW_MAX_WIDTH - 100);
	paddle2->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));

	//Play SFX
	PlaySound(TEXT("Resources_Temp\\BEEP_009.wav"), NULL, SND_ASYNC);

	//Reset angle
	pongDirections::movement_angle = 0;

	//Try stop paddle moving ASAP!
	pongDirections::right_paddle_moving = false;
	pongDirections::left_paddle_moving = false;

	//Update gamestate
	pongGamestate::current_gamestate = gamestate::PLAYER_HAS_WON;
}