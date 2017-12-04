#include "main-is_in_menu.h"


/*
Remove non-managed memory
*/
gamestateIsInMenu::~gamestateIsInMenu()
{
	//Menu overlay 2 player
	if (menu_overlay_twoPlayer)
	{
		delete menu_overlay_twoPlayer;
		menu_overlay_twoPlayer = nullptr;
	}

	//Menu overlay 1 player
	if (menu_overlay_onePlayer)
	{
		delete menu_overlay_onePlayer;
		menu_overlay_onePlayer = nullptr;
	}

	//Menu overlay controls
	if (menu_overlay_controls)
	{
		delete menu_overlay_controls;
		menu_overlay_controls = nullptr;
	}

	//Menu overlay scores
	if (menu_overlay_scoreboard)
	{
		delete menu_overlay_scoreboard;
		menu_overlay_scoreboard = nullptr;
	}
}


/*
Load sprites
*/
void gamestateIsInMenu::loadSprites(ASGE::Renderer* renderer) 
{
	//Two Player overlay
	menu_overlay_twoPlayer = renderer->createRawSprite();
	menu_overlay_twoPlayer->loadTexture("Resources_Temp\\overlay_mode_oneplayer.png");
	menu_overlay_twoPlayer->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_twoPlayer->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//One Player overlay
	menu_overlay_onePlayer = renderer->createRawSprite();
	menu_overlay_onePlayer->loadTexture("Resources_Temp\\overlay_mode_twoplayer.png");
	menu_overlay_onePlayer->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_onePlayer->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Controls overlay
	menu_overlay_controls = renderer->createRawSprite();
	menu_overlay_controls->loadTexture("Resources_Temp\\overlay_mode_controls.png");
	menu_overlay_controls->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_controls->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Scoreboard overlay
	menu_overlay_scoreboard = renderer->createRawSprite();
	menu_overlay_scoreboard->loadTexture("Resources_Temp\\overlay_mode_scores.png");
	menu_overlay_scoreboard->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_scoreboard->height((int)settings::GAMEWINDOW_MAX_HEIGHT);
}