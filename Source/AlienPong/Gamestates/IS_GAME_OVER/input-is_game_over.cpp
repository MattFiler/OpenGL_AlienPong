#include "main-is_game_over.h"

/*
Handle user inputs
*/
void gamestateIsGameOver::keyHandler(ASGE::SharedEventData data) 
{
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	//Disable other controls
	pongDirections::right_paddle_moving = false;
	pongDirections::left_paddle_moving = false;
	if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Play SFX
		PlaySound(TEXT("Resources_Temp\\BEEP_016.wav"), NULL, SND_ASYNC);

		//Reset game and return to menu
		pong_shared.reset();
	}
}