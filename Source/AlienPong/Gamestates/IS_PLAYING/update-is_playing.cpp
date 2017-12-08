#include "main-is_playing.h"

/*
Update game
*/
void gamestateIsPlaying::updateState(const ASGE::GameTime & us) 
{
	/* RESETS */
	//Reset ball if requested
	if (pong_variables.reset_ball == true)
	{
		ball1->xPos(((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - ((int)settings::BALL_SIZE / 2));
		ball1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::BALL_SIZE / 2));
		pong_variables.reset_ball = false;
	}
	//Reset paddles if requested
	if (pong_variables.reset_paddles == true)
	{
		paddle1->xPos(100);
		paddle1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));
		paddle2->xPos((int)settings::GAMEWINDOW_MAX_WIDTH - 100);
		paddle2->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));
		pong_variables.reset_paddles = false;
	}

	//Get current ball position
	auto x_pos = ball1->xPos();
	auto y_pos = ball1->yPos();

	/* BALL COLLISION DETECTION */
	//See if we're touching the LEFT paddle
	if (pong_shared.isTouchingPaddle(paddle1, x_pos, y_pos, "LeftPaddle"))
	{
		pong_directions.ball_direction = direction::RIGHT;
		pong_directions.movement_angle = pong_shared.calculateReturnAngle(paddle1, true, ball1);
		pong_directions.movement_angle_raw = pong_shared.calculateReturnAngle(paddle1, false, ball1);
	}
	//See if we're touching the RIGHT paddle
	else if (pong_shared.isTouchingPaddle(paddle2, x_pos, y_pos, "RightPaddle"))
	{
		pong_directions.ball_direction = direction::LEFT;
		pong_directions.movement_angle = pong_shared.calculateReturnAngle(paddle2, true, ball1);
		pong_directions.movement_angle_raw = pong_shared.calculateReturnAngle(paddle2, false, ball1);
	}
	//See if we're touching the TOP of the window
	if (pong_shared.hasHitEdge("Top", ball1) || pong_shared.hasHitEdge("Bottom", ball1))
	{
		pong_directions.movement_angle *= -1; //Swap angle on touch of top or bottom
	}

	/* BALL MOVEMENT */
	//Movement direction
	float ball_x_modifier = ((int)settings::DEFAULT_SPEED - pong_directions.movement_angle_raw) * (us.delta_time.count() / 1000.f);
	if (pong_directions.ball_direction == direction::LEFT)
	{
		//Set X position
		x_pos -= ball_x_modifier; //speed - angle to account for vertical velocity
	}
	else
	{
		//Set X position
		x_pos += ball_x_modifier; //speed - angle to account for vertical velocity
	}
	//Apply movement angle
	y_pos += pong_directions.movement_angle * (us.delta_time.count() / 1000.f);
	if (!pong_variables.freeze_ball)
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
		pong_animation.state = animationState::HAS_BEEN_REQUESTED;
		pong_shared.handleWin("p2");
	}
	//See if we're touching the RIGHT of the window
	else if (pong_shared.hasHitEdge("Right", ball1))
	{
		//Player 1 wins
		pong_animation.state = animationState::HAS_BEEN_REQUESTED;
		pong_shared.handleWin("p1");
	}

	/* CPU PLAYER */
	if (pong_gamemode.is_against_cpu)
	{
		if (ball1->yPos() > (paddle2->yPos() + ((int)settings::BALL_SIZE * 3)) && ball1->yPos() < (paddle2->yPos() + (int)settings::PADDLE_HEIGHT - ((int)settings::BALL_SIZE * 3)))
		{
			pong_directions.right_paddle_moving = false;
		}
		else
		{
			//Ball is out of paddle range, move to it
			pong_directions.right_paddle_moving = true;
			if (ball1->yPos() > paddle2->yPos())
			{
				pong_directions.right_paddle_direction = direction::DOWN;
			}
			if (ball1->yPos() < (paddle2->yPos() + (int)settings::PADDLE_HEIGHT - ((int)settings::BALL_SIZE * 3)))
			{
				pong_directions.right_paddle_direction = direction::UP;
			}
		}
	}

	/* PADDLE MOVEMENT */
	//Left Paddle
	if (pong_directions.left_paddle_moving)
	{
		float leftpaddle_move_speed = ((int)settings::DEFAULT_SPEED / 2)  * (us.delta_time.count() / 1000.f);
		if (pong_directions.left_paddle_direction == direction::UP)
		{
			//Update Y position of paddle UP
			paddle1->yPos(paddle1->yPos() - leftpaddle_move_speed);
		}
		else
		{
			//Update Y position of paddle DOWN
			paddle1->yPos(paddle1->yPos() + leftpaddle_move_speed);
		}
	}
	//Right Paddle
	if (pong_directions.right_paddle_moving)
	{
		//Bespoke speed modifier for CPU movement (if human player, we default to 2)
		if (int(pong_variables.game_timer) % (int)settings::CPU_SLOW_SPEED_REFRESH == 0 && pong_gamemode.is_against_cpu)
		{
			if (pong_variables.cpu_speed_modifier_check != int(pong_variables.game_timer))
			{
				pong_variables.cpu_speed_modifier = (rand() % (int)settings::CPU_MODIFIER_EASY) + 2.5;
				pong_variables.cpu_speed_modifier_check = int(pong_variables.game_timer);
			}
		}
		float rightpaddle_move_speed = ((int)settings::DEFAULT_SPEED / pong_variables.cpu_speed_modifier)  * (us.delta_time.count() / 1000.f);
		if (pong_directions.right_paddle_direction == direction::UP)
		{
			//Update Y position of paddle UP
			paddle2->yPos(paddle2->yPos() - rightpaddle_move_speed);
		}
		else
		{
			//Update Y position of paddle DOWN
			paddle2->yPos(paddle2->yPos() + rightpaddle_move_speed);
		}
	}
}