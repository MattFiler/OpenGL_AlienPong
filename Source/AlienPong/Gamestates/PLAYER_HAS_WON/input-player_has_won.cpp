#include "main-player_has_won.h"

/*
Handle user inputs
*/
void gamestatePlayerHasWon::keyHandler(ASGE::SharedEventData data) {
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	//Disable all other controls
	pongDirections::right_paddle_moving = false;
	pongDirections::left_paddle_moving = false;
	if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Play SFX
		PlaySound(TEXT("Resources_Temp\\BEEP_011.wav"), NULL, SND_ASYNC);

		//Return to game
		pongGamestate::current_gamestate = gamestate::IS_PLAYING;
		pongFX::has_finished_cycle = false;
	}
}