#include "dynamic.h"


/*
Default constructor
*/
spritesDynamic::spritesDynamic() 
{

}


/*
Remove non-managed memory
*/
spritesDynamic::~spritesDynamic() 
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
}


/*
Define sprites
*/
void spritesDynamic::loadSprites(ASGE::Renderer* renderer)
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
}