#include "main-is_paused.h"


/*
Remove non-managed memory
*/
gamestateIsPaused::~gamestateIsPaused()
{
	//overlay PAUSE menu
	if (menu_overlay_paused)
	{
		delete menu_overlay_paused;
		menu_overlay_paused = nullptr;
	}
}


/*
Load sprites
*/
void gamestateIsPaused::loadSprites(ASGE::Renderer* renderer) 
{
	//overlay PAUSE screen
	menu_overlay_paused = renderer->createRawSprite();
	menu_overlay_paused->loadTexture("Resources_Temp\\overlay_ingame_paused.png");
	menu_overlay_paused->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_paused->height((int)settings::GAMEWINDOW_MAX_HEIGHT);
}