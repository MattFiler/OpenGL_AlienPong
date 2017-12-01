#include "menu_main.h"

/*
	Default values
*/
pongMenuMain::pongMenuMain()
{
	
}

/*
	Handle main menu inputs
*/
void pongMenuMain::handleInputs()
{
	//Get engine data
	ASGE::SharedEventData data;
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	//Swap current menu group
	if (key->key == ASGE::KEYS::KEY_Q && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Play SFX
		sound_fx.playSound(4);

		//Update display
		if (current_menu_page == menuState::MENU_PAGE_1)
		{
			current_menu_page = menuState::MENU_PAGE_2;
			current_menu_tab = menuState::MENU_TAB_1;
			current_menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
		}
		else
		{
			current_menu_page = menuState::MENU_PAGE_1;
			current_menu_tab = menuState::MENU_TAB_1;
			current_menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
		}
	}

	//Swap top/bottom tabs on current menu group
	if (key->key == ASGE::KEYS::KEY_TAB && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Play SFX
		sound_fx.playSound(7);

		//Update screen vars
		if (current_menu_tab == menuState::MENU_TAB_1)
		{
			current_menu_tab = menuState::MENU_TAB_2;
			current_menu_option = menuOption::MENU_OPTION_CPU_INFINITE;
		}
		else
		{
			current_menu_tab = menuState::MENU_TAB_1;
			current_menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
		}
	}

	//Swap menu selections within current tab
	if (current_menu_page == menuState::MENU_PAGE_2 && current_menu_tab == menuState::MENU_TAB_1) //Page 2, Tab 1
	{
		//Go down on press of down
		if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if ((int)current_menu_option != 10)
			{
				current_menu_option = static_cast<menuOption>((int)current_menu_option + 5);
				sound_fx.playSound(8);
			}
			else
			{
				sound_fx.playSound(9);
			}
		}
		//Go up on press of up
		if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if ((int)current_menu_option != 0)
			{
				current_menu_option = static_cast<menuOption>((int)current_menu_option - 5);
				sound_fx.playSound(8);
			}
			else
			{
				sound_fx.playSound(9);
			}
		}
	}
	if (current_menu_page == menuState::MENU_PAGE_2 && current_menu_tab == menuState::MENU_TAB_2) //Page 2, Tab 2
	{
		//Go down on press of down
		if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if ((int)current_menu_option != 25)
			{
				current_menu_option = static_cast<menuOption>((int)current_menu_option + 5);
				sound_fx.playSound(8);
			}
			else
			{
				sound_fx.playSound(9);
			}
		}
		//Go up on press of up
		if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if ((int)current_menu_option != 15)
			{
				current_menu_option = static_cast<menuOption>((int)current_menu_option - 5);
				sound_fx.playSound(8);
			}
			else
			{
				sound_fx.playSound(9);
			}
		}
	}

	//Handle menu selections
	if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		if (gamestate.current_gamestate == gamestate::IS_IN_MENU && current_menu_page == menuState::MENU_PAGE_2)
		{
			//Play SFX
			sound_fx.playSound(10);

			//Reset points & states
			pong_vars.game_timer = 0;
			pong_points.p1 = 0;
			pong_points.p2 = 0;
			pong_vars.freeze_ball = false;

			//Reset paddle positions
			scenemanger_foreground_dynamic.paddle1->xPos(100);
			scenemanger_foreground_dynamic.paddle1->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));
			scenemanger_foreground_dynamic.paddle2->xPos((int)settings::GAMEWINDOW_MAX_WIDTH - 100);
			scenemanger_foreground_dynamic.paddle2->yPos(((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - ((int)settings::PADDLE_HEIGHT / 2));

			//Reset angle & direction
			direction.movement_angle = 0;
			direction.movement_angle_raw = 0;
			direction.ball_direction = direction::RIGHT;

			//Selected infinite mode
			if ((int)current_menu_option == 0)
			{
				gamestate.current_gamestate = gamestate::IS_PLAYING;
				gamemode.current_gamemode = gamemode::GAMEMODE_INFINITE;
				gamemode.is_against_cpu = false;
			}
			//Selected timed mode
			if ((int)current_menu_option == 5)
			{
				gamestate.current_gamestate = gamestate::IS_PLAYING;
				gamemode.current_gamemode = gamemode::GAMEMODE_TIMED;
				gamemode.is_against_cpu = false;
			}
			//Selected score-based mode
			if ((int)current_menu_option == 10)
			{
				gamestate.current_gamestate = gamestate::IS_PLAYING;
				gamemode.current_gamemode = gamemode::GAMEMODE_SCORE;
				gamemode.is_against_cpu = false;
			}
			//Selected VS CPU infinite mode
			if ((int)current_menu_option == 15)
			{
				gamestate.current_gamestate = gamestate::IS_PLAYING;
				gamemode.current_gamemode = gamemode::GAMEMODE_INFINITE;
				gamemode.is_against_cpu = true;
			}
			//Selected VS CPU timed mode
			if ((int)current_menu_option == 20)
			{
				gamestate.current_gamestate = gamestate::IS_PLAYING;
				gamemode.current_gamemode = gamemode::GAMEMODE_TIMED;
				gamemode.is_against_cpu = true;
			}
			//Selected VS CPU score-based mode
			if ((int)current_menu_option == 25)
			{
				gamestate.current_gamestate = gamestate::IS_PLAYING;
				gamemode.current_gamemode = gamemode::GAMEMODE_SCORE;
				gamemode.is_against_cpu = true;
			}
		}
	}

	//Quit game on ESC when in main menu
	if (key->key == ASGE::KEYS::KEY_ESCAPE && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Close game & cleanup
		file_handler.ClearupFiles();
		while (file_handler.cleanup_counter != 45)
		{
			//Wait to delete
		}
		exit(0);
	}
}


/*
	Render main manu
*/
void pongMenuMain::handleRender()
{

}