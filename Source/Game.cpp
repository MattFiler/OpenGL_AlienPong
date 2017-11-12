#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Constants.h"
#include "Game.h"
#include "GameFont.h"


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

	//Menu text
	if (menuTitle)
	{
		delete menuTitle;
		menuTitle = nullptr;
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

	//Create Title
	menuTitle = renderer->createRawSprite();
	menuTitle->loadTexture(".\\Resources\\Textures\\main_logo.png");
	menuTitle->width(300);
	menuTitle->height(149);
	menuTitle->xPos((game_width / 2) - (300 / 2));
	menuTitle->yPos(((game_height / 2)/2) - (149 / 2));

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

	//Change menu controls
	if (is_in_menu) {
		/* MENU */
		//Go down on press of down
		if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if (menu_option == 0) {
				menu_option = 1;
			}
			if (menu_option == 1) {
				menu_option = 2;
			}
		}
		//Go up on press of up
		if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if (menu_option == 2) {
				menu_option = 1;
			}
			if (menu_option == 1) {
				menu_option = 0;
			}
		}
		//Handle menu selections
		if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			//Free play
			if (menu_option == 0)
			{
				is_in_menu = false;
				bool gamestate_freeplay = true;
				bool gamestate_timedgameplay = false;
				bool gamestate_firsttofive = false;
			}
			//Timed gameplay
			if (menu_option == 1)
			{
				is_in_menu = false;
				bool gamestate_freeplay = false;
				bool gamestate_timedgameplay = true;
				bool gamestate_firsttofive = false;
			}
			//First to 5
			if (menu_option == 2)
			{
				is_in_menu = false;
				bool gamestate_freeplay = false;
				bool gamestate_timedgameplay = false;
				bool gamestate_firsttofive = true;
			}
		}
	}
	else 
	{
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
	int movement_speed = speed_base;

	//Get current ball position
	auto x_pos = ball1->xPos();
	auto y_pos = ball1->yPos();

	//Only run game scripts if out of menu
	if (is_in_menu == false) {
		//See if we're touching the LEFT paddle
		if (isTouchingPaddle(paddle1, x_pos, y_pos, "LeftPaddle"))
		{
			movement_direction = 1;
			movement_angle = rand() % angle_variant + angle_base;

			if (rand() % 2 == 1) {
				movement_angle *= -1; //50% of the time we will reverse the angle to up/down
			}
		}

		//See if we're touching the RIGHT paddle
		if (isTouchingPaddle(paddle2, x_pos, y_pos, "RightPaddle"))
		{
			movement_direction = 0;
			movement_angle = rand() % angle_variant + angle_variant;

			if (rand() % 2 == 1) {
				movement_angle *= -1; //50% of the time we will reverse the angle to up/down
			}
		}

		//See if we're touching the TOP of the window
		if (hasHitEdge("Top") || hasHitEdge("Bottom"))
		{
			movement_angle *= -1; //Swap angle on touch of top or bottom
		}

		//Movement direction - 0 = left, 1 = right
		if (movement_direction == 0) {
			//Set X position
			x_pos -= movement_speed * (us.delta_time.count() / 1000.f);
		}
		else
		{
			//Set X position
			x_pos += movement_speed * (us.delta_time.count() / 1000.f);
		}

		//Apply movement angle
		y_pos += movement_angle * (us.delta_time.count() / 1000.f);

		//Update X position of ball
		ball1->xPos(x_pos);

		//Update Y position of ball
		ball1->yPos(y_pos);

		//See if we're touching the LEFT of the window
		if (hasHitEdge("Left"))
		{
			//Update points 
			player_2_points += 1;

			//Reset ball position
			ball1->xPos((game_width / 2) - (ball_size / 2));
			ball1->yPos((game_height / 2) - (ball_size / 2));

			//Reset angle
			movement_angle = 0;
		}

		//See if we're touching the RIGHT of the window
		if (hasHitEdge("Right"))
		{
			//Update points 
			player_1_points += 1;

			//Reset ball position
			ball1->xPos((game_width / 2) - (ball_size / 2));
			ball1->yPos((game_height / 2) - (ball_size / 2));

			//Reset angle
			movement_angle = 0;
		}
	}
	else 
	{
		//Keep ball reset
		ball1->xPos((game_width / 2) - (ball_size / 2));
		ball1->yPos((game_height / 2) - (ball_size / 2));
	}
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

	//Only render game if we're out of the menu
	if (is_in_menu == false) {
		//Render paddle 1
		renderer->renderSprite(*paddle1);

		//Render paddle 2
		renderer->renderSprite(*paddle2);

		//Render ball 1
		renderer->renderSprite(*ball1);

		//Points
		renderer->renderText(std::to_string(player_1_points).c_str(), 850, 25, 1.0, ASGE::COLOURS::DARKORANGE);
		renderer->renderText(std::to_string(player_2_points).c_str(), 850, 55, 1.0, ASGE::COLOURS::DARKORANGE);
	}
	else 
	{
		//Render menu title
		renderer->renderSprite(*menuTitle);

		//Option 1 - freeplay
		renderer->renderText(menu_option == 0 ? ">FREE PLAY" : " FREE PLAY", (game_width / 2), (game_height / 3) * 2 - 100, 1.0, ASGE::COLOURS::DARKORANGE);

		//Option 2 - timed 
		renderer->renderText(menu_option == 1 ? ">TIMED GAMEPLAY" : " TIMED GAMEPLAY", (game_width / 2), (game_height / 3) * 2 - 50, 1.0, ASGE::COLOURS::DARKORANGE);

		//Option 3 - first to 5
		renderer->renderText(menu_option == 2 ? ">FIRST TO 5" : " FIRST TO 5", (game_width / 2), (game_height / 3) * 2, 1.0, ASGE::COLOURS::DARKORANGE);

		//Debug
		renderer->renderText(std::to_string(menu_option).c_str(), 850, 55, 1.0, ASGE::COLOURS::DARKORANGE);
	}
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

	//See if we hit any X, this will encounter issues if we're using V-Sync
	if (int(x) == int(targetX) - 1 ||
		int(x) == int(targetX) ||
		int(x) == int(targetX) + 1) {
		hitX = true; //Hit
	}
	
	float ballY = y; //Get the Y value of our ball

	//See if we hit any Y
	for (int i = 0; i < (paddle_height + 1); i++) { //loop for whole height of paddle
		for (int b = 0; b < ball_size; b++) { //loop for whole size of ball
			if (int(sprite->yPos() + i) == int(ballY) - 1||
				int(sprite->yPos() + i) == int(ballY) ||
				int(sprite->yPos() + i) == int(ballY) + 1) {
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

/**
*   Checks to see if ball is touching the top or bottom of the screen
*/
bool Pong::hasHitEdge(std::string edgeName) const
{
	//Has hit?
	bool hasHitEdge = false;

	//Set sizes/positions
	int xPosToHit = 0;
	int yPosToHit = 0;
	int ballXPosition = ball1->xPos();
	int ballYPosition = ball1->yPos();
	if (edgeName == "Right") 
	{
		xPosToHit = game_width;
	}
	if (edgeName == "Bottom")
	{
		yPosToHit = game_height;
	}
	if (edgeName == "Left")
	{
		ballXPosition += ball_size; 
	}

	//Touching left?
	if (edgeName == "Left")
	{
		if (ballXPosition <= xPosToHit)
		{
			hasHitEdge = true; //Hit
		}
	}

	//Touching right?
	if (edgeName == "Right")
	{
		if (ballXPosition >= xPosToHit)
		{
			hasHitEdge = true; //Hit
		}
	}

	//Touching top?
	if (edgeName == "Top")
	{
		for (int i = 0; i < ball_size; i++)
		{
			if (ballYPosition + i <= yPosToHit)
			{
				hasHitEdge = true; //Hit
			}
		}
	}

	//Touching bottom?
	if (edgeName == "Bottom")
	{
		for (int i = 0; i < ball_size; i++)
		{
			if (ballYPosition + i >= yPosToHit)
			{
				hasHitEdge = true; //Hit
			}
		}
	}

	return hasHitEdge;
}