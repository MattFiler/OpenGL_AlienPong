#include "main-player_has_won.h"

/*
Render everything for gamestate
*/
void gamestatePlayerHasWon::renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer)
{
	//Render round win screen
	switch (pongPlayers::winner)
	{
		case player::PLAYER_P1:
		{
			renderer->renderSprite(*menu_overlay_score_p1); //P1 scored
			pongFX::has_requested = true;
			break;
		}
		case player::PLAYER_P2:
		{
			renderer->renderSprite(*menu_overlay_score_p2); //P2 scored
			pongFX::has_requested = true;
			break;
		}
		case player::PLAYER_CPU:
		{
			renderer->renderSprite(*menu_overlay_score_cpu); //CPU scored
			pongFX::has_requested = true;
			break;
		}
		case player::PLAYER_HUMAN:
		{
			renderer->renderSprite(*menu_overlay_score_player); //Player scored
			pongFX::has_requested = true;
			break;
		}
	}
}