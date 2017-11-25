#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Constants.h"
#include "Game.h"
#include "GameFont.h"


/*

//////// PONG - Created by Matt Filer /////////
///////////// GAME INITIALISATION /////////////

*/



/**
*   @brief   Default Constructor.
*/
Pong::Pong()
{
	//Change Resolution
	game_width = 1024;
	game_height = 768;
}


/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
Pong::~Pong()
{
	//Input callbacks
	this->inputs->unregisterCallback(key_callback_id);

	//Font reset
	for (auto& font : GameFont::fonts)
	{
		delete font;
		font = nullptr;
	}

	//Paddle 1 reset
	if (paddle1)
	{
		delete paddle1;
		paddle1 = nullptr;
	}

	//Paddle 2 reset
	if (paddle2)
	{
		delete paddle2;
		paddle2 = nullptr;
	}

	//Ball 1 reset
	if (ball1)
	{
		delete ball1;
		ball1 = nullptr;
	}

	//Monitor Overlay
	if (monitor_overlay)
	{
		delete monitor_overlay;
		monitor_overlay = nullptr;
	}

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


/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
run the game are loaded. The keyHandler callback should also
be set in the initialise function.
*   @return  True if the game initialised correctly.
*/
bool Pong::init()
{
	//Check graphics API has been initialised
	if (!initAPI())
	{
		return false;
	}

	//Disable sprite batching
	renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);

	//Change window title
	renderer->setWindowTitle("Pong Terminal");

	//Change window background colour
	renderer->setClearColour(ASGE::COLOURS::BLACK);

	//Enable FPS count
	//toggleFPS();

	//Disable threads
	inputs->use_threads = false;


	//Create paddle 1
	paddle1 = renderer->createRawSprite();
	paddle1->loadTexture(".\\Resources\\Textures\\whitepixel.jpg");
	paddle1->width(paddle_width);
	paddle1->height(paddle_height);
	paddle1->xPos(100);
	paddle1->yPos((game_height / 2) - (paddle_height / 2));

	//Create paddle 2
	paddle2 = renderer->createRawSprite();
	paddle2->loadTexture(".\\Resources\\Textures\\whitepixel.jpg");
	paddle2->width(paddle_width);
	paddle2->height(paddle_height);
	paddle2->xPos(game_width - 100);
	paddle2->yPos((game_height / 2) - (paddle_height / 2));

	//Create ball
	ball1 = renderer->createRawSprite();
	ball1->loadTexture(".\\Resources\\Textures\\whitepixel.jpg");
	ball1->width(ball_size);
	ball1->height(ball_size);
	ball1->xPos((game_width / 2) - (ball_size / 2));
	ball1->yPos((game_height / 2) - (ball_size / 2));


	//Monitor overlay
	monitor_overlay = renderer->createRawSprite();
	monitor_overlay->loadTexture(".\\Resources\\Textures\\MENU\\overlay_monitor_effect.png");
	monitor_overlay->width(game_width);
	monitor_overlay->height(game_height);

	//Menu background
	menu_background = renderer->createRawSprite();
	menu_background->loadTexture(".\\Resources\\Textures\\MENU\\background.jpg");
	menu_background->width(game_width);
	menu_background->height(game_height);

	//Menu background state 00
	menu_background_s00 = renderer->createRawSprite();
	menu_background_s00->loadTexture(".\\Resources\\Textures\\MENU\\background_static00.jpg");
	menu_background_s00->width(game_width);
	menu_background_s00->height(game_height);

	//Menu background state 01
	menu_background_s01 = renderer->createRawSprite();
	menu_background_s01->loadTexture(".\\Resources\\Textures\\MENU\\background_static01.jpg");
	menu_background_s01->width(game_width);
	menu_background_s01->height(game_height);

	//Menu background state 02
	menu_background_s02 = renderer->createRawSprite();
	menu_background_s02->loadTexture(".\\Resources\\Textures\\MENU\\background_static02.jpg");
	menu_background_s02->width(game_width);
	menu_background_s02->height(game_height);

	//Menu background state 03
	menu_background_s03 = renderer->createRawSprite();
	menu_background_s03->loadTexture(".\\Resources\\Textures\\MENU\\background_static03.jpg");
	menu_background_s03->width(game_width);
	menu_background_s03->height(game_height);

	//Menu background state 04
	menu_background_s04 = renderer->createRawSprite();
	menu_background_s04->loadTexture(".\\Resources\\Textures\\MENU\\background_static04.jpg");
	menu_background_s04->width(game_width);
	menu_background_s04->height(game_height);

	//Loading overlay
	menu_overlay_loading = renderer->createRawSprite();
	menu_overlay_loading->loadTexture(".\\Resources\\Textures\\MENU\\overlay_loading_s.png");
	menu_overlay_loading->width(game_width);
	menu_overlay_loading->height(game_height);

	//Loading overlay S0
	menu_overlay_loading_s0 = renderer->createRawSprite();
	menu_overlay_loading_s0->loadTexture(".\\Resources\\Textures\\MENU\\overlay_loading_s0.png");
	menu_overlay_loading_s0->width(game_width);
	menu_overlay_loading_s0->height(game_height);

	//Loading overlay S1
	menu_overlay_loading_s1 = renderer->createRawSprite();
	menu_overlay_loading_s1->loadTexture(".\\Resources\\Textures\\MENU\\overlay_loading_s1.png");
	menu_overlay_loading_s1->width(game_width);
	menu_overlay_loading_s1->height(game_height);

	//Loading overlay S2
	menu_overlay_loading_s2 = renderer->createRawSprite();
	menu_overlay_loading_s2->loadTexture(".\\Resources\\Textures\\MENU\\overlay_loading_s2.png");
	menu_overlay_loading_s2->width(game_width);
	menu_overlay_loading_s2->height(game_height);

	//Loading overlay S3
	menu_overlay_loading_s3 = renderer->createRawSprite();
	menu_overlay_loading_s3->loadTexture(".\\Resources\\Textures\\MENU\\overlay_loading_s3.png");
	menu_overlay_loading_s3->width(game_width);
	menu_overlay_loading_s3->height(game_height);

	//Loading overlay S4
	menu_overlay_loading_s4 = renderer->createRawSprite();
	menu_overlay_loading_s4->loadTexture(".\\Resources\\Textures\\MENU\\overlay_loading_s4.png");
	menu_overlay_loading_s4->width(game_width);
	menu_overlay_loading_s4->height(game_height);

	//Loading overlay S5
	menu_overlay_loading_s5 = renderer->createRawSprite();
	menu_overlay_loading_s5->loadTexture(".\\Resources\\Textures\\MENU\\overlay_loading_s5.png");
	menu_overlay_loading_s5->width(game_width);
	menu_overlay_loading_s5->height(game_height);

	//Two Player overlay
	menu_overlay_twoPlayer = renderer->createRawSprite();
	menu_overlay_twoPlayer->loadTexture(".\\Resources\\Textures\\MENU\\overlay_mode_oneplayer.png");
	menu_overlay_twoPlayer->width(game_width);
	menu_overlay_twoPlayer->height(game_height);

	//One Player overlay
	menu_overlay_onePlayer = renderer->createRawSprite();
	menu_overlay_onePlayer->loadTexture(".\\Resources\\Textures\\MENU\\overlay_mode_twoplayer.png");
	menu_overlay_onePlayer->width(game_width);
	menu_overlay_onePlayer->height(game_height);

	//overlay MODE: Regular
	menu_overlay_mode_regular = renderer->createRawSprite();
	menu_overlay_mode_regular->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_regular.png");
	menu_overlay_mode_regular->width(game_width);
	menu_overlay_mode_regular->height(game_height);

	//overlay MODE: Timed
	menu_overlay_mode_timed = renderer->createRawSprite();
	menu_overlay_mode_timed->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_timed.png");
	menu_overlay_mode_timed->width(game_width);
	menu_overlay_mode_timed->height(game_height);

	//overlay MODE: First to 5
	menu_overlay_mode_score = renderer->createRawSprite();
	menu_overlay_mode_score->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_points.png");
	menu_overlay_mode_score->width(game_width);
	menu_overlay_mode_score->height(game_height);

	//overlay PAUSE screen
	menu_overlay_paused = renderer->createRawSprite();
	menu_overlay_paused->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_paused.png");
	menu_overlay_paused->width(game_width);
	menu_overlay_paused->height(game_height);

	//overlay WIN screen - P1
	menu_overlay_win_p1 = renderer->createRawSprite();
	menu_overlay_win_p1->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_win_p1.png");
	menu_overlay_win_p1->width(game_width);
	menu_overlay_win_p1->height(game_height);

	//overlay WIN screen - P2
	menu_overlay_win_p2 = renderer->createRawSprite();
	menu_overlay_win_p2->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_win_p2.png");
	menu_overlay_win_p2->width(game_width);
	menu_overlay_win_p2->height(game_height);

	//overlay WIN screen - PLAYER
	menu_overlay_win_player = renderer->createRawSprite();
	menu_overlay_win_player->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_win_human.png");
	menu_overlay_win_player->width(game_width);
	menu_overlay_win_player->height(game_height);

	//overlay WIN screen - CPU
	menu_overlay_win_cpu = renderer->createRawSprite();
	menu_overlay_win_cpu->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_win_cpu.png");
	menu_overlay_win_cpu->width(game_width);
	menu_overlay_win_cpu->height(game_height);

	//overlay WIN screen - DRAW
	menu_overlay_win_draw = renderer->createRawSprite();
	menu_overlay_win_draw->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_win_draw.png");
	menu_overlay_win_draw->width(game_width);
	menu_overlay_win_draw->height(game_height);

	//overlay SCORE screen - P1
	menu_overlay_score_p1 = renderer->createRawSprite();
	menu_overlay_score_p1->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_score_p1.png");
	menu_overlay_score_p1->width(game_width);
	menu_overlay_score_p1->height(game_height);

	//overlay SCORE screen - P2
	menu_overlay_score_p2 = renderer->createRawSprite();
	menu_overlay_score_p2->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_score_p2.png");
	menu_overlay_score_p2->width(game_width);
	menu_overlay_score_p2->height(game_height);

	//overlay SCORE screen - PLAYER
	menu_overlay_score_player = renderer->createRawSprite();
	menu_overlay_score_player->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_score_human.png");
	menu_overlay_score_player->width(game_width);
	menu_overlay_score_player->height(game_height);

	//overlay SCORE screen - CPU
	menu_overlay_score_cpu = renderer->createRawSprite();
	menu_overlay_score_cpu->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_score_cpu.png");
	menu_overlay_score_cpu->width(game_width);
	menu_overlay_score_cpu->height(game_height);


	//Handle inputs
	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &Pong::keyHandler, this);

	return true;
}