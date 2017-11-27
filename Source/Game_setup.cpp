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
	game_width = GAMEWINDOW_MAX_WIDTH;
	game_height = GAMEWINDOW_MAX_HEIGHT;
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

	//Load all assets before we begin
	loadAssets();
	while(PongFileHandler.output_counter != 45) {
		//Wait to load in
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

	//Load Jixellation font to slot 0
	GameFont::fonts[0] = new GameFont(renderer->loadFont("Jixellation.ttf", 45), "default", 45);

	//Create paddle 1
	paddle1 = renderer->createRawSprite();
	paddle1->loadTexture("whitepixel.jpg");
	paddle1->width(PADDLE_WIDTH);
	paddle1->height(PADDLE_HEIGHT);
	paddle1->xPos(100);
	paddle1->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (PADDLE_HEIGHT / 2));

	//Create paddle 2
	paddle2 = renderer->createRawSprite();
	paddle2->loadTexture("whitepixel.jpg");
	paddle2->width(PADDLE_WIDTH);
	paddle2->height(PADDLE_HEIGHT);
	paddle2->xPos(GAMEWINDOW_MAX_WIDTH - 100);
	paddle2->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (PADDLE_HEIGHT / 2));

	//Create ball
	ball1 = renderer->createRawSprite();
	ball1->loadTexture("whitepixel.jpg");
	ball1->width(BALL_SIZE);
	ball1->height(BALL_SIZE);
	ball1->xPos((GAMEWINDOW_MAX_WIDTH / 2) - (BALL_SIZE / 2));
	ball1->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (BALL_SIZE / 2));


	//Monitor overlay
	monitor_overlay = renderer->createRawSprite();
	monitor_overlay->loadTexture("overlay_monitor_effect.png");
	monitor_overlay->width(GAMEWINDOW_MAX_WIDTH);
	monitor_overlay->height(GAMEWINDOW_MAX_HEIGHT);

	//Menu background
	menu_background = renderer->createRawSprite();
	menu_background->loadTexture("background.jpg");
	menu_background->width(GAMEWINDOW_MAX_WIDTH);
	menu_background->height(GAMEWINDOW_MAX_HEIGHT);

	//Menu background state 00
	menu_background_s00 = renderer->createRawSprite();
	menu_background_s00->loadTexture("background_static00.jpg");
	menu_background_s00->width(GAMEWINDOW_MAX_WIDTH);
	menu_background_s00->height(GAMEWINDOW_MAX_HEIGHT);

	//Menu background state 01
	menu_background_s01 = renderer->createRawSprite();
	menu_background_s01->loadTexture("background_static01.jpg");
	menu_background_s01->width(GAMEWINDOW_MAX_WIDTH);
	menu_background_s01->height(GAMEWINDOW_MAX_HEIGHT);

	//Menu background state 02
	menu_background_s02 = renderer->createRawSprite();
	menu_background_s02->loadTexture("background_static02.jpg");
	menu_background_s02->width(GAMEWINDOW_MAX_WIDTH);
	menu_background_s02->height(GAMEWINDOW_MAX_HEIGHT);

	//Menu background state 03
	menu_background_s03 = renderer->createRawSprite();
	menu_background_s03->loadTexture("background_static03.jpg");
	menu_background_s03->width(GAMEWINDOW_MAX_WIDTH);
	menu_background_s03->height(GAMEWINDOW_MAX_HEIGHT);

	//Menu background state 04
	menu_background_s04 = renderer->createRawSprite();
	menu_background_s04->loadTexture("background_static04.jpg");
	menu_background_s04->width(GAMEWINDOW_MAX_WIDTH);
	menu_background_s04->height(GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay
	menu_overlay_loading = renderer->createRawSprite();
	menu_overlay_loading->loadTexture("overlay_loading_s.png");
	menu_overlay_loading->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading->height(GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S0
	menu_overlay_loading_s0 = renderer->createRawSprite();
	menu_overlay_loading_s0->loadTexture("overlay_loading_s0.png");
	menu_overlay_loading_s0->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s0->height(GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S1
	menu_overlay_loading_s1 = renderer->createRawSprite();
	menu_overlay_loading_s1->loadTexture("overlay_loading_s1.png");
	menu_overlay_loading_s1->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s1->height(GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S2
	menu_overlay_loading_s2 = renderer->createRawSprite();
	menu_overlay_loading_s2->loadTexture("overlay_loading_s2.png");
	menu_overlay_loading_s2->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s2->height(GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S3
	menu_overlay_loading_s3 = renderer->createRawSprite();
	menu_overlay_loading_s3->loadTexture("overlay_loading_s3.png");
	menu_overlay_loading_s3->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s3->height(GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S4
	menu_overlay_loading_s4 = renderer->createRawSprite();
	menu_overlay_loading_s4->loadTexture("overlay_loading_s4.png");
	menu_overlay_loading_s4->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s4->height(GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S5
	menu_overlay_loading_s5 = renderer->createRawSprite();
	menu_overlay_loading_s5->loadTexture("overlay_loading_s5.png");
	menu_overlay_loading_s5->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s5->height(GAMEWINDOW_MAX_HEIGHT);

	//Two Player overlay
	menu_overlay_twoPlayer = renderer->createRawSprite();
	menu_overlay_twoPlayer->loadTexture("overlay_mode_oneplayer.png");
	menu_overlay_twoPlayer->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_twoPlayer->height(GAMEWINDOW_MAX_HEIGHT);

	//One Player overlay
	menu_overlay_onePlayer = renderer->createRawSprite();
	menu_overlay_onePlayer->loadTexture("overlay_mode_twoplayer.png");
	menu_overlay_onePlayer->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_onePlayer->height(GAMEWINDOW_MAX_HEIGHT);

	//Controls overlay
	menu_overlay_controls = renderer->createRawSprite();
	menu_overlay_controls->loadTexture("overlay_mode_controls.png");
	menu_overlay_controls->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_controls->height(GAMEWINDOW_MAX_HEIGHT);

	//Scoreboard overlay
	menu_overlay_scoreboard = renderer->createRawSprite();
	menu_overlay_scoreboard->loadTexture("overlay_mode_scores.png");
	menu_overlay_scoreboard->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_scoreboard->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay MODE: Regular
	menu_overlay_mode_regular = renderer->createRawSprite();
	menu_overlay_mode_regular->loadTexture("overlay_ingame_regular.png");
	menu_overlay_mode_regular->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_mode_regular->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay MODE: Timed
	menu_overlay_mode_timed = renderer->createRawSprite();
	menu_overlay_mode_timed->loadTexture("overlay_ingame_timed.png");
	menu_overlay_mode_timed->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_mode_timed->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay MODE: First to 5
	menu_overlay_mode_score = renderer->createRawSprite();
	menu_overlay_mode_score->loadTexture("overlay_ingame_points.png");
	menu_overlay_mode_score->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_mode_score->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay score box
	menu_overlay_score_box = renderer->createRawSprite();
	menu_overlay_score_box->loadTexture("overlay_ingame_scorebox.png");
	menu_overlay_score_box->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_score_box->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay PAUSE screen
	menu_overlay_paused = renderer->createRawSprite();
	menu_overlay_paused->loadTexture("overlay_ingame_paused.png");
	menu_overlay_paused->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_paused->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay WIN screen - P1
	menu_overlay_win_p1 = renderer->createRawSprite();
	menu_overlay_win_p1->loadTexture("overlay_ingame_win_p1.png");
	menu_overlay_win_p1->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_win_p1->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay WIN screen - P2
	menu_overlay_win_p2 = renderer->createRawSprite();
	menu_overlay_win_p2->loadTexture("overlay_ingame_win_p2.png");
	menu_overlay_win_p2->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_win_p2->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay WIN screen - PLAYER
	menu_overlay_win_player = renderer->createRawSprite();
	menu_overlay_win_player->loadTexture("overlay_ingame_win_human.png");
	menu_overlay_win_player->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_win_player->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay WIN screen - CPU
	menu_overlay_win_cpu = renderer->createRawSprite();
	menu_overlay_win_cpu->loadTexture("overlay_ingame_win_cpu.png");
	menu_overlay_win_cpu->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_win_cpu->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay WIN screen - DRAW
	menu_overlay_win_draw = renderer->createRawSprite();
	menu_overlay_win_draw->loadTexture("overlay_ingame_win_draw.png");
	menu_overlay_win_draw->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_win_draw->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay SCORE screen - P1
	menu_overlay_score_p1 = renderer->createRawSprite();
	menu_overlay_score_p1->loadTexture("overlay_ingame_score_p1.png");
	menu_overlay_score_p1->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_score_p1->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay SCORE screen - P2
	menu_overlay_score_p2 = renderer->createRawSprite();
	menu_overlay_score_p2->loadTexture("overlay_ingame_score_p2.png");
	menu_overlay_score_p2->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_score_p2->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay SCORE screen - PLAYER
	menu_overlay_score_player = renderer->createRawSprite();
	menu_overlay_score_player->loadTexture("overlay_ingame_score_human.png");
	menu_overlay_score_player->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_score_player->height(GAMEWINDOW_MAX_HEIGHT);

	//overlay SCORE screen - CPU
	menu_overlay_score_cpu = renderer->createRawSprite();
	menu_overlay_score_cpu->loadTexture("overlay_ingame_score_cpu.png");
	menu_overlay_score_cpu->width(GAMEWINDOW_MAX_WIDTH);
	menu_overlay_score_cpu->height(GAMEWINDOW_MAX_HEIGHT);


	//Handle inputs
	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &Pong::keyHandler, this);

	return true;
}