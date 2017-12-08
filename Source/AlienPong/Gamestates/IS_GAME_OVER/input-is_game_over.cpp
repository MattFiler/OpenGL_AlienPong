#include "main-is_game_over.h"

/*
Handle user inputs
*/
void gamestateIsGameOver::keyHandler(ASGE::SharedEventData data) 
{
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	//Disable other controls
	pong_directions.right_paddle_moving = false;
	pong_directions.left_paddle_moving = false;
	if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Play SFX
		PlaySound(TEXT("Resources_Temp\\BEEP_016.wav"), NULL, SND_ASYNC);

		//Update existing scoreboard file
		pong_filehandler.saveScoreboard();

		//Reset game and return to menu
		pong_shared.reset();
	}
}