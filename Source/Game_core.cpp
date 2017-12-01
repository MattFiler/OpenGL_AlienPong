#pragma once
#include "Game.h"


/*

//////// PONG - Created by Matt Filer ////////
///////////// CORE GAME SCRIPTS //////////////

*/



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

	/*
	Gamestate key handlers
	*/
	switch (gamestate.current_gamestate)
	{
		/*
		Key handlers for main menu
		*/
		case gamestate::IS_IN_MENU:
		{
			

			break;
		}

		/*
		Key handlers for the main game
		*/
		case gamestate::IS_PLAYING:
		{
			//Pause game on press of escape
			if (key->key == ASGE::KEYS::KEY_ESCAPE && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				gamestate.current_gamestate = gamestate::IS_PAUSED;

				//Play SFX
				sound_fx.playSound(0);
			}

			break;
		}

		/*
		Key handlers for pause screen
		*/
		case gamestate::IS_PAUSED:
		{
			//Close pause menu and return to game
			if (key->key == ASGE::KEYS::KEY_C && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				//Play SFX
				sound_fx.playSound(2);

				//Un-pause
				gamestate.current_gamestate = gamestate::IS_PLAYING;
				pong_fx.has_finished_cycle = false;
				pong_vars.freeze_ball = false;
			}

			//Return to main menu
			if (key->key == ASGE::KEYS::KEY_M && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				//Play SFX
				sound_fx.playSound(4);

				//Reset game and return to menu
				resetGame();
			}

			break;
		}

		/*
		Key handlers for "player has scored" screen
		*/
		case gamestate::PLAYER_HAS_WON:
		{
			//Disable all other controls
			paddle.right_paddle_moving = false;
			paddle.left_paddle_moving = false;
			if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				//Play SFX
				sound_fx.playSound(2);

				//Return to game
				gamestate.current_gamestate = gamestate::IS_PLAYING;
				pong_fx.has_finished_cycle = false;
			}

			break;
		}

		/*
		Key handlers for game over screen
		*/
		case gamestate::IS_GAME_OVER:
		{
			//Disable other controls
			paddle.right_paddle_moving = false;
			paddle.left_paddle_moving = false;
			if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				//Play SFX
				sound_fx.playSound(3);

				//Reset game and return to menu
				resetGame();
			}

			break;
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
	//Update timers
	if (gamestate.current_gamestate == gamestate::IS_PLAYING)
	{
		pong_vars.game_timer += (us.delta_time.count() / 1000.f);
	}
	pong_vars.global_game_timer += (us.delta_time.count() / 1000.f);

	//Get current ball position
	auto x_pos = scenemanger_foreground_dynamic.ball1->xPos();
	auto y_pos = scenemanger_foreground_dynamic.ball1->yPos();

	/*
	Gamestate updates
	*/
	switch (gamestate.current_gamestate)
	{
		/*
		In-game scripts
		*/
		case gamestate::IS_PLAYING:
		{
			/* BALL COLLISION DETECTION */
			//See if we're touching the LEFT paddle
			if (isTouchingPaddle(scenemanger_foreground_dynamic.paddle1, x_pos, y_pos, "LeftPaddle"))
			{
				direction.ball_direction = direction::RIGHT;
				direction.movement_angle = calculateReturnAngle(scenemanger_foreground_dynamic.paddle1, true);
				direction.movement_angle_raw = calculateReturnAngle(scenemanger_foreground_dynamic.paddle1, false);
			}
			//See if we're touching the RIGHT paddle
			if (isTouchingPaddle(scenemanger_foreground_dynamic.paddle2, x_pos, y_pos, "RightPaddle"))
			{
				direction.ball_direction = direction::LEFT;
				direction.movement_angle = calculateReturnAngle(scenemanger_foreground_dynamic.paddle2, true);
				direction.movement_angle_raw = calculateReturnAngle(scenemanger_foreground_dynamic.paddle2, false);
			}
			//See if we're touching the TOP of the window
			if (hasHitEdge("Top") || hasHitEdge("Bottom"))
			{
				direction.movement_angle *= -1; //Swap angle on touch of top or bottom
			}

			/* BALL MOVEMENT */
			//Movement direction
			if (direction.ball_direction == direction::LEFT)
			{
				//Set X position
				x_pos -= ((int)settings::DEFAULT_SPEED - direction.movement_angle_raw) * (us.delta_time.count() / 1000.f); //speed - angle to account for vertical velocity
			}
			else
			{
				//Set X position
				x_pos += ((int)settings::DEFAULT_SPEED - direction.movement_angle_raw) * (us.delta_time.count() / 1000.f); //speed - angle to account for vertical velocity
			}
			//Apply movement angle
			y_pos += direction.movement_angle * (us.delta_time.count() / 1000.f);
			if (!pong_vars.freeze_ball)
			{
				//Update X position of ball
				scenemanger_foreground_dynamic.ball1->xPos(x_pos);

				//Update Y position of ball
				scenemanger_foreground_dynamic.ball1->yPos(y_pos);
			}
			else
			{
				//Freeze ball if requested
				scenemanger_foreground_dynamic.ball1->xPos(scenemanger_foreground_dynamic.ball1->xPos());
				scenemanger_foreground_dynamic.ball1->yPos(scenemanger_foreground_dynamic.ball1->yPos());
			}

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
			if (gamemode.is_against_cpu)
			{
				if (scenemanger_foreground_dynamic.ball1->yPos() > (scenemanger_foreground_dynamic.paddle2->yPos() + ((int)settings::BALL_SIZE * 3)) && scenemanger_foreground_dynamic.ball1->yPos() < (scenemanger_foreground_dynamic.paddle2->yPos() + (int)settings::PADDLE_HEIGHT - ((int)settings::BALL_SIZE * 3)))
				{
					paddle.right_paddle_moving = false;
				}
				else
				{
					//Ball is out of paddle range, move to it
					paddle.right_paddle_moving = true;
					if (scenemanger_foreground_dynamic.ball1->yPos() > scenemanger_foreground_dynamic.paddle2->yPos())
					{
						paddle.right_paddle_direction = direction::DOWN;
					}
					if (scenemanger_foreground_dynamic.ball1->yPos() < (scenemanger_foreground_dynamic.paddle2->yPos() + (int)settings::PADDLE_HEIGHT - ((int)settings::BALL_SIZE * 3)))
					{
						paddle.right_paddle_direction = direction::UP;
					}
				}
			}

			/* PADDLE MOVEMENT */
			//Left Paddle
			if (paddle.left_paddle_moving)
			{
				if (paddle.left_paddle_direction == direction::UP)
				{
					//Update Y position of paddle UP
					scenemanger_foreground_dynamic.paddle1->yPos(scenemanger_foreground_dynamic.paddle1->yPos() - ((int)settings::DEFAULT_SPEED / 2)  * (us.delta_time.count() / 1000.f));
				}
				else
				{
					//Update Y position of paddle DOWN
					scenemanger_foreground_dynamic.paddle1->yPos(scenemanger_foreground_dynamic.paddle1->yPos() + ((int)settings::DEFAULT_SPEED / 2)  * (us.delta_time.count() / 1000.f));
				}
			}
			//Right Paddle
			if (paddle.right_paddle_moving)
			{
				//Bespoke speed modifier for CPU movement (if human player, we default to 2)
				if (int(pong_vars.game_timer) % (int)settings::CPU_SLOW_SPEED_REFRESH == 0 && gamemode.is_against_cpu)
				{
					if (pong_vars.cpu_speed_modifier_check != int(pong_vars.game_timer))
					{
						pong_vars.cpu_speed_modifier = (rand() % (int)settings::CPU_MODIFIER_EASY) + 2.5;
						pong_vars.cpu_speed_modifier_check = int(pong_vars.game_timer);
					}
				}
				if (paddle.right_paddle_direction == direction::UP)
				{
					//Update Y position of paddle UP
					scenemanger_foreground_dynamic.paddle2->yPos(scenemanger_foreground_dynamic.paddle2->yPos() - ((int)settings::DEFAULT_SPEED / pong_vars.cpu_speed_modifier)  * (us.delta_time.count() / 1000.f));
				}
				else
				{
					//Update Y position of paddle DOWN
					scenemanger_foreground_dynamic.paddle2->yPos(scenemanger_foreground_dynamic.paddle2->yPos() + ((int)settings::DEFAULT_SPEED / pong_vars.cpu_speed_modifier)  * (us.delta_time.count() / 1000.f));
				}
			}

			break;
		}

		/*
		Pause scripts
		*/
		case gamestate::IS_PAUSED:
		{
			//Freeze ball on pause
			pong_vars.freeze_ball = true;

			break;
		}

		/*
		"Player has scored" scripts
		*/
		case gamestate::PLAYER_HAS_WON:
		{
			//Keep ball reset
			scenemanger_foreground_dynamic.ball1->xPos(((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - ((int)settings::BALL_SIZE / 2));
			scenemanger_foreground_dynamic.ball1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::BALL_SIZE / 2));

			break;
		}

		/*
		Game over scripts
		*/
		case gamestate::IS_GAME_OVER:
		{
			//Keep ball reset
			scenemanger_foreground_dynamic.ball1->xPos(((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - ((int)settings::BALL_SIZE / 2));
			scenemanger_foreground_dynamic.ball1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::BALL_SIZE / 2));

			break;
		}
	}

	/*
	Timed game mode scripts
	*/
	if (gamemode.current_gamemode == gamemode::GAMEMODE_TIMED)
	{
		if (pong_vars.game_timer > 60)
		{
			paddle.right_paddle_moving = false;
			paddle.left_paddle_moving = false;
			gamestate.current_gamestate = gamestate::IS_GAME_OVER;
			pong_vars.freeze_ball = true;
		}
	}

	/*
	Score-based game mode scripts
	*/
	if (gamemode.current_gamemode == gamemode::GAMEMODE_SCORE)
	{
		if (pong_points.p1 == 5 || pong_points.p2 == 5)
		{
			paddle.right_paddle_moving = false;
			paddle.left_paddle_moving = false;
			gamestate.current_gamestate = gamestate::IS_GAME_OVER;
			pong_vars.freeze_ball = true;
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

	

	/*
	Gamestate rendering
	*/
	switch (gamestate.current_gamestate)
	{
		/*
		Render load screen on game start
		*/
		case gamestate::IS_IN_LOADSCREEN:
		{
			

			break;
		}

		/*
		Render main menu
		*/
		case gamestate::IS_IN_MENU:
		{
			if (main_menu.current_menu_tab == menuState::MENU_TAB_2) //Tab 2
			{
				if (main_menu.current_menu_page == menuState::MENU_PAGE_1) //Page 1, Tab 2
				{
					//Render SCOREBOARD
					renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_scoreboard);
					renderer->setFont(GameFont::fonts[0]->id);

					//Scoreboard
					renderer->renderText("Scoreboard", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 65, 0.6, ASGE::COLOURS::WHITE);
					renderer->renderText("  Player 1 Rounds Won:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.4, ASGE::COLOURS::WHITE);
							renderer->renderText((std::to_string(pong_points.scoreboard_p1)).c_str(), ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Player 2 Rounds Won:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 5, 0.4, ASGE::COLOURS::WHITE);
							renderer->renderText((std::to_string(pong_points.scoreboard_p2)).c_str(), ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 5, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Human (VS CPU) Rounds Won:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 35, 0.4, ASGE::COLOURS::WHITE);
							renderer->renderText((std::to_string(pong_points.scoreboard_player)).c_str(), ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 35, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  CPU Rounds Won:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 65, 0.4, ASGE::COLOURS::WHITE);
							renderer->renderText((std::to_string(pong_points.scoreboard_cpu)).c_str(), ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 65, 0.4, ASGE::COLOURS::WHITE);
				}
				else //Page 2, Tab 2
				{
					//Render TWO PLAYER
					renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_twoPlayer);
					renderer->setFont(GameFont::fonts[0]->id);

					//Option 1 - VS CPU 
					renderer->renderText(main_menu.current_menu_option == menuOption::MENU_OPTION_CPU_INFINITE ? "> PLAY VS CPU - Infinite" : "  PLAY VS CPU - Infinite", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 190, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 65, 0.5, ASGE::COLOURS::WHITE);
					//Option 2 - VS CPU timed
					renderer->renderText(main_menu.current_menu_option == menuOption::MENU_OPTION_CPU_TIMED ? "> PLAY VS CPU - Best of 60 seconds" : "  PLAY VS CPU - Best of 60 seconds", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 190, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.5, ASGE::COLOURS::WHITE);
					//Option 3 - VS CPU first to 5
					renderer->renderText(main_menu.current_menu_option == menuOption::MENU_OPTION_CPU_SCORE ? "> PLAY VS CPU - First to 5" : "  PLAY VS CPU - First to 5", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 190, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 15, 0.5, ASGE::COLOURS::WHITE);
				}
			}
			else //Tab 1
			{
				if (main_menu.current_menu_page == menuState::MENU_PAGE_1) //Page 1, Tab 1
				{
					//Render CONTROLS
					renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_controls);
					renderer->setFont(GameFont::fonts[0]->id);

					//Menu controls
					renderer->renderText("Menu Controls", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 65, 0.6, ASGE::COLOURS::WHITE);
					renderer->renderText("  Swap Primary Menu Groups:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.4, ASGE::COLOURS::WHITE);
							renderer->renderText("Q", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Swap Secondary Menu Groups:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 5, 0.4, ASGE::COLOURS::WHITE);
							renderer->renderText("TAB", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 5, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Swap Menu Choices:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 35, 0.4, ASGE::COLOURS::WHITE);
							renderer->renderText("UP/DOWN ARROW", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 35, 0.4, ASGE::COLOURS::WHITE);

					//In-game controls
					renderer->renderText("In-Game Controls", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 125, 0.6, ASGE::COLOURS::WHITE);
					renderer->renderText("  Left Paddle Up:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 165, 0.4, ASGE::COLOURS::WHITE);
							renderer->renderText("W", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 165, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Left Paddle Down:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 195, 0.4, ASGE::COLOURS::WHITE);
							renderer->renderText("S", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 195, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Right Paddle Up:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 225, 0.4, ASGE::COLOURS::WHITE);
							renderer->renderText("UP ARROW", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 225, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Right Paddle Down:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 255, 0.4, ASGE::COLOURS::WHITE);
							renderer->renderText("DOWN ARROW", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 255, 0.4, ASGE::COLOURS::WHITE);
				}
				else //Page 2, Tab 1
				{
					//Render ONE PLAYER
					renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_onePlayer);
					renderer->setFont(GameFont::fonts[0]->id);

					//Option 1 - freeplay
					renderer->renderText(main_menu.current_menu_option == menuOption::MENU_OPTION_PVP_INFINITE ? "> PLAY VS PLAYER - Infinite" : "  PLAY VS PLAYER - Infinite", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 190, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 65, 0.5, ASGE::COLOURS::WHITE);
					//Option 2 - timed 
					renderer->renderText(main_menu.current_menu_option == menuOption::MENU_OPTION_PVP_TIMED ? "> PLAY VS PLAYER - Best of 60 seconds" : "  PLAY VS PLAYER - Best of 60 seconds", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 190, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.5, ASGE::COLOURS::WHITE);
					//Option 3 - first to 5
					renderer->renderText(main_menu.current_menu_option == menuOption::MENU_OPTION_PVP_SCORE ? "> PLAY VS PLAYER - First to 5" : "  PLAY VS PLAYER - First to 5", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 190, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 15, 0.5, ASGE::COLOURS::WHITE);
				}
			}

			break;
		}

		/*
		Render the main game
		*/
		case gamestate::IS_PLAYING:
		{
			

			break;
		}

		/*
		Render pause screen
		*/
		case gamestate::IS_PAUSED:
		{
			//Game is paused
			renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_paused);
			vhs_fx.pongfx_state = animationState::HAS_BEEN_REQUESTED;
			vhs_fx.renderFX();

			break;
		}

		/*
		Render "player scored" screen
		*/
		case gamestate::PLAYER_HAS_WON:
		{
			//Render round win screen
			switch (player.winner)
			{
				case player::PLAYER_P1:
				{
					renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_score_p1); //P1 scored
					vhs_fx.pongfx_state = animationState::HAS_BEEN_REQUESTED;
					vhs_fx.renderFX();
					break;
				}
				case player::PLAYER_P2:
				{
					renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_score_p2); //P2 scored
					vhs_fx.pongfx_state = animationState::HAS_BEEN_REQUESTED;
					vhs_fx.renderFX();
					break;
				}
				case player::PLAYER_CPU:
				{
					renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_score_cpu); //CPU scored
					vhs_fx.pongfx_state = animationState::HAS_BEEN_REQUESTED;
					vhs_fx.renderFX();
					break;
				}
				case player::PLAYER_HUMAN:
				{
					renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_score_player); //Player scored
					vhs_fx.pongfx_state = animationState::HAS_BEEN_REQUESTED;
					vhs_fx.renderFX();
					break;
				}
			}

			break;
		}

		/*
		Render game over screen
		*/
		case gamestate::IS_GAME_OVER:
		{
			//Render final win screen
			if (pong_points.p1 == pong_points.p2)
			{
				renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_win_draw); //Draw
			}
			if (pong_points.p1 > pong_points.p2)
			{
				if (gamemode.is_against_cpu)
				{
					renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_win_player); //Human wins
					vhs_fx.pongfx_state = animationState::HAS_BEEN_REQUESTED;
					vhs_fx.renderFX();
				}
				else
				{
					renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_win_p1); //P1 wins
					vhs_fx.pongfx_state = animationState::HAS_BEEN_REQUESTED;
					vhs_fx.renderFX();
				}
			}
			if (pong_points.p1 < pong_points.p2)
			{
				if (gamemode.is_against_cpu)
				{
					renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_win_cpu); //CPU wins
					vhs_fx.pongfx_state = animationState::HAS_BEEN_REQUESTED;
					vhs_fx.renderFX();
				}
				else
				{
					renderer->renderSprite(*scenemanager_foreground_static.menu_overlay_win_p2); //P2 wins
					vhs_fx.pongfx_state = animationState::HAS_BEEN_REQUESTED;
					vhs_fx.renderFX();
				}
			}

			break;
		}
	}

	//Render monitor overlay - ALWAYS ON TOP
	renderer->renderSprite(*scenemanager_foreground.monitor_overlay);
}

