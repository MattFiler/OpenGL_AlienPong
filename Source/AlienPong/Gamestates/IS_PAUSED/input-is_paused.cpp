#include "main-is_paused.h"

/*
Handle user inputs
*/
void gamestateIsPaused::keyHandler(ASGE::SharedEventData data)
{
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());
	
	//Close pause menu and return to game
	if (key->key == ASGE::KEYS::KEY_C && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Play SFX
		PlaySound(TEXT("Resources_Temp\\BEEP_011.wav"), NULL, SND_ASYNC);

		//Un-pause
		pong_gamestate.current_gamestate = gamestate::IS_PLAYING;
		pong_variables.freeze_ball = false;
	}

	//Return to main menu
	else if (key->key == ASGE::KEYS::KEY_M && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Play SFX
		PlaySound(TEXT("Resources_Temp\\BEEP_018.wav"), NULL, SND_ASYNC);

		//Update existing scoreboard file
		pong_filehandler.saveScoreboard();

		//Reset game and return to menu
		pong_shared.reset();
	}
}