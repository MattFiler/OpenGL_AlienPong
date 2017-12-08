#include "main-is_in_loadscreen.h"

/*
Render everything for gamestate
*/
void gamestateIsInLoadscreen::renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer)
{
	//Render loading screen for first few seconds
	if (pong_variables.global_game_timer < 3.2f)
	{
		//Speed
		float stage_0 = 0.3f;
		float stage_1 = 0.7f;
		float stage_2 = 1.2f;
		float stage_3 = 1.6f;
		float stage_4 = 2.1f;
		float stage_5 = 2.5f;
		float stage_6 = 2.8f;

		//Play SFX
		if (!pong_variables.has_performed_startup_sound) {
			PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Startup_SHORTENED.wav"), NULL, SND_ASYNC);
			//PlaySound(TEXT("Resources_Temp\\../../Resources/Audio/Interactive_Terminal_BG_Loop.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
			pong_variables.has_performed_startup_sound = true;
			pong_animation.state = animationState::HAS_BEEN_REQUESTED;
		}

		//Animation
		if (pong_variables.global_game_timer < stage_0)
		{
			renderer->renderSprite(*menu_overlay_loading);
		}
		if (pong_variables.global_game_timer < stage_1 && pong_variables.global_game_timer >= stage_0)
		{
			renderer->renderSprite(*menu_overlay_loading_s0);
		}
		if (pong_variables.global_game_timer < stage_2 && pong_variables.global_game_timer >= stage_1)
		{
			renderer->renderSprite(*menu_overlay_loading_s1);
		}
		if (pong_variables.global_game_timer < stage_3 && pong_variables.global_game_timer >= stage_2)
		{
			renderer->renderSprite(*menu_overlay_loading_s2);
		}
		if (pong_variables.global_game_timer < stage_4 && pong_variables.global_game_timer >= stage_3)
		{
			renderer->renderSprite(*menu_overlay_loading_s3);
		}
		if (pong_variables.global_game_timer < stage_5 && pong_variables.global_game_timer >= stage_4)
		{
			renderer->renderSprite(*menu_overlay_loading_s4);
		}
		if ((pong_variables.global_game_timer < stage_6 && pong_variables.global_game_timer >= stage_5) || pong_variables.global_game_timer >= stage_6)
		{
			renderer->renderSprite(*menu_overlay_loading_s5);
		}
	}
	else
	{
		pong_gamestate.current_gamestate = gamestate::IS_IN_MENU; //Take us out of the animation
	}
}