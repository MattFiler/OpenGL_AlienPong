#include "main-is_playing.h"

/*
Remove non-managed memory
*/
gamestateIsPlaying::~gamestateIsPlaying()
{
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
}


/*
Load sprites
*/
void gamestateIsPlaying::loadSprites(ASGE::Renderer* renderer)
{
	//Create paddle 1
	paddle1 = renderer->createRawSprite();
	paddle1->loadTexture("Resources_Temp\\whitepixel.jpg");
	paddle1->width((int)settings::PADDLE_WIDTH);
	paddle1->height((int)settings::PADDLE_HEIGHT);
	paddle1->xPos(100);
	paddle1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));

	//Create paddle 2
	paddle2 = renderer->createRawSprite();
	paddle2->loadTexture("Resources_Temp\\whitepixel.jpg");
	paddle2->width((int)settings::PADDLE_WIDTH);
	paddle2->height((int)settings::PADDLE_HEIGHT);
	paddle2->xPos((int)settings::GAMEWINDOW_MAX_WIDTH - 100);
	paddle2->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));

	//Create ball
	ball1 = renderer->createRawSprite();
	ball1->loadTexture("Resources_Temp\\whitepixel.jpg");
	ball1->width((int)settings::BALL_SIZE);
	ball1->height((int)settings::BALL_SIZE);
	ball1->xPos(((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - ((int)settings::BALL_SIZE / 2));
	ball1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::BALL_SIZE / 2));


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
}