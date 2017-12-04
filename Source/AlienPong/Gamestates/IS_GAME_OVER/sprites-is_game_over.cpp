#include "main-is_game_over.h"


/*
Remove non-managed memory
*/
gamestateIsGameOver::~gamestateIsGameOver()
{
	//overlay WIN menu - P1
	if (menu_overlay_win_p1)
	{
		delete menu_overlay_win_p1;
		menu_overlay_win_p1 = nullptr;
	}

	//overlay WIN menu - P2
	if (menu_overlay_win_p2)
	{
		delete menu_overlay_win_p2;
		menu_overlay_win_p2 = nullptr;
	}

	//overlay WIN menu - PLAYER
	if (menu_overlay_win_player)
	{
		delete menu_overlay_win_player;
		menu_overlay_win_player = nullptr;
	}

	//overlay WIN menu - CPU
	if (menu_overlay_win_cpu)
	{
		delete menu_overlay_win_cpu;
		menu_overlay_win_cpu = nullptr;
	}

	//overlay WIN menu - DRAW
	if (menu_overlay_win_draw)
	{
		delete menu_overlay_win_draw;
		menu_overlay_win_draw = nullptr;
	}
}


/*
Load sprites
*/
void gamestateIsGameOver::loadSprites(ASGE::Renderer* renderer)
{
	//overlay WIN screen - P1
	menu_overlay_win_p1 = renderer->createRawSprite();
	menu_overlay_win_p1->loadTexture("Resources_Temp\\overlay_ingame_win_p1.png");
	menu_overlay_win_p1->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_win_p1->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//overlay WIN screen - P2
	menu_overlay_win_p2 = renderer->createRawSprite();
	menu_overlay_win_p2->loadTexture("Resources_Temp\\overlay_ingame_win_p2.png");
	menu_overlay_win_p2->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_win_p2->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//overlay WIN screen - PLAYER
	menu_overlay_win_player = renderer->createRawSprite();
	menu_overlay_win_player->loadTexture("Resources_Temp\\overlay_ingame_win_human.png");
	menu_overlay_win_player->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_win_player->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//overlay WIN screen - CPU
	menu_overlay_win_cpu = renderer->createRawSprite();
	menu_overlay_win_cpu->loadTexture("Resources_Temp\\overlay_ingame_win_cpu.png");
	menu_overlay_win_cpu->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_win_cpu->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//overlay WIN screen - DRAW
	menu_overlay_win_draw = renderer->createRawSprite();
	menu_overlay_win_draw->loadTexture("Resources_Temp\\overlay_ingame_win_draw.png");
	menu_overlay_win_draw->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_win_draw->height((int)settings::GAMEWINDOW_MAX_HEIGHT);
}