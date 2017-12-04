#include "main-is_paused.h"

/*
Handle user inputs
*/
void gamestateIsPaused::keyHandler(ASGE::SharedEventData data) {
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());
	
	//Close pause menu and return to game
	if (key->key == ASGE::KEYS::KEY_C && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Play SFX
		PlaySound(TEXT("Resources_Temp\\BEEP_011.wav"), NULL, SND_ASYNC);

		//Un-pause
		pongGamestate::current_gamestate = gamestate::IS_PLAYING;
		pongFX::has_finished_cycle = false;
		pongVariables::freeze_ball = false;
	}

	//Return to main menu
	if (key->key == ASGE::KEYS::KEY_M && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Play SFX
		PlaySound(TEXT("Resources_Temp\\BEEP_018.wav"), NULL, SND_ASYNC);

		//Reset game and return to menu TODO
		//resetGame();
	}
}