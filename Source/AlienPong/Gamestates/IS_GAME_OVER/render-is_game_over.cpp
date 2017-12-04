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
	if (pongScores::p1 > pongScores::p2)
	{
		if (pongGamemodes::is_against_cpu)
		{
			renderer->renderSprite(*menu_overlay_win_player); //Human wins
			pongFX::has_requested = true;
		}
		else
		{
			renderer->renderSprite(*menu_overlay_win_p1); //P1 wins
			pongFX::has_requested = true;
		}
	}
	if (pongScores::p1 < pongScores::p2)
	{
		if (pongGamemodes::is_against_cpu)
		{
			renderer->renderSprite(*menu_overlay_win_cpu); //CPU wins
			pongFX::has_requested = true;
		}
		else
		{
			renderer->renderSprite(*menu_overlay_win_p2); //P2 wins
			pongFX::has_requested = true;
		}
	}
}