#include "main-is_playing.h"

/*
Update game
*/
void gamestateIsPlaying::updateState(const ASGE::GameTime & us) 
{
	/* RESETS */
	//Reset ball if requested
	if (pongVariables::reset_ball == true)
	{
		ball1->xPos(((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - ((int)settings::BALL_SIZE / 2));
		ball1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::BALL_SIZE / 2));
		pongVariables::reset_ball = false;
	}
	//Reset paddles if requested
	if (pongVariables::reset_paddles == true)
	{
		paddle1->xPos(100);
		paddle1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));
		paddle2->xPos((int)settings::GAMEWINDOW_MAX_WIDTH - 100);
		paddle2->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));
		pongVariables::reset_paddles = false;
	}

	//Get current ball position
	auto x_pos = ball1->xPos();
	auto y_pos = ball1->yPos();

	/* BALL COLLISION DETECTION */
	//See if we're touching the LEFT paddle
	if (pong_shared.isTouchingPaddle(paddle1, x_pos, y_pos, "LeftPaddle"))
	{
		pongDirections::ball_direction = direction::RIGHT;
		pongDirections::movement_angle = pong_shared.calculateReturnAngle(paddle1, true, ball1);
		pongDirections::movement_angle_raw = pong_shared.calculateReturnAngle(paddle1, false, ball1);
	}
	//See if we're touching the RIGHT paddle
	if (pong_shared.isTouchingPaddle(paddle2, x_pos, y_pos, "RightPaddle"))
	{
		pongDirections::ball_direction = direction::LEFT;
		pongDirections::movement_angle = pong_shared.calculateReturnAngle(paddle2, true, ball1);
		pongDirections::movement_angle_raw = pong_shared.calculateReturnAngle(paddle2, false, ball1);
	}
	//See if we're touching the TOP of the window
	if (pong_shared.hasHitEdge("Top", ball1) || pong_shared.hasHitEdge("Bottom", ball1))
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
	if (pong_shared.hasHitEdge("Left", ball1))
	{
		//Player 2 wins
		pongAnimationState::state = animationState::HAS_BEEN_REQUESTED;
		pong_shared.handleWin("p2");
	}
	//See if we're touching the RIGHT of the window
	if (pong_shared.hasHitEdge("Right", ball1))
	{
		//Player 1 wins
		pongAnimationState::state = animationState::HAS_BEEN_REQUESTED;
		pong_shared.handleWin("p1");
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