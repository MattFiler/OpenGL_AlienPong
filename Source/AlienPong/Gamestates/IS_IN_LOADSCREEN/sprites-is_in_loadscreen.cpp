#include "main-is_in_loadscreen.h"


/*
Remove non-managed memory
*/
gamestateIsInLoadscreen::~gamestateIsInLoadscreen()
{
	//Menu loading
	if (menu_overlay_loading)
	{
		delete menu_overlay_loading;
		menu_overlay_loading = nullptr;
	}

	//Menu loading 0
	if (menu_overlay_loading_s0)
	{
		delete menu_overlay_loading_s0;
		menu_overlay_loading_s0 = nullptr;
	}

	//Menu loading 1 
	if (menu_overlay_loading_s1)
	{
		delete menu_overlay_loading_s1;
		menu_overlay_loading_s1 = nullptr;
	}

	//Menu loading 2
	if (menu_overlay_loading_s2)
	{
		delete menu_overlay_loading_s2;
		menu_overlay_loading_s2 = nullptr;
	}

	//Menu loading 3
	if (menu_overlay_loading_s3)
	{
		delete menu_overlay_loading_s3;
		menu_overlay_loading_s3 = nullptr;
	}

	//Menu loading 4 
	if (menu_overlay_loading_s4)
	{
		delete menu_overlay_loading_s4;
		menu_overlay_loading_s4 = nullptr;
	}

	//Menu loading 5
	if (menu_overlay_loading_s5)
	{
		delete menu_overlay_loading_s5;
		menu_overlay_loading_s5 = nullptr;
	}
}


/*
Load sprites
*/
void gamestateIsInLoadscreen::loadSprites(ASGE::Renderer* renderer) 
{
	//Loading overlay
	menu_overlay_loading = renderer->createRawSprite();
	menu_overlay_loading->loadTexture("Resources_Temp\\overlay_loading_s.png");
	menu_overlay_loading->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S0
	menu_overlay_loading_s0 = renderer->createRawSprite();
	menu_overlay_loading_s0->loadTexture("Resources_Temp\\overlay_loading_s0.png");
	menu_overlay_loading_s0->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s0->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S1
	menu_overlay_loading_s1 = renderer->createRawSprite();
	menu_overlay_loading_s1->loadTexture("Resources_Temp\\overlay_loading_s1.png");
	menu_overlay_loading_s1->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s1->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S2
	menu_overlay_loading_s2 = renderer->createRawSprite();
	menu_overlay_loading_s2->loadTexture("Resources_Temp\\overlay_loading_s2.png");
	menu_overlay_loading_s2->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s2->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S3
	menu_overlay_loading_s3 = renderer->createRawSprite();
	menu_overlay_loading_s3->loadTexture("Resources_Temp\\overlay_loading_s3.png");
	menu_overlay_loading_s3->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s3->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S4
	menu_overlay_loading_s4 = renderer->createRawSprite();
	menu_overlay_loading_s4->loadTexture("Resources_Temp\\overlay_loading_s4.png");
	menu_overlay_loading_s4->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s4->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Loading overlay S5
	menu_overlay_loading_s5 = renderer->createRawSprite();
	menu_overlay_loading_s5->loadTexture("Resources_Temp\\overlay_loading_s5.png");
	menu_overlay_loading_s5->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_overlay_loading_s5->height((int)settings::GAMEWINDOW_MAX_HEIGHT);
}