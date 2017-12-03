#include "main-is_in_loadscreen.h"

/*
Render everything for gamestate
*/
void gamestateIsInLoadscreen::renderState(ASGE::Renderer* renderer)
{
	//Render loading screen for first few seconds
	if (int(pong_vars.global_game_timer) < 3.2)
	{
		//Speed
		float stage_0 = 0.3;
		float stage_1 = 0.7;
		float stage_2 = 1.2;
		float stage_3 = 1.6;
		float stage_4 = 2.1;
		float stage_5 = 2.5;
		float stage_6 = 2.8;

		//Play SFX
		if (!pong_vars.has_performed_startup_sound) {
			PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Startup_SHORTENED.wav"), NULL, SND_ASYNC);
			//PlaySound(TEXT("Resources_Temp\\../../Resources/Audio/Interactive_Terminal_BG_Loop.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
			pong_vars.has_performed_startup_sound = true;
		}

		//Animation
		if (pong_vars.global_game_timer < stage_0)
		{
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading);
			pong_fx.has_requested = true;
		}
		if (pong_vars.global_game_timer < stage_1 && pong_vars.global_game_timer >= stage_0)
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading_s0);
		if (pong_vars.global_game_timer < stage_2 && pong_vars.global_game_timer >= stage_1)
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading_s1);
		if (pong_vars.global_game_timer < stage_3 && pong_vars.global_game_timer >= stage_2)
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading_s2);
		if (pong_vars.global_game_timer < stage_4 && pong_vars.global_game_timer >= stage_3)
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading_s3);
		if (pong_vars.global_game_timer < stage_5 && pong_vars.global_game_timer >= stage_4)
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading_s4);
		if ((pong_vars.global_game_timer < stage_6 && pong_vars.global_game_timer >= stage_5) || pong_vars.global_game_timer >= stage_6)
		{
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading_s5);
			pong_fx.has_finished_cycle = false;
		}
	}
	else
	{
		pong_gamestate.current_gamestate = gamestate::IS_IN_MENU; //Take us out of the animation
	}
}