/**
*   Checks to see if ball is touching paddle
*/
bool Pong::isTouchingPaddle(const ASGE::Sprite* sprite, float x, float y, std::string spriteName)
{
	//Auto-correct ball's X position for right paddle
	float ball_x_pos = x; 
	if (spriteName == "RightPaddle") 
	{
		ball_x_pos += (int)settings::BALL_SIZE;
	}

	//See if we hit any area on the paddle
	/*
		TODO: When using vectors, calculate path between the two vectors and see if it intersects the paddle.
		Should solve the lag issue when frames skip and the ball hit isn't registered.
	*/
	if (ball_x_pos > sprite->xPos() && ball_x_pos < (sprite->xPos() + (int)settings::PADDLE_WIDTH))
	{
		if (y > (sprite->yPos() - (int)settings::BALL_SIZE) && y < (sprite->yPos() + (int)settings::PADDLE_HEIGHT))
		{
			//Play SFX
			sound_fx.playSound(5);
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
*   Calculate the angle to return the ball at
*/
int Pong::calculateReturnAngle(const ASGE::Sprite* paddle, bool include_reverses) const
{
	//Save Y vals
	int paddle_bottom_y = paddle->yPos();
	int paddle_middle_y = paddle_bottom_y + ((int)settings::PADDLE_HEIGHT / 2);
	int paddle_top_y = paddle_bottom_y + (int)settings::PADDLE_HEIGHT;
	int ball_bottom_y = scenemanger_foreground_dynamic.ball1->yPos();
	int ball_middle_y = ball_bottom_y + ((int)settings::BALL_SIZE / 2);
	int ball_top_y = ball_bottom_y + (int)settings::BALL_SIZE;

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
		return_angle = distance_to_middle_from_middle * (int)settings::DEFAULT_ANGLE_MULTIPLIER; //use angle multiplier for return angle
	}
	else 
	{
		distance_to_middle_from_middle = paddle_middle_y - ball_middle_y; //work out distance to middle of paddle from below
		return_angle = distance_to_middle_from_middle * (int)settings::DEFAULT_ANGLE_MULTIPLIER; //use angle multiplier for return angle
		if (include_reverses)
		{
			return_angle *= -1; //reverse the direction up/down
		}
	}

	//Return the angle
	return return_angle;
}

/**
*   Scripts for win
*/
void Pong::handleWin(std::string winner_name)
{
	if (winner_name == "p1") //Left side wins
	{
		//Update points 
		pong_points.p1 += 1;
		if (gamemode.is_against_cpu)
		{
			player.winner = player::PLAYER_HUMAN; //PLAYER
			pong_points.scoreboard_player += 1;
		}
		else
		{
			player.winner = player::PLAYER_P1; //P1
			pong_points.scoreboard_p1 += 1;
		}
	}
	else //Right side wins
	{
		//Update points 
		pong_points.p2 += 1;
		if (gamemode.is_against_cpu)
		{
			player.winner = player::PLAYER_CPU; //CPU
			pong_points.scoreboard_cpu += 1;
		}
		else
		{
			player.winner = player::PLAYER_P2; //P2
			pong_points.scoreboard_p2 += 1;
		}
	}

	//Reset ball position
	scenemanger_foreground_dynamic.ball1->xPos(((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - ((int)settings::BALL_SIZE / 2));
	scenemanger_foreground_dynamic.ball1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::BALL_SIZE / 2));

	//Reset paddle positions
	scenemanger_foreground_dynamic.paddle1->xPos(100);
	scenemanger_foreground_dynamic.paddle1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));
	scenemanger_foreground_dynamic.paddle2->xPos((int)settings::GAMEWINDOW_MAX_WIDTH - 100);
	scenemanger_foreground_dynamic.paddle2->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));

	//Play SFX
	sound_fx.playSound(1);

	//Reset angle
	direction.movement_angle = 0;

	//Try stop paddle moving ASAP!
	paddle.right_paddle_moving = false;
	paddle.left_paddle_moving = false;

	//Update gamestate
	gamestate.current_gamestate = gamestate::PLAYER_HAS_WON;
}

