#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Constants.h"
#include "Game.h"
#include "GameFont.h"


//Paddle and ball sizes
int paddle_height = 150;
int paddle_width = 10;
int ball_size = 10;

//Movement direction: left = 0, right = 1.
int movement_direction = 0;


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
	renderer->setWindowTitle("Pong");

	//Change window background colour
	renderer->setClearColour(ASGE::COLOURS::BLACK);

	//Enable FPS count
	toggleFPS();

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

	//Handle inputs
	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &Pong::keyHandler, this);
	
	return true;
}


/**
*   @brief   Processes any key inputs
*   @details This function is added as a callback to handle the game's 
			 keyboard input. For this assignment, calls to this function 
			 are thread safe, so you may alter the game's state as you 
			 see fit. 
*   @param   data The event data relating to key input.
*   @see     KeyEvent
*   @return  void
*/
void Pong::keyHandler(ASGE::SharedEventData data)
{
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	//Quit game on press of ESC
	if (key->key == ASGE::KEYS::KEY_ESCAPE)
	{
		signalExit();
	}

	/* LEFT PADDLE */
	//Move up
	if (key->key == ASGE::KEYS::KEY_W)
	{
		//Update Y position of paddle
		paddle1->yPos(paddle1->yPos() - 10);
	}
	//Move Down
	if (key->key == ASGE::KEYS::KEY_S)
	{
		//Update Y position of paddle
		paddle1->yPos(paddle1->yPos() + 10);
	}

	/* RIGHT PADDLE */
	//Move up
	if (key->key == ASGE::KEYS::KEY_UP)
	{
		//Update Y position of paddle
		paddle2->yPos(paddle2->yPos() - 10);
	}
	//Move Down
	if (key->key == ASGE::KEYS::KEY_DOWN)
	{
		//Update Y position of paddle
		paddle2->yPos(paddle2->yPos() + 10);
	}
}


/**
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
			 current frame. Once the current frame is has finished
			 the buffers are swapped accordingly and the image shown.
*   @return  void
*/
void Pong::update(const ASGE::GameTime & us)
{
	//Ball move speed
	int movement_speed = 200;

	//Get current ball position
	auto x_pos = ball1->xPos();
	auto y_pos = ball1->yPos();

	//See if we're touching the LEFT paddle
	if (isTouchingPaddle(paddle1, x_pos, y_pos, "LeftPaddle"))
	{
		movement_direction = 1;
	}

	//See if we're touching the RIGHT paddle
	if (isTouchingPaddle(paddle2, x_pos, y_pos, "RightPaddle"))
	{
		movement_direction = 0;
	}

	if (movement_direction == 0) {
		//Set X position
		x_pos -= movement_speed * (us.delta_time.count() / 1000.f);
	}
	else
	{
		//Set X position
		x_pos += movement_speed * (us.delta_time.count() / 1000.f);
	}

	//Update X position of ball
	ball1->xPos(x_pos);
}


/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
			 Once the current frame is has finished the buffers are 
			 swapped accordingly and the image shown.
*   @return  void
*/
void Pong::render(const ASGE::GameTime &)
{
	//Set default font
	renderer->setFont(0);

	//Render paddle 1
	renderer->renderSprite(*paddle1);

	//Render paddle 2
	renderer->renderSprite(*paddle2);

	//Render ball 1
	renderer->renderSprite(*ball1);
}

/**
*   Checks to see if ball is touching paddle
*/
bool Pong::isTouchingPaddle(const ASGE::Sprite* sprite, float x, float y, std::string spriteName) const
{
	//Has hit?
	bool hitX = false;
	bool hitY = false;

	float targetX = sprite->xPos(); //Get the X value our ball needs to hit
	if (spriteName == "LeftPaddle") {
		targetX = sprite->xPos() + paddle_width; //Adjust X position for left paddle
	}
	if (spriteName == "RightPaddle") {
		targetX = sprite->xPos() - ball_size; //Adjust X position for right paddle
	}

	//See if we hit any X
	if (int(x) == int(targetX) - 1 ||
		int(x) == int(targetX) || 
		int(x) == int(targetX) + 1) {
		hitX = true; //Hit
	}
	
	float ballY = y; //Get the Y value of our ball

	//See if we hit any Y
	for (int i = 0; i < (paddle_height + 1); i++) {
		for (int b = 0; b < ball_size; b++) {
			if ((sprite->yPos() + i) == ballY) {
				hitY = true; //Hit
			}
		}
	}

	//Only return HIT if we matched X and Y
	if (hitX && hitY)
	{
		return true;
	}
	else
	{
		return false;
	}
}