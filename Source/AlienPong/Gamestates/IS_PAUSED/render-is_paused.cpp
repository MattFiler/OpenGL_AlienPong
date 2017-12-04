#include "main-is_paused.h"

/*
Render everything for gamestate
*/
void gamestateIsPaused::renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer)
{
	//Game is paused
	renderer->renderSprite(*menu_overlay_paused);
	pongFX::has_requested = true;
}