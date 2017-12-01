#include "scene_foreground.h"

/*
	Define default values
*/
sceneForeground::sceneForeground()
{

}


/*
	Destruct sprites
*/
sceneForeground::~sceneForeground()
{
	//Monitor Overlay
	if (monitor_overlay)
	{
		delete monitor_overlay;
		monitor_overlay = nullptr;
	}
}


/*
Load sprites
*/
void sceneForeground::loadSprites(std::shared_ptr<ASGE::Renderer> renderer)
{
	//Monitor overlay
	monitor_overlay = renderer->createRawSprite();
	monitor_overlay->loadTexture("Resources_Temp\\overlay_monitor_effect.png");
	monitor_overlay->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	monitor_overlay->height((int)settings::GAMEWINDOW_MAX_HEIGHT);
}