/**
*   Perform a game reset
*/
void Pong::resetGame()
{
	//Reset points
	pong_points.p1 = 0;
	pong_points.p2 = 0;

	//Open and reset menu
	gamestate.current_gamestate = gamestate::IS_IN_MENU;
	main_menu.current_menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
	main_menu.current_menu_page = menuState::MENU_PAGE_1;
	main_menu.current_menu_tab = menuState::MENU_TAB_1;

	//Reset gamestates, settings & vars
	gamemode.current_gamemode = gamemode::NO_GAMEMODE;
	gamemode.is_against_cpu = false;
	pong_vars.game_timer = 0;
	pong_vars.freeze_ball = true;
	direction.ball_direction = direction::RIGHT;
	pong_vars.cpu_speed_modifier = 2;
	direction.movement_angle = 0;
	pong_fx.has_finished_cycle = false;

	//Reset ball position
	scenemanger_foreground_dynamic.ball1->xPos(((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - ((int)settings::BALL_SIZE / 2));
	scenemanger_foreground_dynamic.ball1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::BALL_SIZE / 2));

	//Reset paddle positions
	scenemanger_foreground_dynamic.paddle1->xPos(100);
	scenemanger_foreground_dynamic.paddle1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));
	scenemanger_foreground_dynamic.paddle2->xPos((int)settings::GAMEWINDOW_MAX_WIDTH - 100);
	scenemanger_foreground_dynamic.paddle2->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));
}

