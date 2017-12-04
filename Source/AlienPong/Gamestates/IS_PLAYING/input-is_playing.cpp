#include "main-is_playing.h"

/*
Handle user inputs
*/
void gamestateIsPlaying::keyHandler(ASGE::SharedEventData data)
{
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	/* LEFT PADDLE */
	//Move up
	if (key->key == ASGE::KEYS::KEY_W)
	{
		pongDirections::left_paddle_moving = true;
		pongDirections::left_paddle_direction = direction::UP;
	}
	//Move Down
	if (key->key == ASGE::KEYS::KEY_S)
	{
		pongDirections::left_paddle_moving = true;
		pongDirections::left_paddle_direction = direction::DOWN;
	}
	//Stop moving
	if (key->key == ASGE::KEYS::KEY_W && key->action == ASGE::KEYS::KEY_RELEASED ||
		key->key == ASGE::KEYS::KEY_S && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		pongDirections::left_paddle_moving = false;
	}

	/* RIGHT PADDLE */
	if (!pongGamemodes::is_against_cpu)
	{
		//Move up
		if (key->key == ASGE::KEYS::KEY_UP)
		{
			pongDirections::right_paddle_moving = true;
			pongDirections::right_paddle_direction = direction::UP;
		}
		//Move Down
		if (key->key == ASGE::KEYS::KEY_DOWN)
		{
			pongDirections::right_paddle_moving = true;
			pongDirections::right_paddle_direction = direction::DOWN;
		}
		//Stop moving
		if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED ||
			key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			pongDirections::right_paddle_moving = false;
		}
	}

	//Pause game on press of escape
	if (key->key == ASGE::KEYS::KEY_ESCAPE && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		pongGamestate::current_gamestate = gamestate::IS_PAUSED;
		pongAnimationState::state = animationState::HAS_BEEN_REQUESTED;

		//Play SFX
		PlaySound(TEXT("Resources_Temp\\BEEP_005.wav"), NULL, SND_ASYNC);
	}
}