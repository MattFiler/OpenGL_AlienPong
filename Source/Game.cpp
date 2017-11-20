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

	if (player_has_won) 
	{
		//Winning screen currently showing, disable all other controls
		if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			player_has_won = false;
		}

		if (game_over)
		{
			player_has_won = false;
		}
	}
	else
	{
		if (game_over) 
		{
			//Game over screen showing, disable other controls
			if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				/* SOMETHING NOT WORKING HERE */
				game_over = false;
				is_in_menu = true; //send back to menu
			}
		}
		else
		{
			//Change menu controls
			if (is_in_menu) {
				/* MENU */
				//Go down on press of down
				if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					if (menu_option < 6 && menu_option >= 0)
					{
						menu_option += 5;
					}
				}
				//Go up on press of up
				if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					if (menu_option <= 10 && menu_option > 0)
					{
						menu_option -= 5;
					}
				}
				//Handle menu selections
				if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					//Free play
					if (menu_option == 0)
					{
						is_in_menu = false;
						gamestate_freeplay = true;
						gamestate_timedgameplay = false;
						gamestate_firsttofive = false;
					}
					//Timed gameplay
					if (menu_option == 5)
					{
						is_in_menu = false;
						gamestate_freeplay = false;
						gamestate_timedgameplay = true;
						gamestate_firsttofive = false;
					}
					//First to 5
					if (menu_option == 10)
					{
						is_in_menu = false;
						gamestate_freeplay = false;
						gamestate_timedgameplay = false;
						gamestate_firsttofive = true;
					}
				}

				//Quit on ESC
				if (key->key == ASGE::KEYS::KEY_ESCAPE && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					if (!is_paused) 
					{
						signalExit();
					}
					else 
					{
						is_in_menu = false;
						is_paused = false;
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

				//Pause on ESC
				if (key->key == ASGE::KEYS::KEY_ESCAPE && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					is_in_menu = true;
					is_paused = true;
				}
			}
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
	//Update global game timer (if in-game)
	if (is_in_menu == false && player_has_won == false)
	{
		game_timer += (us.delta_time.count() / 1000.f);
	}

	//Timed game mode
	if (gamestate_timedgameplay)
	{
		if (game_timer > 60)
		{
			game_over = true;
		}
	}

	//First to five game mode
	if (gamestate_firsttofive)
	{
		if (player_1_points == 5 || player_2_points == 5)
		{
			game_over = true;
		}
	}

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
			movement_angle = calculateReturnAngle(paddle1, true);
			movement_angle_raw = calculateReturnAngle(paddle1, false);
		}

		//See if we're touching the RIGHT paddle
		if (isTouchingPaddle(paddle2, x_pos, y_pos, "RightPaddle"))
		{
			movement_direction = 0;
			movement_angle = calculateReturnAngle(paddle2, true);
			movement_angle_raw = calculateReturnAngle(paddle2, false);
		}

		//See if we're touching the TOP of the window
		if (hasHitEdge("Top") || hasHitEdge("Bottom"))
		{
			movement_angle *= -1; //Swap angle on touch of top or bottom
		}

		//Movement direction - 0 = left, 1 = right
		if (movement_direction == 0) {
			//Set X position
			x_pos -= (movement_speed - movement_angle_raw) * (us.delta_time.count() / 1000.f); //speed - angle to account for vertical velocity
		}
		else
		{
			//Set X position
			x_pos += (movement_speed - movement_angle_raw) * (us.delta_time.count() / 1000.f); //speed - angle to account for vertical velocity
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
			//Player 2 wins
			handleWin("p2");
		}

		//See if we're touching the RIGHT of the window
		if (hasHitEdge("Right"))
		{
			//Player 1 wins
			handleWin("p1");
		}
	}
	else 
	{
		if (is_paused) {
			//Freeze ball on pause
			ball1->xPos(ball1->xPos());
			ball1->yPos(ball1->yPos());
		}
		else
		{
			//Keep ball reset
			ball1->xPos((game_width / 2) - (ball_size / 2));
			ball1->yPos((game_height / 2) - (ball_size / 2));
		}
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

	if (game_over)
	{
		//Win string
		std::string winner_string = "";
		if (player_1_points > player_2_points) {
			winner_string = "Player 1 wins the game!"; //P1 wins
		}
		if (player_1_points < player_2_points) {
			winner_string = "Player 2 wins the game!"; //P2 wins
		}
		if (player_1_points == player_2_points) {
			winner_string = "No player won the game!"; //Draw
		}

		//Render round win screen
		renderer->renderText((winner_string).c_str(), (game_width / 2) - 160, (game_height / 2) - 50, 1.4, ASGE::COLOURS::WHITE);
		renderer->renderText("Press ENTER key to continue.", (game_width / 2) - 135, (game_height / 2) - 20, 1.0, ASGE::COLOURS::WHITE);
		
		//Clear player win state
		player_has_won = false;
	}
	else
	{
		//Only render game if we're out of the menu
		if (is_in_menu == false)
		{
			//Render paddle 1
			renderer->renderSprite(*paddle1);

			//Render paddle 2
			renderer->renderSprite(*paddle2);

			//Render ball 1
			renderer->renderSprite(*ball1);

			//Points
			renderer->renderText(("Player 1 Score: " + std::to_string(player_1_points)).c_str(), game_width - 50 - 195, 50, 1.0, ASGE::COLOURS::WHITE);
			renderer->renderText(("Player 2 Score: " + std::to_string(player_2_points)).c_str(), game_width - 50 - 195, 80, 1.0, ASGE::COLOURS::WHITE);

			//First to 5
			if (gamestate_firsttofive) 
			{
				renderer->renderText("Game Mode: First to Five", 50, 65, 1.0, ASGE::COLOURS::WHITE);
			}
			//Freemode
			if (gamestate_freeplay)
			{
				renderer->renderText("Game Mode: Free Play", 50, 65, 1.0, ASGE::COLOURS::WHITE);
			}
			//Timed gameplay
			if (gamestate_timedgameplay)
			{
				renderer->renderText("Game Mode: Timed Gameplay", 50, 65, 1.0, ASGE::COLOURS::WHITE);
			}
		}
		else
		{
			//Render menu title
			renderer->renderSprite(*menuTitle);

			if (is_paused)
			{
				renderer->renderText("GAME PAUSED", (game_width / 2) - 85, (game_height / 2) - 50, 1.4, ASGE::COLOURS::WHITE);
				renderer->renderText("Press the ESC key to continue.", (game_width / 2) - 150, (game_height / 2) - 20, 1.0, ASGE::COLOURS::WHITE);
			}
			else
			{
				//Option 1 - freeplay
				renderer->renderText(menu_option == 0 ? ">FREE PLAY" : " FREE PLAY", (game_width / 2), (game_height / 3) * 2 - 100, 1.0, ASGE::COLOURS::DARKORANGE);

				//Option 2 - timed 
				renderer->renderText(menu_option == 5 ? ">TIMED GAMEPLAY" : " TIMED GAMEPLAY", (game_width / 2), (game_height / 3) * 2 - 50, 1.0, ASGE::COLOURS::DARKORANGE);

				//Option 3 - first to 5
				renderer->renderText(menu_option == 10 ? ">FIRST TO 5" : " FIRST TO 5", (game_width / 2), (game_height / 3) * 2, 1.0, ASGE::COLOURS::DARKORANGE);
			}
		}

		if (player_has_won) {
			//Render round win screen
			renderer->renderText((winner_name + " wins a point!").c_str(), (game_width / 2) - 150, (game_height / 2) - 50, 1.4, ASGE::COLOURS::WHITE);
			renderer->renderText("Press ENTER key to continue.", (game_width / 2) - 135, (game_height / 2) - 20, 1.0, ASGE::COLOURS::WHITE);
		}
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

		if (int(x) <= int(targetX)) {
			hitX = true; //Hit
		}
	}
	if (spriteName == "RightPaddle") {
		targetX = sprite->xPos() - ball_size; //Adjust X position for right paddle

		if (int(x) >= int(targetX)) {
			hitX = true; //Hit
		}
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

/**
*   Calculate the angle to return the ball at
*/
int Pong::calculateReturnAngle(const ASGE::Sprite* paddle, bool include_reverses) const
{
	//Save Y vals
	int paddle_bottom_y = paddle->yPos();
	int paddle_middle_y = paddle_bottom_y + (paddle_height / 2);
	int paddle_top_y = paddle_bottom_y + paddle_height;
	int ball_bottom_y = ball1->yPos();
	int ball_middle_y = ball_bottom_y + (ball_size / 2);
	int ball_top_y = ball_bottom_y + ball_size;

	//Values to set later
	int distance_to_middle_from_middle = 0;
	int return_angle = 0;
	
	//Check if we hit below (or on) the middle of the paddle
	bool hit_below_bottom = false;
	for (int i = 0; i < 11; i++) 
	{
		if (ball_bottom_y + i <= paddle_middle_y) 
		{
			hit_below_bottom = true;
		}
	}

	//Vary directions based on hit location
	if (hit_below_bottom == false) 
	{
		distance_to_middle_from_middle = ball_middle_y - paddle_middle_y; //work out distance to middle of paddle from above
		return_angle = distance_to_middle_from_middle * 2.5; //use distance * 2 for angle
		if (include_reverses) {
			return_angle *= -1; //reverse the direction up/down
		}
	}
	else 
	{
		distance_to_middle_from_middle = paddle_middle_y - ball_middle_y; //work out distance to middle of paddle from below
		return_angle = distance_to_middle_from_middle * 2.5; //use distance * 2 for angle
	}

	//Return the angle
	return return_angle;
}

/**
*   Scripts for win
*/
void Pong::handleWin(std::string winner)
{
	if (winner == "p1")
	{
		//Update points 
		player_1_points += 1;
		winner_name = "Player 1";
	}
	else 
	{
		//Update points 
		player_2_points += 1;
		winner_name = "Player 2";
	}

	//Reset ball position
	ball1->xPos((game_width / 2) - (ball_size / 2));
	ball1->yPos((game_height / 2) - (ball_size / 2));

	//Reset paddle positions
	paddle1->xPos(100);
	paddle1->yPos((game_height / 2) - (paddle_height / 2));
	paddle2->xPos(game_width - 100);
	paddle2->yPos((game_height / 2) - (paddle_height / 2));

	//Reset angle
	movement_angle = 0;

	//Show win text
	player_has_won = true;
}