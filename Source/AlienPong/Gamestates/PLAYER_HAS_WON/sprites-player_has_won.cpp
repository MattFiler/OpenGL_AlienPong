#include "main-player_has_won.h"


/*
Remove non-managed memory
*/
gamestatePlayerHasWon::~gamestatePlayerHasWon()
{
	//in-game SCORE screen - P1
	if (menu_overlay_score_p1)
	{
		delete menu_overlay_score_p1;
		menu_overlay_score_p1 = nullptr;
	}

	//in-game SCORE screen - P2
	if (menu_overlay_score_p2)
	{
		delete menu_overlay_score_p2;
		menu_overlay_score_p2 = nullptr;
	}

	//in-game SCORE screen - PLAYER
	if (menu_overlay_score_player)
	{
		delete menu_overlay_score_player;
		menu_overlay_score_player = nullptr;
	}

	//in-game SCORE screen - CPU
	if (menu_overlay_score_cpu)
	{
		delete menu_overlay_score_cpu;
		menu_overlay_score_cpu = nullptr;
	}
}


/*
Load sprites
*/
void gamestatePlayerHasWon::loadSprites(ASGE::Renderer* renderer)
{
	//overlay SCORE screen - P1
	menu_overlay_score_p1 = renderer->createRawSprite();
	menu_overlay_score_p1->loadTexture("Resources_Temp\\overlay_ingame_score_p1.png");
	menu_overlay_score_p1->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_score_p1->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//overlay SCORE screen - P2
	menu_overlay_score_p2 = renderer->createRawSprite();
	menu_overlay_score_p2->loadTexture("Resources_Temp\\overlay_ingame_score_p2.png");
	menu_overlay_score_p2->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_score_p2->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//overlay SCORE screen - PLAYER
	menu_overlay_score_player = renderer->createRawSprite();
	menu_overlay_score_player->loadTexture("Resources_Temp\\overlay_ingame_score_human.png");
	menu_overlay_score_player->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_score_player->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//overlay SCORE screen - CPU
	menu_overlay_score_cpu = renderer->createRawSprite();
	menu_overlay_score_cpu->loadTexture("Resources_Temp\\overlay_ingame_score_cpu.png");
	menu_overlay_score_cpu->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_score_cpu->height((int)settings::GAMEWINDOW_MAX_HEIGHT);
}