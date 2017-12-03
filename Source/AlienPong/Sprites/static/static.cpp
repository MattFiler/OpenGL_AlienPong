#include "static.h"


/*
Default constructor
*/
spritesStatic::spritesStatic()
{

}


/*
Remove non-managed memory
*/
spritesStatic::~spritesStatic()
{
	//Menu background
	if (menu_background)
	{
		delete menu_background;
		menu_background = nullptr;
	}

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

	//Menu loading
	if (menu_overlay_loading)
	{
		delete menu_overlay_loading;
		menu_overlay_loading = nullptr;
	}

	//Menu loading 0
	if (menu_overlay_loading_s0)
	{
		delete menu_overlay_loading_s0;
		menu_overlay_loading_s0 = nullptr;
	}

	//Menu loading 1 
	if (menu_overlay_loading_s1)
	{
		delete menu_overlay_loading_s1;
		menu_overlay_loading_s1 = nullptr;
	}

	//Menu loading 2
	if (menu_overlay_loading_s2)
	{
		delete menu_overlay_loading_s2;
		menu_overlay_loading_s2 = nullptr;
	}

	//Menu loading 3
	if (menu_overlay_loading_s3)
	{
		delete menu_overlay_loading_s3;
		menu_overlay_loading_s3 = nullptr;
	}

	//Menu loading 4 
	if (menu_overlay_loading_s4)
	{
		delete menu_overlay_loading_s4;
		menu_overlay_loading_s4 = nullptr;
	}

	//Menu loading 5
	if (menu_overlay_loading_s5)
	{
		delete menu_overlay_loading_s5;
		menu_overlay_loading_s5 = nullptr;
	}

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

	//overlay MODE: Regular
	if (menu_overlay_mode_regular)
	{
		delete menu_overlay_mode_regular;
		menu_overlay_mode_regular = nullptr;
	}

	//overlay MODE: Timed
	if (menu_overlay_mode_timed)
	{
		delete menu_overlay_mode_timed;
		menu_overlay_mode_timed = nullptr;
	}

	//overlay MODE: Score
	if (menu_overlay_mode_score)
	{
		delete menu_overlay_mode_score;
		menu_overlay_mode_score = nullptr;
	}

	//overlay score counter
	if (menu_overlay_score_box)
	{
		delete menu_overlay_score_box;
		menu_overlay_score_box = nullptr;
	}

	//overlay PAUSE menu
	if (menu_overlay_paused)
	{
		delete menu_overlay_paused;
		menu_overlay_paused = nullptr;
	}

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

	//Monitor Overlay
	if (monitor_overlay)
	{
		delete monitor_overlay;
		monitor_overlay = nullptr;
	}
}


/*
Define sprites
*/
void spritesStatic::loadSprites(ASGE::Renderer* renderer)
{
	//Menu background
	menu_background = renderer->createRawSprite();
	menu_background->loadTexture("Resources_Temp\\background.jpg");
	menu_background->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_background->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

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

	//Monitor overlay
	monitor_overlay = renderer->createRawSprite();
	monitor_overlay->loadTexture("Resources_Temp\\overlay_monitor_effect.png");
	monitor_overlay->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	monitor_overlay->height((int)settings::GAMEWINDOW_MAX_HEIGHT);
}