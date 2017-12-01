#include "scene_background.h"

/*
	Define default values
*/
sceneBackground::sceneBackground()
{

}


/*
	Destruct sprites
*/
sceneBackground::~sceneBackground()
{
	//Menu background
	if (menu_background)
	{
		delete menu_background;
		menu_background = nullptr;
	}
}


/*
	Load sprites
*/
void sceneBackground::loadSprites(std::shared_ptr<ASGE::Renderer> renderer)
{
	//Menu background
	menu_background = renderer->createRawSprite();
	menu_background->loadTexture("Resources_Temp\\background.jpg");
	menu_background->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_background->height((int)settings::GAMEWINDOW_MAX_HEIGHT);
}