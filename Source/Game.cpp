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
		right_paddle_moving = false;
		left_paddle_moving = false;
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
			right_paddle_moving = false;
			left_paddle_moving = false;
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
				right_paddle_moving = false;
				left_paddle_moving = false;

				/* MENU */
				//Go down on press of down
				if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					if (menu_option < (((number_of_menu_options - 2) * 5) + 1) && menu_option >= 0)
					{
						menu_option += 5;
					}
				}
				//Go up on press of up
				if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					if (menu_option <= ((number_of_menu_options - 1) * 5) && menu_option > 0)
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
						gamestate_superspeed = false;
					}
					//Timed gameplay
					if (menu_option == 5)
					{
						is_in_menu = false;
						gamestate_freeplay = false;
						gamestate_timedgameplay = true;
						gamestate_firsttofive = false;
						gamestate_superspeed = false;
					}
					//First to 5
					if (menu_option == 10)
					{
						is_in_menu = false;
						gamestate_freeplay = false;
						gamestate_timedgameplay = false;
						gamestate_firsttofive = true;
						gamestate_superspeed = false;
					}
					//Super Speed - modify core game speed var
					if (menu_option == 15)
					{
						is_in_menu = false;
						gamestate_freeplay = false;
						gamestate_timedgameplay = false;
						gamestate_firsttofive = false;
						gamestate_superspeed = true;
						speed_base *= 2; //Game runs 2X faster (paddle and ball speed)
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
					left_paddle_moving = true;
					left_paddle_moving_up = true;
				}
				//Move Down
				if (key->key == ASGE::KEYS::KEY_S)
				{
					left_paddle_moving = true;
					left_paddle_moving_up = false;
				}
				//Stop moving
				if (key->key == ASGE::KEYS::KEY_W && key->action == ASGE::KEYS::KEY_RELEASED ||
					key->key == ASGE::KEYS::KEY_S && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					left_paddle_moving = false;
				}

				/* RIGHT PADDLE */
				//Move up
				if (key->key == ASGE::KEYS::KEY_UP)
				{
					right_paddle_moving = true;
					right_paddle_moving_up = true;
				}
				//Move Down
				if (key->key == ASGE::KEYS::KEY_DOWN)
				{
					right_paddle_moving = true;
					right_paddle_moving_up = false;
				}
				//Stop moving
				if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED ||
					key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					right_paddle_moving = false;
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
			right_paddle_moving = false;
			left_paddle_moving = false;
			game_over = true;
		}
	}

	//First to five game mode
	if (gamestate_firsttofive)
	{
		if (player_1_points == 5 || player_2_points == 5)
		{
			right_paddle_moving = false;
			left_paddle_moving = false;
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

		/* BALL COLLISION DETECTION */

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

		/* BALL MOVEMENT */

		//Movement direction - 0 = left, 1 = right
		if (movement_direction == 0) 
		{
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

		/* HANDLE WINS */

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

		/* PADDLE MOVEMENT */

		//Right Paddle
		if (right_paddle_moving) 
		{
			if (right_paddle_moving_up) 
			{
				//Update Y position of paddle UP
				paddle2->yPos(paddle2->yPos() - (movement_speed / 2)  * (us.delta_time.count() / 1000.f));
			}
			else
			{
				//Update Y position of paddle DOWN
				paddle2->yPos(paddle2->yPos() + (movement_speed / 2)  * (us.delta_time.count() / 1000.f));
			}
		}

		//Left Paddle
		if (left_paddle_moving)
		{
			if (left_paddle_moving_up)
			{
				//Update Y position of paddle UP
				paddle1->yPos(paddle1->yPos() - (movement_speed / 2)  * (us.delta_time.count() / 1000.f));
			}
			else
			{
				//Update Y position of paddle DOWN
				paddle1->yPos(paddle1->yPos() + (movement_speed / 2)  * (us.delta_time.count() / 1000.f));
			}
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

	//DEBUG OUTPUT
	//renderer->renderText(std::to_string(menu_option).c_str(), 50, 65, 1.0, ASGE::COLOURS::WHITE);

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
				renderer->renderText("Game Mode: Timed Gameplay", 50, 50, 1.0, ASGE::COLOURS::WHITE);
				renderer->renderText((std::to_string(int((60 - game_timer)+0.5)) + " Seconds Remaining").c_str(), 171, 80, 1.0, ASGE::COLOURS::WHITE);
			}
			//Super speed
			if (gamestate_superspeed)
			{
				renderer->renderText("Game Mode: Super Speed", 50, 65, 1.0, ASGE::COLOURS::WHITE);
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
				renderer->renderText(menu_option == 0 ? ">FREE PLAY" : " FREE PLAY", (game_width / 2) - 49, (game_height / 3) * 2 - 100, 1.0, ASGE::COLOURS::WHITE);

				//Option 2 - timed 
				renderer->renderText(menu_option == 5 ? ">TIMED GAMEPLAY" : " TIMED GAMEPLAY", (game_width / 2) - 76, (game_height / 3) * 2 - 50, 1.0, ASGE::COLOURS::WHITE);

				//Option 3 - first to 5
				renderer->renderText(menu_option == 10 ? ">FIRST TO 5" : " FIRST TO 5", (game_width / 2) - 54, (game_height / 3) * 2, 1.0, ASGE::COLOURS::WHITE);

				//Option 4 - super speed (DISABLED DUE TO HIT DETECTION ISSUES)
				//renderer->renderText(menu_option == 15 ? ">SUPER SPEED" : " SUPER SPEED", (game_width / 2) - 59, (game_height / 3) * 2 + 50, 1.0, ASGE::COLOURS::WHITE);
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
	//Auto-correct ball's X position for right paddle
	float ball_x_pos = x; 
	if (spriteName == "RightPaddle") 
	{
		ball_x_pos += ball_size;
	}

	//See if we hit any area on the paddle
	/*
		TODO: When using vectors, calculate path between the two vectors and see if it intersects the paddle.
		Should solve the lag issue when frames skip and the ball hit isn't registered.
	*/
	if (ball_x_pos > sprite->xPos() && ball_x_pos < (sprite->xPos() + paddle_width))
	{
		if (y > sprite->yPos() && y < (sprite->yPos() + paddle_height))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

/**
*   Checks to see if ball is touching the top or bottom of the screen
*/
bool Pong::hasHitEdge(std::string edgeName) const
{
	//Touching left?
	if (edgeName == "Left")
	{
		if (ball1->xPos() - ball_size <= 0)
		{
			return true; //Hit
		}
	}

	//Touching right?
	if (edgeName == "Right")
	{
		if (ball1->xPos() >= game_width)
		{
			return true; //Hit
		}
	}

	//Touching top?
	if (edgeName == "Top")
	{
		if (ball1->yPos() <= 0)
		{
			return true; //Hit
		}
	}

	//Touching bottom?
	if (edgeName == "Bottom")
	{
		if (ball1->yPos() + ball_size >= game_height)
		{
			return true; //Hit
		}
	}

	return false;
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

	//Try stop paddle moving ASAP!
	right_paddle_moving = false;
	left_paddle_moving = false;

	//Show win text
	player_has_won = true;
}