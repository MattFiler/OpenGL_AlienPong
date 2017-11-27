#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Constants.h"
#include "Game.h"
#include "GameFont.h"

#ifdef _WIN32
	#include <windows.h>
	#include <mmsystem.h>
#endif


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
	switch (gamestate)
	{
		/*
		Key handlers for main menu
		*/
		case IS_IN_MENU:
		{
			//Force stop paddles
			right_paddle_moving = false;
			left_paddle_moving = false;

			//Swap current menu group
			if (key->key == ASGE::KEYS::KEY_Q && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				//Play SFX
				PlaySound(TEXT("../../Resources/Audio/BEEP_018.wav"), NULL, SND_ASYNC);

				//Update display
				if (menu_page == MENU_PAGE_1)
				{
					menu_page = MENU_PAGE_2;
					menu_tab = MENU_TAB_1;
					menu_option = MENU_OPTION_PVP_INFINITE;
				}
				else
				{
					menu_page = MENU_PAGE_1;
					menu_tab = MENU_TAB_1;
					menu_option = MENU_OPTION_PVP_INFINITE;
				}
			}

			//Swap top/bottom tabs on current menu group
			if (key->key == ASGE::KEYS::KEY_TAB && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				//Play SFX
				PlaySound(TEXT("../../Resources/Audio/Interactive_Terminal_Telem_02.wav"), NULL, SND_ASYNC);

				//Update screen vars
				if (menu_tab == MENU_TAB_1)
				{
					menu_tab = MENU_TAB_2;
					menu_option = MENU_OPTION_CPU_INFINITE;
				}
				else
				{
					menu_tab = MENU_TAB_1;
					menu_option = MENU_OPTION_PVP_INFINITE;
				}
			}

			//Swap menu selections within current tab
			if (menu_page == MENU_PAGE_2 && menu_tab == MENU_TAB_1) //Page 2, Tab 1
			{
				//Go down on press of down
				if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					if (menu_option != 10)
					{
						menu_option += 5;
						PlaySound(TEXT("../../Resources/Audio/Interactive_Terminal_Telem_04.wav"), NULL, SND_ASYNC);
					}
					else
					{
						PlaySound(TEXT("../../Resources/Audio/Interactive_Terminal_Telem_06.wav"), NULL, SND_ASYNC);
					}
				}
				//Go up on press of up
				if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					if (menu_option != 0)
					{
						menu_option -= 5;
						PlaySound(TEXT("../../Resources/Audio/Interactive_Terminal_Telem_04.wav"), NULL, SND_ASYNC);
					}
					else
					{
						PlaySound(TEXT("../../Resources/Audio/Interactive_Terminal_Telem_06.wav"), NULL, SND_ASYNC);
					}
				}
			}
			if (menu_page == MENU_PAGE_2 && menu_tab == MENU_TAB_2) //Page 2, Tab 2
			{
				//Go down on press of down
				if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					if (menu_option != 25)
					{
						menu_option += 5;
						PlaySound(TEXT("../../Resources/Audio/Interactive_Terminal_Telem_04.wav"), NULL, SND_ASYNC);
					}
					else
					{
						PlaySound(TEXT("../../Resources/Audio/Interactive_Terminal_Telem_06.wav"), NULL, SND_ASYNC);
					}
				}
				//Go up on press of up
				if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					if (menu_option != 15)
					{
						menu_option -= 5;
						PlaySound(TEXT("../../Resources/Audio/Interactive_Terminal_Telem_04.wav"), NULL, SND_ASYNC);
					}
					else
					{
						PlaySound(TEXT("../../Resources/Audio/Interactive_Terminal_Telem_06.wav"), NULL, SND_ASYNC);
					}
				}
			}

			//Handle menu selections
			if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				if (gamestate == IS_IN_MENU && menu_page == MENU_PAGE_2)
				{
					//Play SFX
					PlaySound(TEXT("../../Resources/Audio/Interactive_Terminal_Telem_07.wav"), NULL, SND_ASYNC);

					//Reset points & states
					pong_core.game_timer = 0;
					pong_points.p1 = 0;
					pong_points.p2 = 0;
					pong_core.freeze_ball = false;

					//Reset paddle positions
					paddle1->xPos(100);
					paddle1->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (PADDLE_HEIGHT / 2));
					paddle2->xPos(GAMEWINDOW_MAX_WIDTH - 100);
					paddle2->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (PADDLE_HEIGHT / 2));

					//Reset angle & direction
					movement_angle = 0;
					movement_angle_raw = 0;
					ball_direction = RIGHT;

					//Selected infinite mode
					if (menu_option == 0)
					{
						gamestate = IS_PLAYING;
						gamemode = GAMEMODE_INFINITE;
						is_against_cpu = false;
					}
					//Selected timed mode
					if (menu_option == 5)
					{
						gamestate = IS_PLAYING;
						gamemode = GAMEMODE_TIMED;
						is_against_cpu = false;
					}
					//Selected score-based mode
					if (menu_option == 10)
					{
						gamestate = IS_PLAYING;
						gamemode = GAMEMODE_SCORE;
						is_against_cpu = false;
					}
					//Selected VS CPU infinite mode
					if (menu_option == 15)
					{
						gamestate = IS_PLAYING;
						gamemode = GAMEMODE_INFINITE;
						is_against_cpu = true;
					}
					//Selected VS CPU timed mode
					if (menu_option == 20)
					{
						gamestate = IS_PLAYING;
						gamemode = GAMEMODE_TIMED;
						is_against_cpu = true;
					}
					//Selected VS CPU score-based mode
					if (menu_option == 25)
					{
						gamestate = IS_PLAYING;
						gamemode = GAMEMODE_SCORE;
						is_against_cpu = true;
					}
				}
			}

			//Quit game on ESC when in main menu
			if (key->key == ASGE::KEYS::KEY_ESCAPE && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				signalExit();
			}

			break;
		}

		/*
		Key handlers for the main game
		*/
		case IS_PLAYING:
		{
			/* LEFT PADDLE */
			//Move up
			if (key->key == ASGE::KEYS::KEY_W)
			{
				left_paddle_moving = true;
				left_paddle_direction = UP;
			}
			//Move Down
			if (key->key == ASGE::KEYS::KEY_S)
			{
				left_paddle_moving = true;
				left_paddle_direction = DOWN;
			}
			//Stop moving
			if (key->key == ASGE::KEYS::KEY_W && key->action == ASGE::KEYS::KEY_RELEASED ||
				key->key == ASGE::KEYS::KEY_S && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				left_paddle_moving = false;
			}

			/* RIGHT PADDLE */
			if (!is_against_cpu)
			{
				//Move up
				if (key->key == ASGE::KEYS::KEY_UP)
				{
					right_paddle_moving = true;
					right_paddle_direction = UP;
				}
				//Move Down
				if (key->key == ASGE::KEYS::KEY_DOWN)
				{
					right_paddle_moving = true;
					right_paddle_direction = DOWN;
				}
				//Stop moving
				if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED ||
					key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
				{
					right_paddle_moving = false;
				}
			}

			//Pause game on press of escape
			if (key->key == ASGE::KEYS::KEY_ESCAPE && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				gamestate = IS_PAUSED;

				//Play SFX
				PlaySound(TEXT("../../Resources/Audio/BEEP_005.wav"), NULL, SND_ASYNC);
			}

			break;
		}

		/*
		Key handlers for pause screen
		*/
		case IS_PAUSED:
		{
			//Close pause menu and return to game
			if (key->key == ASGE::KEYS::KEY_C && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				//Play SFX
				PlaySound(TEXT("../../Resources/Audio/BEEP_011.wav"), NULL, SND_ASYNC);

				//Un-pause
				gamestate = IS_PLAYING;
				pong_fx.has_finished_cycle = false;
				pong_core.freeze_ball = false;
			}

			//Return to main menu
			if (key->key == ASGE::KEYS::KEY_M && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				//Play SFX
				PlaySound(TEXT("../../Resources/Audio/BEEP_018.wav"), NULL, SND_ASYNC);

				//Reset game and return to menu
				resetGame();
			}

			break;
		}

		/*
		Key handlers for "player has scored" screen
		*/
		case PLAYER_HAS_WON:
		{
			//Disable all other controls
			right_paddle_moving = false;
			left_paddle_moving = false;
			if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				//Play SFX
				PlaySound(TEXT("../../Resources/Audio/BEEP_011.wav"), NULL, SND_ASYNC);

				//Return to game
				gamestate = IS_PLAYING;
				pong_fx.has_finished_cycle = false;
			}

			break;
		}

		/*
		Key handlers for game over screen
		*/
		case IS_GAME_OVER:
		{
			//Disable other controls
			right_paddle_moving = false;
			left_paddle_moving = false;
			if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
			{
				//Play SFX
				PlaySound(TEXT("../../Resources/Audio/BEEP_016.wav"), NULL, SND_ASYNC);

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
	if (gamestate == IS_PLAYING)
	{
		pong_core.game_timer += (us.delta_time.count() / 1000.f);
	}
	pong_core.global_game_timer += (us.delta_time.count() / 1000.f);

	//Get current ball position
	auto x_pos = ball1->xPos();
	auto y_pos = ball1->yPos();

	/*
	Gamestate updates
	*/
	switch (gamestate)
	{
		/*
		In-game scripts
		*/
		case IS_PLAYING:
		{
			/* BALL COLLISION DETECTION */
			//See if we're touching the LEFT paddle
			if (isTouchingPaddle(paddle1, x_pos, y_pos, "LeftPaddle"))
			{
				ball_direction = RIGHT;
				movement_angle = calculateReturnAngle(paddle1, true);
				movement_angle_raw = calculateReturnAngle(paddle1, false);
			}
			//See if we're touching the RIGHT paddle
			if (isTouchingPaddle(paddle2, x_pos, y_pos, "RightPaddle"))
			{
				ball_direction = LEFT;
				movement_angle = calculateReturnAngle(paddle2, true);
				movement_angle_raw = calculateReturnAngle(paddle2, false);
			}
			//See if we're touching the TOP of the window
			if (hasHitEdge("Top") || hasHitEdge("Bottom"))
			{
				movement_angle *= -1; //Swap angle on touch of top or bottom
			}

			/* BALL MOVEMENT */
			//Movement direction
			if (ball_direction == LEFT)
			{
				//Set X position
				x_pos -= (DEFAULT_SPEED - movement_angle_raw) * (us.delta_time.count() / 1000.f); //speed - angle to account for vertical velocity
			}
			else
			{
				//Set X position
				x_pos += (DEFAULT_SPEED - movement_angle_raw) * (us.delta_time.count() / 1000.f); //speed - angle to account for vertical velocity
			}
			//Apply movement angle
			y_pos += movement_angle * (us.delta_time.count() / 1000.f);
			if (!pong_core.freeze_ball)
			{
				//Update X position of ball
				ball1->xPos(x_pos);

				//Update Y position of ball
				ball1->yPos(y_pos);
			}
			else
			{
				//Freeze ball if requested
				ball1->xPos(ball1->xPos());
				ball1->yPos(ball1->yPos());
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
			if (is_against_cpu)
			{
				if (ball1->yPos() > (paddle2->yPos() + (BALL_SIZE * 3)) && ball1->yPos() < (paddle2->yPos() + PADDLE_HEIGHT - (BALL_SIZE * 3)))
				{
					right_paddle_moving = false;
				}
				else
				{
					//Ball is out of paddle range, move to it
					right_paddle_moving = true;
					if (ball1->yPos() > paddle2->yPos())
					{
						right_paddle_direction = DOWN;
					}
					if (ball1->yPos() < (paddle2->yPos() + PADDLE_HEIGHT - (BALL_SIZE * 3)))
					{
						right_paddle_direction = UP;
					}
				}
			}

			/* PADDLE MOVEMENT */
			//Left Paddle
			if (left_paddle_moving)
			{
				if (left_paddle_direction == UP)
				{
					//Update Y position of paddle UP
					paddle1->yPos(paddle1->yPos() - (DEFAULT_SPEED / 2)  * (us.delta_time.count() / 1000.f));
				}
				else
				{
					//Update Y position of paddle DOWN
					paddle1->yPos(paddle1->yPos() + (DEFAULT_SPEED / 2)  * (us.delta_time.count() / 1000.f));
				}
			}
			//Right Paddle
			if (right_paddle_moving)
			{
				//Bespoke speed modifier for CPU movement (if human player, we default to 2)
				if (int(pong_core.game_timer) % CPU_SLOW_SPEED_REFRESH == 0 && is_against_cpu)
				{
					if (pong_core.cpu_speed_modifier_check != int(pong_core.game_timer))
					{
						pong_core.cpu_speed_modifier = (rand() % CPU_MODIFIER_EASY) + 2.5;
						pong_core.cpu_speed_modifier_check = int(pong_core.game_timer);
					}
				}
				if (right_paddle_direction == UP)
				{
					//Update Y position of paddle UP
					paddle2->yPos(paddle2->yPos() - (DEFAULT_SPEED / pong_core.cpu_speed_modifier)  * (us.delta_time.count() / 1000.f));
				}
				else
				{
					//Update Y position of paddle DOWN
					paddle2->yPos(paddle2->yPos() + (DEFAULT_SPEED / pong_core.cpu_speed_modifier)  * (us.delta_time.count() / 1000.f));
				}
			}

			break;
		}

		/*
		Pause scripts
		*/
		case IS_PAUSED:
		{
			//Freeze ball on pause
			pong_core.freeze_ball = true;

			break;
		}

		/*
		"Player has scored" scripts
		*/
		case PLAYER_HAS_WON:
		{
			//Keep ball reset
			ball1->xPos((GAMEWINDOW_MAX_WIDTH / 2) - (BALL_SIZE / 2));
			ball1->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (BALL_SIZE / 2));

			break;
		}

		/*
		Game over scripts
		*/
		case IS_GAME_OVER:
		{
			//Keep ball reset
			ball1->xPos((GAMEWINDOW_MAX_WIDTH / 2) - (BALL_SIZE / 2));
			ball1->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (BALL_SIZE / 2));

			break;
		}
	}

	/*
	Timed game mode scripts
	*/
	if (gamemode == GAMEMODE_TIMED)
	{
		if (pong_core.game_timer > 60)
		{
			right_paddle_moving = false;
			left_paddle_moving = false;
			gamestate = IS_GAME_OVER;
			pong_core.freeze_ball = true;
		}
	}

	/*
	Score-based game mode scripts
	*/
	if (gamemode == GAMEMODE_SCORE)
	{
		if (pong_points.p1 == 5 || pong_points.p2 == 5)
		{
			right_paddle_moving = false;
			left_paddle_moving = false;
			gamestate = IS_GAME_OVER;
			pong_core.freeze_ball = true;
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

	//Debug output
	//renderer->renderText((std::to_string(cpu_speed_modifier)).c_str(),55, 55, 0.5, ASGE::COLOURS::WHITE);

	/*
	Render FX if requested (and not already performing)
	*/
	if (pong_fx.has_requested || //Has requested effect?
		((pong_fx.time_started + pong_fx.time_in_seconds) < pong_core.global_game_timer && pong_fx.is_performing) //Is in time range for performing effect?
		) 
	{
		if (!pong_fx.has_finished_cycle)
		{
			if (pong_fx.is_performing == false)
			{
				pong_fx.time_started = pong_core.global_game_timer; //Log start time (if not already performing)
			}
			pong_fx.is_performing = false;

			//Run animation
			if (pong_core.global_game_timer - pong_fx.time_started < 0.01)
			{
				renderer->renderSprite(*menu_background_s00);
				pong_fx.is_performing = true;
			}
			if (pong_core.global_game_timer - pong_fx.time_started < 0.03 && pong_core.global_game_timer - pong_fx.time_started >= 0.01)
			{
				renderer->renderSprite(*menu_background_s01);
				pong_fx.is_performing = true;
			}
			if (pong_core.global_game_timer - pong_fx.time_started < 0.04 && pong_core.global_game_timer - pong_fx.time_started >= 0.03)
			{
				renderer->renderSprite(*menu_background_s02);
				pong_fx.is_performing = true;
			}
			if (pong_core.global_game_timer - pong_fx.time_started < 0.06 && pong_core.global_game_timer - pong_fx.time_started >= 0.04)
			{
				renderer->renderSprite(*menu_background_s03);
				pong_fx.is_performing = true;
			}
			if (pong_core.global_game_timer - pong_fx.time_started < 0.07 && pong_core.global_game_timer - pong_fx.time_started >= 0.06)
			{
				renderer->renderSprite(*menu_background_s04);
				pong_fx.is_performing = true;
				pong_fx.has_finished_cycle = true;
			}

			pong_fx.has_requested = false; //Clear request
		}
	}

	/*
	Render overlays for each mode (as long as we're not in the menu)
	*/
	if (gamemode == GAMEMODE_INFINITE && gamestate != IS_IN_MENU)
		renderer->renderSprite(*menu_overlay_mode_regular); //MODE OVERLAY: regular
	if (gamemode == GAMEMODE_SCORE && gamestate != IS_IN_MENU)
		renderer->renderSprite(*menu_overlay_mode_score); //MODE OVERLAY: score
	if (gamemode == GAMEMODE_TIMED && gamestate != IS_IN_MENU)
		renderer->renderSprite(*menu_overlay_mode_timed); //MODE OVERLAY: timed

	/*
	Gamestate rendering
	*/
	switch (gamestate) 
	{
		/*
		Render load screen on game start
		*/
		case IS_IN_LOADSCREEN:
		{
			//Render loading screen for first few seconds
			if (int(pong_core.global_game_timer) < 3.2)
			{
				//Speed
				float stage_0 = 0.3;
				float stage_1 = 0.7;
				float stage_2 = 1.2;
				float stage_3 = 1.6;
				float stage_4 = 2.1;
				float stage_5 = 2.5;
				float stage_6 = 2.8;

				//Play SFX
				if (!pong_core.has_performed_startup_sound) {
					PlaySound(TEXT("../../Resources/Audio/Interactive_Terminal_Startup_SHORTENED.wav"), NULL, SND_ASYNC);
					//PlaySound(TEXT("../../Resources/Audio/Interactive_Terminal_BG_Loop.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
					pong_core.has_performed_startup_sound = true;
				}

				//Animation
				if (pong_core.global_game_timer < stage_0)
				{
					renderer->renderSprite(*menu_overlay_loading);
					pong_fx.has_requested = true;
				}
				if (pong_core.global_game_timer < stage_1 && pong_core.global_game_timer >= stage_0)
					renderer->renderSprite(*menu_overlay_loading_s0);
				if (pong_core.global_game_timer < stage_2 && pong_core.global_game_timer >= stage_1)
					renderer->renderSprite(*menu_overlay_loading_s1);
				if (pong_core.global_game_timer < stage_3 && pong_core.global_game_timer >= stage_2)
					renderer->renderSprite(*menu_overlay_loading_s2);
				if (pong_core.global_game_timer < stage_4 && pong_core.global_game_timer >= stage_3)
					renderer->renderSprite(*menu_overlay_loading_s3);
				if (pong_core.global_game_timer < stage_5 && pong_core.global_game_timer >= stage_4)
					renderer->renderSprite(*menu_overlay_loading_s4);
				if ((pong_core.global_game_timer < stage_6 && pong_core.global_game_timer >= stage_5) || pong_core.global_game_timer >= stage_6)
				{
					renderer->renderSprite(*menu_overlay_loading_s5);
					pong_fx.has_finished_cycle = false;
				}
			}
			else
			{
				gamestate = IS_IN_MENU; //Take us out of the animation
			}

			break;
		}

		/*
		Render main menu
		*/
		case IS_IN_MENU:
		{
			if (menu_tab == MENU_TAB_2) //Tab 2
			{
				if (menu_page == MENU_PAGE_1) //Page 1, Tab 2
				{
					//Render SCOREBOARD
					renderer->renderSprite(*menu_overlay_scoreboard);
					renderer->setFont(GameFont::fonts[0]->id);

					//Scoreboard
					renderer->renderText("Scoreboard", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) - 65, 0.6, ASGE::COLOURS::WHITE);
					renderer->renderText("  Player 1 Rounds Won:", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText((std::to_string(pong_points.scoreboard_p1)).c_str(), (GAMEWINDOW_MAX_WIDTH / 2) + 220, (GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Player 2 Rounds Won:", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) + 5, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText((std::to_string(pong_points.scoreboard_p2)).c_str(), (GAMEWINDOW_MAX_WIDTH / 2) + 220, (GAMEWINDOW_MAX_HEIGHT / 2) + 5, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Human (VS CPU) Rounds Won:", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) + 35, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText((std::to_string(pong_points.scoreboard_player)).c_str(), (GAMEWINDOW_MAX_WIDTH / 2) + 220, (GAMEWINDOW_MAX_HEIGHT / 2) + 35, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  CPU Rounds Won:", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) + 65, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText((std::to_string(pong_points.scoreboard_cpu)).c_str(), (GAMEWINDOW_MAX_WIDTH / 2) + 220, (GAMEWINDOW_MAX_HEIGHT / 2) + 65, 0.4, ASGE::COLOURS::WHITE);
				}
				else //Page 2, Tab 2
				{
					//Render TWO PLAYER
					renderer->renderSprite(*menu_overlay_twoPlayer);
					renderer->setFont(GameFont::fonts[0]->id);

					//Option 1 - VS CPU 
					renderer->renderText(menu_option == MENU_OPTION_CPU_INFINITE ? "> PLAY VS CPU - Infinite" : "  PLAY VS CPU - Infinite", (GAMEWINDOW_MAX_WIDTH / 2) - 190, (GAMEWINDOW_MAX_HEIGHT / 2) - 65, 0.5, ASGE::COLOURS::WHITE);
					//Option 2 - VS CPU timed
					renderer->renderText(menu_option == MENU_OPTION_CPU_TIMED ? "> PLAY VS CPU - Best of 60 seconds" : "  PLAY VS CPU - Best of 60 seconds", (GAMEWINDOW_MAX_WIDTH / 2) - 190, (GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.5, ASGE::COLOURS::WHITE);
					//Option 3 - VS CPU first to 5
					renderer->renderText(menu_option == MENU_OPTION_CPU_SCORE ? "> PLAY VS CPU - First to 5" : "  PLAY VS CPU - First to 5", (GAMEWINDOW_MAX_WIDTH / 2) - 190, (GAMEWINDOW_MAX_HEIGHT / 2) + 15, 0.5, ASGE::COLOURS::WHITE);
				}
			}
			else //Tab 1
			{
				if (menu_page == MENU_PAGE_1) //Page 1, Tab 1
				{
					//Render CONTROLS
					renderer->renderSprite(*menu_overlay_controls);
					renderer->setFont(GameFont::fonts[0]->id);

					//Menu controls
					renderer->renderText("Menu Controls", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) - 65, 0.6, ASGE::COLOURS::WHITE);
					renderer->renderText("  Swap Primary Menu Groups:", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.4, ASGE::COLOURS::WHITE);
													renderer->renderText("Q", (GAMEWINDOW_MAX_WIDTH / 2) + 220, (GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Swap Secondary Menu Groups:", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) + 5, 0.4, ASGE::COLOURS::WHITE);
													renderer->renderText("TAB", (GAMEWINDOW_MAX_WIDTH / 2) + 220, (GAMEWINDOW_MAX_HEIGHT / 2) + 5, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Swap Menu Choices:", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) + 35, 0.4, ASGE::COLOURS::WHITE);
													renderer->renderText("UP/DOWN ARROW", (GAMEWINDOW_MAX_WIDTH / 2) + 220, (GAMEWINDOW_MAX_HEIGHT / 2) + 35, 0.4, ASGE::COLOURS::WHITE);

					//In-game controls
					renderer->renderText("In-Game Controls", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) + 125, 0.6, ASGE::COLOURS::WHITE);
					renderer->renderText("  Left Paddle Up:", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) + 165, 0.4, ASGE::COLOURS::WHITE);
													renderer->renderText("W", (GAMEWINDOW_MAX_WIDTH / 2) + 220, (GAMEWINDOW_MAX_HEIGHT / 2) + 165, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Left Paddle Down:", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) + 195, 0.4, ASGE::COLOURS::WHITE);
													renderer->renderText("S", (GAMEWINDOW_MAX_WIDTH / 2) + 220, (GAMEWINDOW_MAX_HEIGHT / 2) + 195, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Right Paddle Up:", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) + 225, 0.4, ASGE::COLOURS::WHITE);
													renderer->renderText("UP ARROW", (GAMEWINDOW_MAX_WIDTH / 2) + 220, (GAMEWINDOW_MAX_HEIGHT / 2) + 225, 0.4, ASGE::COLOURS::WHITE);
					renderer->renderText("  Right Paddle Down:", (GAMEWINDOW_MAX_WIDTH / 2) - 180, (GAMEWINDOW_MAX_HEIGHT / 2) + 255, 0.4, ASGE::COLOURS::WHITE);
													renderer->renderText("DOWN ARROW", (GAMEWINDOW_MAX_WIDTH / 2) + 220, (GAMEWINDOW_MAX_HEIGHT / 2) + 255, 0.4, ASGE::COLOURS::WHITE);
				}
				else //Page 2, Tab 1
				{
					//Render ONE PLAYER
					renderer->renderSprite(*menu_overlay_onePlayer);
					renderer->setFont(GameFont::fonts[0]->id);

					//Option 1 - freeplay
					renderer->renderText(menu_option == MENU_OPTION_PVP_INFINITE ? "> PLAY VS PLAYER - Infinite" : "  PLAY VS PLAYER - Infinite", (GAMEWINDOW_MAX_WIDTH / 2) - 190, (GAMEWINDOW_MAX_HEIGHT / 2) - 65, 0.5, ASGE::COLOURS::WHITE);
					//Option 2 - timed 
					renderer->renderText(menu_option == MENU_OPTION_PVP_TIMED ? "> PLAY VS PLAYER - Best of 60 seconds" : "  PLAY VS PLAYER - Best of 60 seconds", (GAMEWINDOW_MAX_WIDTH / 2) - 190, (GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.5, ASGE::COLOURS::WHITE);
					//Option 3 - first to 5
					renderer->renderText(menu_option == MENU_OPTION_PVP_SCORE ? "> PLAY VS PLAYER - First to 5" : "  PLAY VS PLAYER - First to 5", (GAMEWINDOW_MAX_WIDTH / 2) - 190, (GAMEWINDOW_MAX_HEIGHT / 2) + 15, 0.5, ASGE::COLOURS::WHITE);
				}
			}

			break;
		}

		/*
		Render the main game
		*/
		case IS_PLAYING:
		{
			//Render paddle 1
			renderer->renderSprite(*paddle1);

			//Render paddle 2
			renderer->renderSprite(*paddle2);

			//Render ball 1
			renderer->renderSprite(*ball1);

			//Render score box
			renderer->renderSprite(*menu_overlay_score_box);

			//Render Points
			if (is_against_cpu)
			{
				renderer->setFont(GameFont::fonts[0]->id);
				renderer->renderText("Player", GAMEWINDOW_MAX_WIDTH - 50 - 175, GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
									renderer->renderText((std::to_string(pong_points.p1)).c_str(), GAMEWINDOW_MAX_WIDTH - 85, GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
				renderer->renderText("CPU", GAMEWINDOW_MAX_WIDTH - 50 - 175, GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
									renderer->renderText((std::to_string(pong_points.p2)).c_str(), GAMEWINDOW_MAX_WIDTH - 85, GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
			}
			else
			{
				renderer->setFont(GameFont::fonts[0]->id);
				renderer->renderText("Player 1", GAMEWINDOW_MAX_WIDTH - 50 - 175, GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
									renderer->renderText((std::to_string(pong_points.p1)).c_str(), GAMEWINDOW_MAX_WIDTH - 85, GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
				renderer->renderText("Player 2", GAMEWINDOW_MAX_WIDTH - 50 - 175, GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
									renderer->renderText((std::to_string(pong_points.p2)).c_str(), GAMEWINDOW_MAX_WIDTH - 85, GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
			}

			//Render Timer
			if (gamemode == GAMEMODE_TIMED)
			{
				renderer->setFont(GameFont::fonts[0]->id);
				renderer->renderText((std::to_string(int((60 - pong_core.game_timer) + 0.5)) + " Seconds Remaining").c_str(), 50, GAMEWINDOW_MAX_HEIGHT - 50, 0.4, ASGE::COLOURS::WHITE);
			}

			break;
		}

		/*
		Render pause screen
		*/
		case IS_PAUSED:
		{
			//Game is paused
			renderer->renderSprite(*menu_overlay_paused);
			pong_fx.has_requested = true;

			break;
		}

		/*
		Render "player scored" screen
		*/
		case PLAYER_HAS_WON:
		{
			//Render round win screen
			switch (winner)
			{
				case PLAYER_P1:
				{
					renderer->renderSprite(*menu_overlay_score_p1); //P1 scored
					pong_fx.has_requested = true;
					break;
				}
				case PLAYER_P2:
				{
					renderer->renderSprite(*menu_overlay_score_p2); //P2 scored
					pong_fx.has_requested = true;
					break;
				}
				case PLAYER_CPU:
				{
					renderer->renderSprite(*menu_overlay_score_cpu); //CPU scored
					pong_fx.has_requested = true;
					break;
				}
				case PLAYER_HUMAN:
				{
					renderer->renderSprite(*menu_overlay_score_player); //Player scored
					pong_fx.has_requested = true;
					break;
				}
			}

			break;
		}

		/*
		Render game over screen
		*/
		case IS_GAME_OVER: 
		{
			//Render final win screen
			if (pong_points.p1 == pong_points.p2)
			{
				renderer->renderSprite(*menu_overlay_win_draw); //Draw
			}
			if (pong_points.p1 > pong_points.p2)
			{
				if (is_against_cpu)
				{
					renderer->renderSprite(*menu_overlay_win_player); //Human wins
					pong_fx.has_requested = true;
				}
				else
				{
					renderer->renderSprite(*menu_overlay_win_p1); //P1 wins
					pong_fx.has_requested = true;
				}
			}
			if (pong_points.p1 < pong_points.p2)
			{
				if (is_against_cpu)
				{
					renderer->renderSprite(*menu_overlay_win_cpu); //CPU wins
					pong_fx.has_requested = true;
				}
				else
				{
					renderer->renderSprite(*menu_overlay_win_p2); //P2 wins
					pong_fx.has_requested = true;
				}
			}

			break;
		}
	}

	//Render monitor overlay - ALWAYS ON TOP
	renderer->renderSprite(*monitor_overlay);
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
		ball_x_pos += BALL_SIZE;
	}

	//See if we hit any area on the paddle
	/*
		TODO: When using vectors, calculate path between the two vectors and see if it intersects the paddle.
		Should solve the lag issue when frames skip and the ball hit isn't registered.
	*/
	if (ball_x_pos > sprite->xPos() && ball_x_pos < (sprite->xPos() + PADDLE_WIDTH))
	{
		if (y > (sprite->yPos() - BALL_SIZE) && y < (sprite->yPos() + PADDLE_HEIGHT))
		{
			//Play SFX
			PlaySound(TEXT("../../Resources/Audio/BEEP_021.wav"), NULL, SND_ASYNC | SND_NOSTOP);
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
		if (ball1->xPos() - BALL_SIZE <= 0)
		{
			return true; //Hit
		}
	}

	//Touching right?
	if (edgeName == "Right")
	{
		if (ball1->xPos() >= GAMEWINDOW_MAX_WIDTH)
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
		if (ball1->yPos() + BALL_SIZE >= GAMEWINDOW_MAX_HEIGHT)
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
	int paddle_middle_y = paddle_bottom_y + (PADDLE_HEIGHT / 2);
	int paddle_top_y = paddle_bottom_y + PADDLE_HEIGHT;
	int ball_bottom_y = ball1->yPos();
	int ball_middle_y = ball_bottom_y + (BALL_SIZE / 2);
	int ball_top_y = ball_bottom_y + BALL_SIZE;

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
		return_angle = distance_to_middle_from_middle * DEFAULT_ANGLE_MULTIPLIER; //use angle multiplier for return angle
	}
	else 
	{
		distance_to_middle_from_middle = paddle_middle_y - ball_middle_y; //work out distance to middle of paddle from below
		return_angle = distance_to_middle_from_middle * DEFAULT_ANGLE_MULTIPLIER; //use angle multiplier for return angle
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
		if (is_against_cpu)
		{
			winner = PLAYER_HUMAN; //PLAYER
			pong_points.scoreboard_player += 1;
		}
		else
		{
			winner = PLAYER_P1; //P1
			pong_points.scoreboard_p1 += 1;
		}
	}
	else //Right side wins
	{
		//Update points 
		pong_points.p2 += 1;
		if (is_against_cpu)
		{
			winner = PLAYER_CPU; //CPU
			pong_points.scoreboard_cpu += 1;
		}
		else
		{
			winner = PLAYER_P2; //P2
			pong_points.scoreboard_p2 += 1;
		}
	}

	//Reset ball position
	ball1->xPos((GAMEWINDOW_MAX_WIDTH / 2) - (BALL_SIZE / 2));
	ball1->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (BALL_SIZE / 2));

	//Reset paddle positions
	paddle1->xPos(100);
	paddle1->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (PADDLE_HEIGHT / 2));
	paddle2->xPos(GAMEWINDOW_MAX_WIDTH - 100);
	paddle2->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (PADDLE_HEIGHT / 2));

	//Play SFX
	PlaySound(TEXT("../../Resources/Audio/BEEP_009.wav"), NULL, SND_ASYNC);

	//Reset angle
	movement_angle = 0;

	//Try stop paddle moving ASAP!
	right_paddle_moving = false;
	left_paddle_moving = false;

	//Update gamestate
	gamestate = PLAYER_HAS_WON;
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
	gamestate = IS_IN_MENU;
	menu_option = MENU_OPTION_PVP_INFINITE;
	menu_page = MENU_PAGE_1;
	menu_tab = MENU_TAB_1;

	//Reset gamestates, settings & vars
	gamemode = NO_GAMEMODE;
	is_against_cpu = false;
	pong_core.game_timer = 0;
	pong_core.freeze_ball = true;
	ball_direction = RIGHT;
	pong_core.cpu_speed_modifier = 2;
	movement_angle = 0;
	pong_fx.has_finished_cycle = false;

	//Reset ball position
	ball1->xPos((GAMEWINDOW_MAX_WIDTH / 2) - (BALL_SIZE / 2));
	ball1->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (BALL_SIZE / 2));

	//Reset paddle positions
	paddle1->xPos(100);
	paddle1->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (PADDLE_HEIGHT / 2));
	paddle2->xPos(GAMEWINDOW_MAX_WIDTH - 100);
	paddle2->yPos((GAMEWINDOW_MAX_HEIGHT / 2) - (PADDLE_HEIGHT / 2));
}