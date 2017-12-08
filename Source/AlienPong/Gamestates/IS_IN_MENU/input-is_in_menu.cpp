#include "main-is_in_menu.h"

/*
Handle user inputs
*/
void gamestateIsInMenu::keyHandler(ASGE::SharedEventData data) 
{
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	//Swap current menu group
	if (key->key == ASGE::KEYS::KEY_Q && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Play SFX
		PlaySound(TEXT("Resources_Temp\\BEEP_018.wav"), NULL, SND_ASYNC);

		//Update display
		if (pong_menu_state.menu_page == menuState::MENU_PAGE_1)
		{
			pong_menu_state.menu_page = menuState::MENU_PAGE_2;
			pong_menu_state.menu_tab = menuState::MENU_TAB_1;
			pong_menu_state.menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
		}
		else
		{
			pong_menu_state.menu_page = menuState::MENU_PAGE_1;
			pong_menu_state.menu_tab = menuState::MENU_TAB_1;
			pong_menu_state.menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
		}
	}

	//Swap top/bottom tabs on current menu group
	else if (key->key == ASGE::KEYS::KEY_TAB && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Play SFX
		PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_02.wav"), NULL, SND_ASYNC);

		//Update screen vars
		if (pong_menu_state.menu_tab == menuState::MENU_TAB_1)
		{
			pong_menu_state.menu_tab = menuState::MENU_TAB_2;
			pong_menu_state.menu_option = menuOption::MENU_OPTION_CPU_INFINITE;
		}
		else
		{
			pong_menu_state.menu_tab = menuState::MENU_TAB_1;
			pong_menu_state.menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
		}
	}

	//Swap menu selections within current tab
	else if (pong_menu_state.menu_page == menuState::MENU_PAGE_2 && pong_menu_state.menu_tab == menuState::MENU_TAB_1) //Page 2, Tab 1
	{
		//Go down on press of down
		if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if ((int)pong_menu_state.menu_option != 15)
			{
				pong_menu_state.menu_option = static_cast<menuOption>((int)pong_menu_state.menu_option + 5);
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_04.wav"), NULL, SND_ASYNC);
			}
			else
			{
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_06.wav"), NULL, SND_ASYNC);
			}
		}
		//Go up on press of up
		else if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if ((int)pong_menu_state.menu_option != 0)
			{
				pong_menu_state.menu_option = static_cast<menuOption>((int)pong_menu_state.menu_option - 5);
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_04.wav"), NULL, SND_ASYNC);
			}
			else
			{
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_06.wav"), NULL, SND_ASYNC);
			}
		}
	}
	else if (pong_menu_state.menu_page == menuState::MENU_PAGE_2 && pong_menu_state.menu_tab == menuState::MENU_TAB_2) //Page 2, Tab 2
	{
		//Go down on press of down
		if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if ((int)pong_menu_state.menu_option != 30)
			{
				pong_menu_state.menu_option = static_cast<menuOption>((int)pong_menu_state.menu_option + 5);
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_04.wav"), NULL, SND_ASYNC);
			}
			else
			{
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_06.wav"), NULL, SND_ASYNC);
			}
		}
		//Go up on press of up
		else if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if ((int)pong_menu_state.menu_option != 20)
			{
				pong_menu_state.menu_option = static_cast<menuOption>((int)pong_menu_state.menu_option - 5);
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_04.wav"), NULL, SND_ASYNC);
			}
			else
			{
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_06.wav"), NULL, SND_ASYNC);
			}
		}
	}

	//Handle menu selections
	if (key->key == ASGE::KEYS::KEY_ENTER && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		if (pong_menu_state.menu_page == menuState::MENU_PAGE_2)
		{
			//Play SFX
			PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_07.wav"), NULL, SND_ASYNC);

			//Reset points & states
			pong_variables.game_timer = 0;
			pong_scores.p1 = 0;
			pong_scores.p2 = 0;
			pong_variables.freeze_ball = false;
			pong_variables.reset_ball = true;
			pong_variables.reset_paddles = true;

			//Reset angle & direction
			pong_directions.movement_angle = 0;
			pong_directions.movement_angle_raw = 0;
			pong_directions.ball_direction = direction::RIGHT;

			//Selected infinite mode
			if (pong_menu_state.menu_option == menuOption::MENU_OPTION_PVP_INFINITE)
			{
				pong_gamestate.current_gamestate = gamestate::IS_PLAYING;
				pong_gamemode.current_gamemode = gamemode::GAMEMODE_INFINITE;
				pong_gamemode.is_against_cpu = false;
			}
			//Selected timed mode
			if (pong_menu_state.menu_option == menuOption::MENU_OPTION_PVP_TIMED)
			{
				pong_gamestate.current_gamestate = gamestate::IS_PLAYING;
				pong_gamemode.current_gamemode = gamemode::GAMEMODE_TIMED;
				pong_gamemode.is_against_cpu = false;
			}
			//Selected score-based mode
			if (pong_menu_state.menu_option == menuOption::MENU_OPTION_PVP_SCORE)
			{
				pong_gamestate.current_gamestate = gamestate::IS_PLAYING;
				pong_gamemode.current_gamemode = gamemode::GAMEMODE_SCORE;
				pong_gamemode.is_against_cpu = false;
			}
			//Selected crazy mode
			if (pong_menu_state.menu_option == menuOption::MENU_OPTION_PVP_CRAZY)
			{
				pong_gamestate.current_gamestate = gamestate::IS_PLAYING;
				pong_gamemode.current_gamemode = gamemode::GAMEMODE_CRAZY;
				pong_gamemode.is_against_cpu = false;
			}
			//Selected VS CPU infinite mode
			if (pong_menu_state.menu_option == menuOption::MENU_OPTION_CPU_INFINITE)
			{
				pong_gamestate.current_gamestate = gamestate::IS_PLAYING;
				pong_gamemode.current_gamemode = gamemode::GAMEMODE_INFINITE;
				pong_gamemode.is_against_cpu = true;
			}
			//Selected VS CPU timed mode
			if (pong_menu_state.menu_option == menuOption::MENU_OPTION_CPU_TIMED)
			{
				pong_gamestate.current_gamestate = gamestate::IS_PLAYING;
				pong_gamemode.current_gamemode = gamemode::GAMEMODE_TIMED;
				pong_gamemode.is_against_cpu = true;
			}
			//Selected VS CPU score-based mode
			if (pong_menu_state.menu_option == menuOption::MENU_OPTION_CPU_SCORE)
			{
				pong_gamestate.current_gamestate = gamestate::IS_PLAYING;
				pong_gamemode.current_gamemode = gamemode::GAMEMODE_SCORE;
				pong_gamemode.is_against_cpu = true;
			}
			//Selected VS CPU crazy mode
			if (pong_menu_state.menu_option == menuOption::MENU_OPTION_CPU_CRAZY)
			{
				pong_gamestate.current_gamestate = gamestate::IS_PLAYING;
				pong_gamemode.current_gamemode = gamemode::GAMEMODE_CRAZY;
				pong_gamemode.is_against_cpu = true;
			}
		}
	}

	//Quit game on ESC when in main menu
	else if (key->key == ASGE::KEYS::KEY_ESCAPE && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Close game & cleanup
		pong_gamestate.has_requested_shutdown = true;
	}
}