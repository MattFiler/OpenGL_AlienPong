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

	//Menu background
	if (menu_background)
	{
		delete menu_background;
		menu_background = nullptr;
	}

	//Menu loading
	if (menu_overlay_loading)
	{
		delete menu_overlay_loading;
		menu_overlay_loading = nullptr;
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

	//Menu background
	menu_background = renderer->createRawSprite();
	menu_background->loadTexture(".\\Resources\\Textures\\MENU\\background.jpg");
	menu_background->width(game_width);
	menu_background->height(game_height);
	menu_background->xPos(0);
	menu_background->yPos(0);

	//Loading overlay
	menu_overlay_loading = renderer->createRawSprite();
	menu_overlay_loading->loadTexture(".\\Resources\\Textures\\MENU\\overlay_loading.png");
	menu_overlay_loading->width(game_width);
	menu_overlay_loading->height(game_height);
	menu_overlay_loading->xPos(0);
	menu_overlay_loading->yPos(0);

	//Two Player overlay
	menu_overlay_twoPlayer = renderer->createRawSprite();
	menu_overlay_twoPlayer->loadTexture(".\\Resources\\Textures\\MENU\\overlay_mode_oneplayer.png");
	menu_overlay_twoPlayer->width(game_width);
	menu_overlay_twoPlayer->height(game_height);
	menu_overlay_twoPlayer->xPos(0);
	menu_overlay_twoPlayer->yPos(0);

	//One Player overlay
	menu_overlay_onePlayer = renderer->createRawSprite();
	menu_overlay_onePlayer->loadTexture(".\\Resources\\Textures\\MENU\\overlay_mode_twoplayer.png");
	menu_overlay_onePlayer->width(game_width);
	menu_overlay_onePlayer->height(game_height);
	menu_overlay_onePlayer->xPos(0);
	menu_overlay_onePlayer->yPos(0);

	//overlay MODE: Regular
	menu_overlay_mode_regular = renderer->createRawSprite();
	menu_overlay_mode_regular->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_regular.png");
	menu_overlay_mode_regular->width(game_width);
	menu_overlay_mode_regular->height(game_height);
	menu_overlay_mode_regular->xPos(0);
	menu_overlay_mode_regular->yPos(0);

	//overlay MODE: Timed
	menu_overlay_mode_timed = renderer->createRawSprite();
	menu_overlay_mode_timed->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_timed.png");
	menu_overlay_mode_timed->width(game_width);
	menu_overlay_mode_timed->height(game_height);
	menu_overlay_mode_timed->xPos(0);
	menu_overlay_mode_timed->yPos(0);

	//overlay MODE: First to 5
	menu_overlay_mode_score = renderer->createRawSprite();
	menu_overlay_mode_score->loadTexture(".\\Resources\\Textures\\MENU\\overlay_ingame_points.png");
	menu_overlay_mode_score->width(game_width);
	menu_overlay_mode_score->height(game_height);
	menu_overlay_mode_score->xPos(0);
	menu_overlay_mode_score->yPos(0);

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
				//Reset points
				player_1_points = 0;
				player_2_points = 0;

				//Open and reset menu
				is_in_menu = true;
				menu_option = 0;
				player_has_won = false;
				show_twoplayer_overlay = false;

				//Reset gamestates
				gamestate_freeplay = false;
				gamestate_timedgameplay = false;
				gamestate_firsttofive = false;
				gamestate_vscpu = false;
				game_over = false;
				game_timer = 0;
				is_paused = false;
			}
		}
		else
		{
			//Change menu controls
			if (is_in_menu && !is_in_loadscreen) {
				right_paddle_moving = false;
				left_paddle_moving = false;

				/* MENU */
				//Swap two/one player menu on tab
				if (key->key == ASGE::KEYS::KEY_TAB && key->action == ASGE::KEYS::KEY_RELEASED) 
				{
					if (show_twoplayer_overlay) 
					{
						show_twoplayer_overlay = false;
						menu_option = 0;
					}
					else 
					{
						show_twoplayer_overlay = true;
						menu_option = 15;
					}
				}
				if (show_twoplayer_overlay)
				{
					//Go down on press of down
					if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
					{
						if (menu_option != 25)
						{
							menu_option += 5;
						}
					}
					//Go up on press of up
					if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
					{
						if (menu_option != 15)
						{
							menu_option -= 5;
						}
					}
				}
				else
				{
					//Go down on press of down
					if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
					{
						if (menu_option != 10)
						{
							menu_option += 5;
						}
					}
					//Go up on press of up
					if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
					{
						if (menu_option != 0)
						{
							menu_option -= 5;
						}
					}
				}
				//Handle menu selections
				if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					//Reset points
					game_timer = 0;
					player_1_points = 0;
					player_2_points = 0;

					//Free play
					if (menu_option == 0)
					{
						is_in_menu = false;
						gamestate_freeplay = true;
						gamestate_timedgameplay = false;
						gamestate_firsttofive = false;
						gamestate_vscpu = false;
					}
					//Timed gameplay
					if (menu_option == 5)
					{
						is_in_menu = false;
						gamestate_freeplay = false;
						gamestate_timedgameplay = true;
						gamestate_firsttofive = false;
						gamestate_vscpu = false;
					}
					//First to 5
					if (menu_option == 10)
					{
						is_in_menu = false;
						gamestate_freeplay = false;
						gamestate_timedgameplay = false;
						gamestate_firsttofive = true;
						gamestate_vscpu = false;
					}
					//VS CPU
					if (menu_option == 15)
					{
						is_in_menu = false;
						gamestate_freeplay = true;
						gamestate_timedgameplay = false;
						gamestate_firsttofive = false;
						gamestate_vscpu = true;
					}
					//VS CPU timed
					if (menu_option == 20)
					{
						is_in_menu = false;
						gamestate_freeplay = false;
						gamestate_timedgameplay = true;
						gamestate_firsttofive = false;
						gamestate_vscpu = true;
					}
					//VS CPU first to 5
					if (menu_option == 25)
					{
						is_in_menu = false;
						gamestate_freeplay = false;
						gamestate_timedgameplay = false;
						gamestate_firsttofive = true;
						gamestate_vscpu = true;
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
				if (!gamestate_vscpu) 
				{
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
	global_game_timer += (us.delta_time.count() / 1000.f);

	//Ball move speed
	int movement_speed = speed_base;

	//Get current ball position
	auto x_pos = ball1->xPos();
	auto y_pos = ball1->yPos();

	//Only run game scripts if out of menu
	if (is_in_menu == false) 
	{
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


		/* CPU PLAYER */

		if (gamestate_vscpu)
		{
			if (ball1->yPos() > (paddle2->yPos() + (ball_size * 3)) && ball1->yPos() < (paddle2->yPos() + paddle_height - (ball_size * 3)))
			{
				right_paddle_moving = false;
			}
			else
			{
				//Ball is out of paddle range, move to it
				right_paddle_moving = true;
				if (ball1->yPos() > paddle2->yPos())
				{
					right_paddle_moving_up = false;
				}
				if (ball1->yPos() < (paddle2->yPos() + paddle_height - (ball_size * 3)))
				{
					right_paddle_moving_up = true;
				}
			}
		}


		/* PADDLE MOVEMENT */

		//Right Paddle
		if (right_paddle_moving) 
		{
			//Bespoke speed modifier for CPU movement (if human player, we default to 2)
			if (int(game_timer) % cpu_speed_refresh_rate == 0 && gamestate_vscpu)
			{
				if (cpu_speed_modifier_check != int(game_timer)) 
				{
					cpu_speed_modifier = (rand() % 3) + 2.5;
					cpu_speed_modifier_check = int(game_timer);
				}
			}

			if (right_paddle_moving_up) 
			{
				//Update Y position of paddle UP
				paddle2->yPos(paddle2->yPos() - (movement_speed / cpu_speed_modifier)  * (us.delta_time.count() / 1000.f));
			}
			else
			{
				//Update Y position of paddle DOWN
				paddle2->yPos(paddle2->yPos() + (movement_speed / cpu_speed_modifier)  * (us.delta_time.count() / 1000.f));
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
		if (is_paused) 
		{
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

	//Render background
	renderer->renderSprite(*menu_background);

	//Mode overlays
	if (gamestate_freeplay)
	{
		renderer->renderSprite(*menu_overlay_mode_regular); //MODE OVERLAY: regular
	}
	if (gamestate_firsttofive)
	{
		renderer->renderSprite(*menu_overlay_mode_score); //MODE OVERLAY: score
	}
	if (gamestate_timedgameplay)
	{
		renderer->renderSprite(*menu_overlay_mode_timed); //MODE OVERLAY: timed
	}

	//DEBUG OUTPUT
	//renderer->renderText(std::to_string(menu_option).c_str(), 70, 70, 1.0, ASGE::COLOURS::WHITE);

	if (game_over)
	{
		//Win string
		std::string winner_string = "";
		if (player_1_points == player_2_points)
		{
			winner_string = "  The game was a draw!"; //Draw
		}
		if (player_1_points > player_2_points)
		{
			if (gamestate_vscpu)
			{
				winner_string = "   You won the game!"; //Human wins
			}
			else
			{
				winner_string = "Player 1 wins the game!"; //P1 wins
			}
		}
		if (player_1_points < player_2_points) 
		{
			if (gamestate_vscpu) 
			{
				winner_string = "Computer wins the game!"; //CPU wins
			} 
			else
			{
				winner_string = "Player 2 wins the game!"; //P2 wins
			}
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
			if (gamestate_vscpu) 
			{
				renderer->renderText(("Player Score: " + std::to_string(player_1_points)).c_str(), game_width - 50 - 195, game_height - 80, 1.0, ASGE::COLOURS::WHITE);
				renderer->renderText(("CPU Score: " + std::to_string(player_2_points)).c_str(), game_width - 50 - 195, game_height - 50, 1.0, ASGE::COLOURS::WHITE);
			}
			else
			{
				renderer->renderText(("Player 1 Score: " + std::to_string(player_1_points)).c_str(), game_width - 50 - 195, game_height - 80, 1.0, ASGE::COLOURS::WHITE);
				renderer->renderText(("Player 2 Score: " + std::to_string(player_2_points)).c_str(), game_width - 50 - 195, game_height - 50, 1.0, ASGE::COLOURS::WHITE);
			}

			//Timer
			if (gamestate_timedgameplay)
			{
				renderer->renderText((std::to_string(int((60 - game_timer)+0.5)) + " Seconds Remaining").c_str(), 50, game_height - 50, 1.0, ASGE::COLOURS::WHITE); 
			}
		}
		else
		{
			if (is_paused)
			{
				//Game is paused
				renderer->renderText("GAME PAUSED", (game_width / 2) - 85, (game_height / 2) - 50, 1.4, ASGE::COLOURS::WHITE);
				renderer->renderText("Press the ESC key to continue.", (game_width / 2) - 150, (game_height / 2) - 20, 1.0, ASGE::COLOURS::WHITE);
			}
			else
			{
				if (int(global_game_timer) < 3) 
				{
					//Render loading screen for first few seconds
					renderer->renderSprite(*menu_overlay_loading);
				}
				else
				{
					is_in_loadscreen = false;
					if (show_twoplayer_overlay) 
					{
						//Render TWO PLAYER
						renderer->renderSprite(*menu_overlay_twoPlayer);

						//Option 1 - VS CPU 
						renderer->renderText(menu_option == 15 ? "> PLAY - Player VS CPU" : "  PLAY - Player VS CPU", (game_width / 2) - 190, (game_height / 2) - 65, 1.0, ASGE::COLOURS::WHITE);
						//Option 2 - VS CPU timed
						renderer->renderText(menu_option == 20 ? "> PLAY - Best of 60 seconds" : "  PLAY - Best of 60 seconds", (game_width / 2) - 190, (game_height / 2) - 25, 1.0, ASGE::COLOURS::WHITE);
						//Option 3 - VS CPU first to 5
						renderer->renderText(menu_option == 25 ? "> PLAY - First to 5" : "  PLAY - First to 5", (game_width / 2) - 190, (game_height / 2) + 15, 1.0, ASGE::COLOURS::WHITE);
					} 
					else
					{
						//Render ONE PLAYER
						renderer->renderSprite(*menu_overlay_onePlayer);

						//Option 1 - freeplay
						renderer->renderText(menu_option == 0 ? "> PLAY - Player VS Player" : "  PLAY - Player VS Player", (game_width / 2) - 190, (game_height / 2) - 65, 1.0, ASGE::COLOURS::WHITE);
						//Option 2 - timed 
						renderer->renderText(menu_option == 5 ? "> PLAY - Best of 60 seconds" : "  PLAY - Best of 60 seconds", (game_width / 2) - 190, (game_height / 2) - 25, 1.0, ASGE::COLOURS::WHITE);
						//Option 3 - first to 5
						renderer->renderText(menu_option == 10 ? "> PLAY - First to 5" : "  PLAY - First to 5", (game_width / 2) - 190, (game_height / 2) + 15, 1.0, ASGE::COLOURS::WHITE);
					}
				}
			}
		}

		if (player_has_won && !game_over)
		{
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
		if (y > (sprite->yPos() - ball_size) && y < (sprite->yPos() + paddle_height))
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
		if (include_reverses)
		{
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
		if (gamestate_vscpu)
		{
			winner_name = " Player";
		}
		else
		{
			winner_name = "Player 1";
		}
	}
	else 
	{
		//Update points 
		player_2_points += 1;
		if (gamestate_vscpu)
		{
			winner_name = "  CPU";
		}
		else
		{
			winner_name = "Player 2";
		}
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