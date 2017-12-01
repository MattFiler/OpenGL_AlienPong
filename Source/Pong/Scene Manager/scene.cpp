#include "scene.h"

sceneManager::sceneManager()
{

}

sceneManager::~sceneManager()
{
	background.~sceneBackground();
	static_foreground.~sceneStaticForeground();
	dynamic_foreground.~sceneDynamicForeground();
	foreground.~sceneForeground();
}

void sceneManager::loadAllSprites()
{
	std::shared_ptr<ASGE::Renderer> renderer;

	background.loadSprites(renderer);
	static_foreground.loadSprites(renderer);
	dynamic_foreground.loadSprites(renderer);
	foreground.loadSprites(renderer);
}

void sceneManager::renderBackground()
{
	//std::shared_ptr<ASGE::Renderer> renderer;
	//background.loadSprites();
	//renderer->renderSprite(*background.menu_background);
}

void sceneManager::renderLoadscreen()
{
	/*
	std::shared_ptr<ASGE::Renderer> renderer;

	//Render loading screen for first few seconds
	if (int(pong_core.global_game_timer) < 3.2)
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
		if (!pong_core.has_performed_startup_sound) {
			PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Startup_SHORTENED.wav"), NULL, SND_ASYNC);
			//PlaySound(TEXT("Resources_Temp\\../../Resources/Audio/Interactive_Terminal_BG_Loop.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
			pong_core.has_performed_startup_sound = true;
		}

		//Animation
		if (pong_core.global_game_timer < stage_0)
		{
			renderer->renderSprite(*static_foreground.menu_overlay_loading);
			vhs_fx.pongfx_state = animationState::HAS_BEEN_REQUESTED;
			pong_core.vhs_fx.renderFX();
		}
		if (pong_core.global_game_timer < stage_1 && pong_core.global_game_timer >= stage_0)
		{
			renderer->renderSprite(*static_foreground.menu_overlay_loading_s0);
		}
		if (pong_core.global_game_timer < stage_2 && pong_core.global_game_timer >= stage_1)
		{
			renderer->renderSprite(*static_foreground.menu_overlay_loading_s1);
		}
		if (pong_core.global_game_timer < stage_3 && pong_core.global_game_timer >= stage_2)
		{
			renderer->renderSprite(*static_foreground.menu_overlay_loading_s2);
		}
		if (pong_core.global_game_timer < stage_4 && pong_core.global_game_timer >= stage_3)
		{
			renderer->renderSprite(*static_foreground.menu_overlay_loading_s3);
		}
		if (pong_core.global_game_timer < stage_5 && pong_core.global_game_timer >= stage_4)
		{
			renderer->renderSprite(*static_foreground.menu_overlay_loading_s4);
		}
		if ((pong_core.global_game_timer < stage_6 && pong_core.global_game_timer >= stage_5) || pong_core.global_game_timer >= stage_6)
		{
			renderer->renderSprite(*static_foreground.menu_overlay_loading_s5);
		}
	}
	else
	{
		pong_core.current_gamestate = gamestate::IS_IN_MENU; //Take us out of the animation
	}
	*/
}

void sceneManager::renderMenuPage1()
{
	//std::shared_ptr<ASGE::Renderer> renderer;
}

void sceneManager::renderMenuPage2()
{
	//std::shared_ptr<ASGE::Renderer> renderer;
}

void sceneManager::renderInGame()
{
	/*
	std::shared_ptr<ASGE::Renderer> renderer;

	//Render score box
	renderer->renderSprite(*static_foreground.menu_overlay_score_box);
	
	//Render mode-specific overlays
	switch (pong_core.current_gamemode)
	{
		case gamemode::GAMEMODE_INFINITE:
		{
			renderer->renderSprite(*static_foreground.menu_overlay_mode_regular); //MODE OVERLAY: regular
			break;
		}
		case gamemode::GAMEMODE_SCORE:
		{
			renderer->renderSprite(*static_foreground.menu_overlay_mode_score); //MODE OVERLAY: score
			break;
		}
		case gamemode::GAMEMODE_TIMED:
		{
			renderer->setFont(GameFont::fonts[0]->id);
			renderer->renderSprite(*static_foreground.menu_overlay_mode_timed); //MODE OVERLAY: timed
			renderer->renderText((std::to_string(int((60 - pong_core.game_timer) + 0.5)) + " Seconds Remaining").c_str(), 50, (int)settings::GAMEWINDOW_MAX_HEIGHT - 50, 0.4, ASGE::COLOURS::WHITE);
			break;
		}
	}

	//Render Points
	if (pong_core.is_against_cpu)
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText("Player", (int)settings::GAMEWINDOW_MAX_WIDTH - 50 - 175, (int)settings::GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText((std::to_string(pong_core.pong_points.p1)).c_str(), (int)settings::GAMEWINDOW_MAX_WIDTH - 80, (int)settings::GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText("CPU", (int)settings::GAMEWINDOW_MAX_WIDTH - 50 - 175, (int)settings::GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText((std::to_string(pong_core.pong_points.p2)).c_str(), (int)settings::GAMEWINDOW_MAX_WIDTH - 80, (int)settings::GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
	}
	else
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText("Player 1", (int)settings::GAMEWINDOW_MAX_WIDTH - 50 - 175, (int)settings::GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText((std::to_string(pong_core.pong_points.p1)).c_str(), (int)settings::GAMEWINDOW_MAX_WIDTH - 80, (int)settings::GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText("Player 2", (int)settings::GAMEWINDOW_MAX_WIDTH - 50 - 175, (int)settings::GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText((std::to_string(pong_core.pong_points.p2)).c_str(), (int)settings::GAMEWINDOW_MAX_WIDTH - 80, (int)settings::GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
	}

	//Render paddle 1
	renderer->renderSprite(*dynamic_foreground.paddle1);

	//Render paddle 2
	renderer->renderSprite(*dynamic_foreground.paddle2);

	//Render ball 1
	renderer->renderSprite(*dynamic_foreground.ball1);
	*/
}

void sceneManager::renderPauseMenu()
{
	//std::shared_ptr<ASGE::Renderer> renderer;
}

void sceneManager::renderScoreScreen()
{
	//std::shared_ptr<ASGE::Renderer> renderer;
}