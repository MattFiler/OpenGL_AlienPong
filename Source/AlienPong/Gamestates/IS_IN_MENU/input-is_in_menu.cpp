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
		if (pongMenuState::menu_page == menuState::MENU_PAGE_1)
		{
			pongMenuState::menu_page = menuState::MENU_PAGE_2;
			pongMenuState::menu_tab = menuState::MENU_TAB_1;
			pongMenuState::menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
		}
		else
		{
			pongMenuState::menu_page = menuState::MENU_PAGE_1;
			pongMenuState::menu_tab = menuState::MENU_TAB_1;
			pongMenuState::menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
		}
	}

	//Swap top/bottom tabs on current menu group
	if (key->key == ASGE::KEYS::KEY_TAB && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Play SFX
		PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_02.wav"), NULL, SND_ASYNC);

		//Update screen vars
		if (pongMenuState::menu_tab == menuState::MENU_TAB_1)
		{
			pongMenuState::menu_tab = menuState::MENU_TAB_2;
			pongMenuState::menu_option = menuOption::MENU_OPTION_CPU_INFINITE;
		}
		else
		{
			pongMenuState::menu_tab = menuState::MENU_TAB_1;
			pongMenuState::menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
		}
	}

	//Swap menu selections within current tab
	if (pongMenuState::menu_page == menuState::MENU_PAGE_2 && pongMenuState::menu_tab == menuState::MENU_TAB_1) //Page 2, Tab 1
	{
		//Go down on press of down
		if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if ((int)pongMenuState::menu_option != 10)
			{
				pongMenuState::menu_option = static_cast<menuOption>((int)pongMenuState::menu_option + 5);
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_04.wav"), NULL, SND_ASYNC);
			}
			else
			{
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_06.wav"), NULL, SND_ASYNC);
			}
		}
		//Go up on press of up
		if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if ((int)pongMenuState::menu_option != 0)
			{
				pongMenuState::menu_option = static_cast<menuOption>((int)pongMenuState::menu_option - 5);
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_04.wav"), NULL, SND_ASYNC);
			}
			else
			{
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_06.wav"), NULL, SND_ASYNC);
			}
		}
	}
	if (pongMenuState::menu_page == menuState::MENU_PAGE_2 && pongMenuState::menu_tab == menuState::MENU_TAB_2) //Page 2, Tab 2
	{
		//Go down on press of down
		if (key->key == ASGE::KEYS::KEY_DOWN && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if ((int)pongMenuState::menu_option != 25)
			{
				pongMenuState::menu_option = static_cast<menuOption>((int)pongMenuState::menu_option + 5);
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_04.wav"), NULL, SND_ASYNC);
			}
			else
			{
				PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_06.wav"), NULL, SND_ASYNC);
			}
		}
		//Go up on press of up
		if (key->key == ASGE::KEYS::KEY_UP && key->action == ASGE::KEYS::KEY_RELEASED)
		{
			if ((int)pongMenuState::menu_option != 15)
			{
				pongMenuState::menu_option = static_cast<menuOption>((int)pongMenuState::menu_option - 5);
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
		if (pongMenuState::menu_page == menuState::MENU_PAGE_2)
		{
			//Play SFX
			PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_07.wav"), NULL, SND_ASYNC);

			//Reset points & states
			pongVariables::game_timer = 0;
			pongScores::p1 = 0;
			pongScores::p2 = 0;
			pongVariables::freeze_ball = false;
			pongVariables::reset_ball = true;
			pongVariables::reset_paddles = true;

			//Reset angle & direction
			pongDirections::movement_angle = 0;
			pongDirections::movement_angle_raw = 0;
			pongDirections::ball_direction = direction::RIGHT;

			//Selected infinite mode
			if (pongMenuState::menu_option == menuOption::MENU_OPTION_PVP_INFINITE)
			{
				pongGamestate::current_gamestate = gamestate::IS_PLAYING;
				pongGamemodes::current_gamemode = gamemode::GAMEMODE_INFINITE;
				pongGamemodes::is_against_cpu = false;
			}
			//Selected timed mode
			if (pongMenuState::menu_option == menuOption::MENU_OPTION_PVP_TIMED)
			{
				pongGamestate::current_gamestate = gamestate::IS_PLAYING;
				pongGamemodes::current_gamemode = gamemode::GAMEMODE_TIMED;
				pongGamemodes::is_against_cpu = false;
			}
			//Selected score-based mode
			if (pongMenuState::menu_option == menuOption::MENU_OPTION_PVP_SCORE)
			{
				pongGamestate::current_gamestate = gamestate::IS_PLAYING;
				pongGamemodes::current_gamemode = gamemode::GAMEMODE_SCORE;
				pongGamemodes::is_against_cpu = false;
			}
			//Selected VS CPU infinite mode
			if (pongMenuState::menu_option == menuOption::MENU_OPTION_CPU_INFINITE)
			{
				pongGamestate::current_gamestate = gamestate::IS_PLAYING;
				pongGamemodes::current_gamemode = gamemode::GAMEMODE_INFINITE;
				pongGamemodes::is_against_cpu = true;
			}
			//Selected VS CPU timed mode
			if (pongMenuState::menu_option == menuOption::MENU_OPTION_CPU_TIMED)
			{
				pongGamestate::current_gamestate = gamestate::IS_PLAYING;
				pongGamemodes::current_gamemode = gamemode::GAMEMODE_TIMED;
				pongGamemodes::is_against_cpu = true;
			}
			//Selected VS CPU score-based mode
			if (pongMenuState::menu_option == menuOption::MENU_OPTION_CPU_SCORE)
			{
				pongGamestate::current_gamestate = gamestate::IS_PLAYING;
				pongGamemodes::current_gamemode = gamemode::GAMEMODE_SCORE;
				pongGamemodes::is_against_cpu = true;
			}
		}
	}

	//Quit game on ESC when in main menu
	if (key->key == ASGE::KEYS::KEY_ESCAPE && key->action == ASGE::KEYS::KEY_RELEASED)
	{
		//Close game & cleanup
		pong_filehandler.ClearupFiles();
		while (pong_filehandler.cleanup_counter != 45)
		{
			//Wait to delete
		}
		exit(0);
	}
}