#include "main-is_game_over.h"

/*
Render everything for gamestate
*/
void gamestateIsGameOver::renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer)
{
	//Render final win screen
	if (pongScores::p1 == pongScores::p2)
	{
		renderer->renderSprite(*menu_overlay_win_draw); //Draw
	}
	else if (pongScores::p1 > pongScores::p2)
	{
		if (pongGamemodes::is_against_cpu)
		{
			renderer->renderSprite(*menu_overlay_win_player); //Human wins
		}
		else
		{
			renderer->renderSprite(*menu_overlay_win_p1); //P1 wins
		}
	}
	else if (pongScores::p1 < pongScores::p2)
	{
		if (pongGamemodes::is_against_cpu)
		{
			renderer->renderSprite(*menu_overlay_win_cpu); //CPU wins
		}
		else
		{
			renderer->renderSprite(*menu_overlay_win_p2); //P2 wins
		}
	}

	if (pong_gamemode.current_gamemode == gamemode::GAMEMODE_CRAZY)
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText(("You Lasted " + std::to_string(int((pong_variables.game_timer) + 0.5)) + " Seconds").c_str(), 50, (int)settings::GAMEWINDOW_MAX_HEIGHT - 50, 0.4, ASGE::COLOURS::WHITE);
	}
}