#include "Game.h"


/*

//////// PONG - Created by Matt Filer /////////
///////////// GAME INITIALISATION /////////////

*/


/**
*   @brief   Default Constructor.
*/
Pong::Pong()
{
	//Change Resolution
	game_width = (int)settings::GAMEWINDOW_MAX_WIDTH;
	game_height = (int)settings::GAMEWINDOW_MAX_HEIGHT; 
}



/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
Pong::~Pong()
{
	//Input callbacks
	this->inputs->unregisterCallback(key_callback_id);

	//Font reset
	for (auto& font : GameFont::fonts)
	{
		delete font;
		font = nullptr;
	}

	//Sprite resets
	scenemanager.~sceneManager();
}


/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
run the game are loaded. The keyHandler callback should also
be set in the initialise function.
*   @return  True if the game initialised correctly.
*/
bool Pong::init()
{
	//Check graphics API has been initialised
	if (!initAPI())
	{
		return false;
	}

	//Pre-set window title
	renderer->setWindowTitle("LOADING...");

	//Change window background colour
	renderer->setClearColour(ASGE::COLOURS::BLACK);

	//Load all assets before we begin
	loadAssets();
	while(file_handler.output_counter != 45) 
	{
		//Wait to load in
	}

	//Disable sprite batching
	renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);

	//Change window title
	renderer->setWindowTitle("Pong Terminal");

	//Change window background colour
	renderer->setClearColour(ASGE::COLOURS::WHITE);

	//Enable FPS count
	//toggleFPS();

	//Disable threads
	inputs->use_threads = false;

	//Load Jixellation font to slot 0
	GameFont::fonts[0] = new GameFont(renderer->loadFont("Resources_Temp\\Jixellation.ttf", 45), "default", 45);

	//Load sprites
	scenemanager_background.loadSprites(renderer.get());
	scenemanager_foreground.loadSprites(renderer.get());
	scenemanager_foreground_static.loadSprites(renderer.get());
	scenemanger_foreground_dynamic.loadSprites(renderer.get());

	//Handle inputs
	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &Pong::keyHandler, this);

	return true;
}