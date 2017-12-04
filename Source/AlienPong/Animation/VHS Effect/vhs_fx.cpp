#include "vhs_fx.h"

/*
	Define default values
*/
pongVHS::pongVHS()
{
	pongfx_state = animationState::IS_IDLE;
	time_started = 0;
	time_in_seconds = 0.07;
}


/*
Remove non-managed memory
*/
pongVHS::~pongVHS()
{
	//Menu background s00
	if (menu_background_s00)
	{
		delete menu_background_s00;
		menu_background_s00 = nullptr;
	}

	//Menu background s01
	if (menu_background_s01)
	{
		delete menu_background_s01;
		menu_background_s01 = nullptr;
	}

	//Menu background s02
	if (menu_background_s02)
	{
		delete menu_background_s02;
		menu_background_s02 = nullptr;
	}

	//Menu background s03
	if (menu_background_s03)
	{
		delete menu_background_s03;
		menu_background_s03 = nullptr;
	}

	//Menu background s04
	if (menu_background_s04)
	{
		delete menu_background_s04;
		menu_background_s04 = nullptr;
	}
}


/*
Load sprites
*/
void pongVHS::loadSprites(ASGE::Renderer* renderer)
{
	//Menu background state 00
	menu_background_s00 = renderer->createRawSprite();
	menu_background_s00->loadTexture("Resources_Temp\\background_static00.jpg");
	menu_background_s00->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_background_s00->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Menu background state 01
	menu_background_s01 = renderer->createRawSprite();
	menu_background_s01->loadTexture("Resources_Temp\\background_static01.jpg");
	menu_background_s01->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_background_s01->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Menu background state 02
	menu_background_s02 = renderer->createRawSprite();
	menu_background_s02->loadTexture("Resources_Temp\\background_static02.jpg");
	menu_background_s02->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_background_s02->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Menu background state 03
	menu_background_s03 = renderer->createRawSprite();
	menu_background_s03->loadTexture("Resources_Temp\\background_static03.jpg");
	menu_background_s03->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_background_s03->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Menu background state 04
	menu_background_s04 = renderer->createRawSprite();
	menu_background_s04->loadTexture("Resources_Temp\\background_static04.jpg");
	menu_background_s04->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_background_s04->height((int)settings::GAMEWINDOW_MAX_HEIGHT);
}


/*
	Render FX if requested (and not already performing)
*/
void pongVHS::renderFX(ASGE::Renderer* renderer) {
	if (pongfx_state == animationState::HAS_BEEN_REQUESTED || //Has requested effect?
		((time_started + time_in_seconds) < pongVariables::global_game_timer && pongfx_state == animationState::IS_PERFORMING) //Is in time range for performing effect?
		)
	{
		if (pongfx_state != animationState::HAS_FINISHED)
		{
			if (pongfx_state == animationState::HAS_BEEN_REQUESTED)
			{
				time_started = pongVariables::global_game_timer; //Log start time (if not already performing)
			}
			pongfx_state == animationState::IS_IDLE;

			//Run animation
			if (pongVariables::global_game_timer - time_started < 0.01)
			{
				renderer->renderSprite(*menu_background_s00);
				pongfx_state == animationState::IS_PERFORMING;
			}
			if (pongVariables::global_game_timer - time_started < 0.03 && pongVariables::global_game_timer - time_started >= 0.01)
			{
				renderer->renderSprite(*menu_background_s01);
				pongfx_state == animationState::IS_PERFORMING;
			}
			if (pongVariables::global_game_timer - time_started < 0.04 && pongVariables::global_game_timer - time_started >= 0.03)
			{
				renderer->renderSprite(*menu_background_s02);
				pongfx_state == animationState::IS_PERFORMING;
			}
			if (pongVariables::global_game_timer - time_started < 0.06 && pongVariables::global_game_timer - time_started >= 0.04)
			{
				renderer->renderSprite(*menu_background_s03);
				pongfx_state == animationState::IS_PERFORMING;
			}
			if (pongVariables::global_game_timer - time_started < 0.07 && pongVariables::global_game_timer - time_started >= 0.06)
			{
				renderer->renderSprite(*menu_background_s04);
				pongfx_state == animationState::HAS_FINISHED;
			}
		}
	}
}