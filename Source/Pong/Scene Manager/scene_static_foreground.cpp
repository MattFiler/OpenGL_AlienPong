#include "scene_static_foreground.h"

/*
	Define default values
*/
sceneStaticForeground::sceneStaticForeground()
{

}


/*
	Destruct sprites
*/
sceneStaticForeground::~sceneStaticForeground()
{
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
}


/*
	Load sprites
*/
void sceneStaticForeground::loadSprites(std::shared_ptr<ASGE::Renderer> renderer)
{
	//Loading overlay
	menu_overlay_loading = renderer->createRawSprite();
	menu_overlay_loading->loadTexture("Resources_Temp\\overlay_loading_s.png");
	menu_overlay_loading->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S0
	menu_overlay_loading_s0 = renderer->createRawSprite();
	menu_overlay_loading_s0->loadTexture("Resources_Temp\\overlay_loading_s0.png");
	menu_overlay_loading_s0->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s0->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S1
	menu_overlay_loading_s1 = renderer->createRawSprite();
	menu_overlay_loading_s1->loadTexture("Resources_Temp\\overlay_loading_s1.png");
	menu_overlay_loading_s1->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s1->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S2
	menu_overlay_loading_s2 = renderer->createRawSprite();
	menu_overlay_loading_s2->loadTexture("Resources_Temp\\overlay_loading_s2.png");
	menu_overlay_loading_s2->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s2->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S3
	menu_overlay_loading_s3 = renderer->createRawSprite();
	menu_overlay_loading_s3->loadTexture("Resources_Temp\\overlay_loading_s3.png");
	menu_overlay_loading_s3->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s3->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S4
	menu_overlay_loading_s4 = renderer->createRawSprite();
	menu_overlay_loading_s4->loadTexture("Resources_Temp\\overlay_loading_s4.png");
	menu_overlay_loading_s4->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s4->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S5
	menu_overlay_loading_s5 = renderer->createRawSprite();
	menu_overlay_loading_s5->loadTexture("Resources_Temp\\overlay_loading_s5.png");
	menu_overlay_loading_s5->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s5->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

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

	//overlay MODE: Regular
	menu_overlay_mode_regular = renderer->createRawSprite();
	menu_overlay_mode_regular->loadTexture("Resources_Temp\\overlay_ingame_regular.png");
	menu_overlay_mode_regular->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_mode_regular->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//overlay MODE: Timed
	menu_overlay_mode_timed = renderer->createRawSprite();
	menu_overlay_mode_timed->loadTexture("Resources_Temp\\overlay_ingame_timed.png");
	menu_overlay_mode_timed->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_mode_timed->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//overlay MODE: First to 5
	menu_overlay_mode_score = renderer->createRawSprite();
	menu_overlay_mode_score->loadTexture("Resources_Temp\\overlay_ingame_points.png");
	menu_overlay_mode_score->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_mode_score->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//overlay score box
	menu_overlay_score_box = renderer->createRawSprite();
	menu_overlay_score_box->loadTexture("Resources_Temp\\overlay_ingame_scorebox.png");
	menu_overlay_score_box->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_score_box->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//overlay PAUSE screen
	menu_overlay_paused = renderer->createRawSprite();
	menu_overlay_paused->loadTexture("Resources_Temp\\overlay_ingame_paused.png");
	menu_overlay_paused->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_paused->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

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