/*
	Load our assets
*/
void Pong::loadAssets() 
{
	//Load FONTS
	file_handler.FetchFile("Jixellation.ttf");

	//Load SOUNDS
	file_handler.FetchFile("BEEP_005.wav");
	file_handler.FetchFile("BEEP_009.wav");
	file_handler.FetchFile("BEEP_011.wav");
	file_handler.FetchFile("BEEP_016.wav");
	file_handler.FetchFile("BEEP_018.wav");
	file_handler.FetchFile("BEEP_021.wav");
	file_handler.FetchFile("Interactive_Terminal_Startup_SHORTENED.wav");
	file_handler.FetchFile("Interactive_Terminal_Telem_02.wav");
	file_handler.FetchFile("Interactive_Terminal_Telem_04.wav");
	file_handler.FetchFile("Interactive_Terminal_Telem_06.wav");
	file_handler.FetchFile("Interactive_Terminal_Telem_07.wav");

	//Load IMAGES
	file_handler.FetchFile("whitepixel.jpg");
	file_handler.FetchFile("overlay_monitor_effect.png");
	file_handler.FetchFile("background.jpg");
	file_handler.FetchFile("background_static00.jpg");
	file_handler.FetchFile("background_static01.jpg");
	file_handler.FetchFile("background_static02.jpg");
	file_handler.FetchFile("background_static03.jpg");
	file_handler.FetchFile("background_static04.jpg");
	file_handler.FetchFile("overlay_loading_s.png");
	file_handler.FetchFile("overlay_loading_s0.png");
	file_handler.FetchFile("overlay_loading_s1.png");
	file_handler.FetchFile("overlay_loading_s2.png");
	file_handler.FetchFile("overlay_loading_s3.png");
	file_handler.FetchFile("overlay_loading_s4.png");
	file_handler.FetchFile("overlay_loading_s5.png");
	file_handler.FetchFile("overlay_mode_oneplayer.png");
	file_handler.FetchFile("overlay_mode_twoplayer.png");
	file_handler.FetchFile("overlay_mode_controls.png");
	file_handler.FetchFile("overlay_mode_scores.png");
	file_handler.FetchFile("overlay_ingame_regular.png");
	file_handler.FetchFile("overlay_ingame_timed.png");
	file_handler.FetchFile("overlay_ingame_points.png");
	file_handler.FetchFile("overlay_ingame_scorebox.png");
	file_handler.FetchFile("overlay_ingame_paused.png");
	file_handler.FetchFile("overlay_ingame_win_p1.png");
	file_handler.FetchFile("overlay_ingame_win_p2.png");
	file_handler.FetchFile("overlay_ingame_win_human.png");
	file_handler.FetchFile("overlay_ingame_win_cpu.png");
	file_handler.FetchFile("overlay_ingame_win_draw.png");
	file_handler.FetchFile("overlay_ingame_score_p1.png");
	file_handler.FetchFile("overlay_ingame_score_p2.png");
	file_handler.FetchFile("overlay_ingame_score_human.png");
	file_handler.FetchFile("overlay_ingame_score_cpu.png");
}

/**
*   Checks to see if ball is touching the top or bottom of the screen
*/
bool Pong::hasHitEdge(std::string edgeName) const
{
	//Touching left?
	if (edgeName == "Left")
	{
		if (scenemanger_foreground_dynamic.ball1->xPos() - (int)settings::BALL_SIZE <= 0)
		{
			return true; //Hit
		}
	}

	//Touching right?
	if (edgeName == "Right")
	{
		if (scenemanger_foreground_dynamic.ball1->xPos() >= (int)settings::GAMEWINDOW_MAX_WIDTH)
		{
			return true; //Hit
		}
	}

	//Touching top?
	if (edgeName == "Top")
	{
		if (scenemanger_foreground_dynamic.ball1->yPos() <= 0)
		{
			return true; //Hit
		}
	}

	//Touching bottom?
	if (edgeName == "Bottom")
	{
		if (scenemanger_foreground_dynamic.ball1->yPos() + (int)settings::BALL_SIZE >= (int)settings::GAMEWINDOW_MAX_HEIGHT)
		{
			return true; //Hit
		}
	}

	return false;
}