#include "paddle.h"

/*
	Handle paddle movement
*/
pongPaddles::pongPaddles()
{
	//Get engine data
	ASGE::SharedEventData data;
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());
	
	if (key != nullptr) {
		/*
			LEFT PADDLE
		*/

		//Define values
		left_paddle_moving = false;
		left_paddle_direction = direction::NO_DIRECTION;

		//Move up
		if (key->key == ASGE::KEYS::KEY_W)
		{
			left_paddle_moving = true;
			left_paddle_direction = direction::UP;
		}

		//Move Down
		if (key->key == ASGE::KEYS::KEY_S)
		{
			left_paddle_moving = true;
			left_paddle_direction = direction::DOWN;
		}

		//Stop moving
		if (key->key == ASGE::KEYS::KEY_W && key->action == ASGE::KEYS::KEY_RELEASED ||
			key->key == ASGE::KEYS::KEY_S && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			left_paddle_moving = false;
		}


		/*
			RIGHT PADDLE
		*/

		//Define values
		right_paddle_moving = false;
		right_paddle_direction = direction::NO_DIRECTION;

		if (!gamemode.is_against_cpu)
		{
			//Move up
			if (key->key == ASGE::KEYS::KEY_UP)
			{
				right_paddle_moving = true;
				right_paddle_direction = direction::UP;
			}
			//Move Down
			if (key->key == ASGE::KEYS::KEY_DOWN)
			{
				right_paddle_moving = true;
				right_paddle_direction = direction::DOWN;
			}
			//Stop moving
			if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED ||
				key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				right_paddle_moving = false;
			}
		}
	}
}