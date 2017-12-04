#include "main-is_in_loadscreen.h"

/*
Remove non-managed memory
*/
gamestateIsInLoadscreen::~gamestateIsInLoadscreen()
{
	pong_sprite_static.~spritesStatic();
	pong_sprite_dynamic.~spritesDynamic();
}


/*
Render everything for gamestate
*/
void gamestateIsInLoadscreen::renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer)
{
	//Load sprites
	pong_sprite_static.loadSprites(renderer);
	pong_sprite_dynamic.loadSprites(renderer);

	//Debug text
	renderer->renderText(("INLOADSCREEN CLASS: " + std::to_string(pongVariables::global_game_timer)).c_str(), 55, 55, 1, ASGE::COLOURS::WHITE);

	//Render loading screen for first few seconds
	if (pongVariables::global_game_timer < 3.2f)
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
		if (!pongVariables::has_performed_startup_sound) {
			PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Startup_SHORTENED.wav"), NULL, SND_ASYNC);
			//PlaySound(TEXT("Resources_Temp\\../../Resources/Audio/Interactive_Terminal_BG_Loop.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
			pongVariables::has_performed_startup_sound = true;
		}

		//Animation
		if (pongVariables::global_game_timer < stage_0)
		{
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading);
			pong_fx.has_requested = true;
		}
		if (pongVariables::global_game_timer < stage_1 && pongVariables::global_game_timer >= stage_0)
		{
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading_s0);
		}
		if (pongVariables::global_game_timer < stage_2 && pongVariables::global_game_timer >= stage_1)
		{
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading_s1);
		}
		if (pongVariables::global_game_timer < stage_3 && pongVariables::global_game_timer >= stage_2)
		{
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading_s2);
		}
		if (pongVariables::global_game_timer < stage_4 && pongVariables::global_game_timer >= stage_3)
		{
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading_s3);
		}
		if (pongVariables::global_game_timer < stage_5 && pongVariables::global_game_timer >= stage_4)
		{
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading_s4);
		}
		if ((pongVariables::global_game_timer < stage_6 && pongVariables::global_game_timer >= stage_5) || pongVariables::global_game_timer >= stage_6)
		{
			renderer->renderSprite(*pong_sprite_static.menu_overlay_loading_s5);
			pong_fx.has_finished_cycle = false;
		}
	}
	else
	{
		pongGamestate::current_gamestate = gamestate::IS_IN_MENU; //Take us out of the animation
	}
}