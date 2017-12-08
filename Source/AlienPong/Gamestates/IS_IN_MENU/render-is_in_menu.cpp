#include "main-is_in_menu.h"

/*
Render everything for gamestate
*/
void gamestateIsInMenu::renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer)
{
	//Handle menu screens
	if (pong_menu_state.menu_tab == menuState::MENU_TAB_2) //Tab 2
	{
		if (pong_menu_state.menu_page == menuState::MENU_PAGE_1) //Page 1, Tab 2
		{
			//Render SCOREBOARD
			renderer->renderSprite(*menu_overlay_scoreboard);
			renderer->setFont(GameFont::fonts[0]->id);

			//Scoreboard
			renderer->renderText("Scoreboard", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 65, 0.6, ASGE::COLOURS::WHITE);
			renderer->renderText("  Player 1 Rounds Won:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.4, ASGE::COLOURS::WHITE);
			renderer->renderText((std::to_string(pong_scores.scoreboard_p1)).c_str(), ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.4, ASGE::COLOURS::WHITE);
			renderer->renderText("  Player 2 Rounds Won:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 5, 0.4, ASGE::COLOURS::WHITE);
			renderer->renderText((std::to_string(pong_scores.scoreboard_p2)).c_str(), ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 5, 0.4, ASGE::COLOURS::WHITE);
			renderer->renderText("  Human (VS CPU) Rounds Won:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 35, 0.4, ASGE::COLOURS::WHITE);
			renderer->renderText((std::to_string(pong_scores.scoreboard_player)).c_str(), ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 35, 0.4, ASGE::COLOURS::WHITE);
			renderer->renderText("  CPU Rounds Won:", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 180, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 65, 0.4, ASGE::COLOURS::WHITE);
			renderer->renderText((std::to_string(pong_scores.scoreboard_cpu)).c_str(), ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) + 220, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 65, 0.4, ASGE::COLOURS::WHITE);
		}
		else //Page 2, Tab 2
		{
			//Render TWO PLAYER
			renderer->renderSprite(*menu_overlay_twoPlayer);
			renderer->setFont(GameFont::fonts[0]->id);

			//Option 1 - VS CPU 
			renderer->renderText(pong_menu_state.menu_option == menuOption::MENU_OPTION_CPU_INFINITE ? "> PLAY VS CPU - Infinite" : "  PLAY VS CPU - Infinite", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 190, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 65, 0.5, ASGE::COLOURS::WHITE);
			//Option 2 - VS CPU timed
			renderer->renderText(pong_menu_state.menu_option == menuOption::MENU_OPTION_CPU_TIMED ? "> PLAY VS CPU - Best of 60 seconds" : "  PLAY VS CPU - Best of 60 seconds", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 190, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.5, ASGE::COLOURS::WHITE);
			//Option 3 - VS CPU first to 5
			renderer->renderText(pong_menu_state.menu_option == menuOption::MENU_OPTION_CPU_SCORE ? "> PLAY VS CPU - First to 5" : "  PLAY VS CPU - First to 5", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 190, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 15, 0.5, ASGE::COLOURS::WHITE);
		}
	}
	else //Tab 1
	{
		if (pong_menu_state.menu_page == menuState::MENU_PAGE_1) //Page 1, Tab 1
		{
			//Render CONTROLS
			renderer->renderSprite(*menu_overlay_controls);
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
			renderer->renderSprite(*menu_overlay_onePlayer);
			renderer->setFont(GameFont::fonts[0]->id);

			//Option 1 - freeplay
			renderer->renderText(pong_menu_state.menu_option == menuOption::MENU_OPTION_PVP_INFINITE ? "> PLAY VS PLAYER - Infinite" : "  PLAY VS PLAYER - Infinite", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 190, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 65, 0.5, ASGE::COLOURS::WHITE);
			//Option 2 - timed 
			renderer->renderText(pong_menu_state.menu_option == menuOption::MENU_OPTION_PVP_TIMED ? "> PLAY VS PLAYER - Best of 60 seconds" : "  PLAY VS PLAYER - Best of 60 seconds", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 190, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) - 25, 0.5, ASGE::COLOURS::WHITE);
			//Option 3 - first to 5
			renderer->renderText(pong_menu_state.menu_option == menuOption::MENU_OPTION_PVP_SCORE ? "> PLAY VS PLAYER - First to 5" : "  PLAY VS PLAYER - First to 5", ((int)settings::GAMEWINDOW_MAX_WIDTH / 2) - 190, ((int)settings::GAMEWINDOW_MAX_HEIGHT / 2) + 15, 0.5, ASGE::COLOURS::WHITE);
		}
	}
}