#include "Pong.h"


/*
Default constructor
*/
Pong::Pong()
{
	//Change Resolution
	game_width = (int)settings::GAMEWINDOW_MAX_WIDTH;
	game_height = (int)settings::GAMEWINDOW_MAX_HEIGHT;
}


/*
Remove non-managed memory
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

	//Pong main sprite resets
	if (menu_background)
	{
		delete menu_background;
		menu_background = nullptr;
	}
	if (monitor_overlay)
	{
		delete monitor_overlay;
		monitor_overlay = nullptr;
	}

	//Gamestate sprite resets
	pong_gamestate_gameover.~gamestateIsGameOver();
	pong_gamestate_loadscreen.~gamestateIsInLoadscreen();
	pong_gamestate_menu.~gamestateIsInMenu();
	pong_gamestate_paused.~gamestateIsPaused();
	pong_gamestate_playing.~gamestateIsPlaying();
	pong_gamestate_scored.~gamestatePlayerHasWon();
}


/*
Initialise the game
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
	while (pong_filehandler.output_counter != 45)
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

	//Load FX Sprites
	pong_vhs.loadSprites(renderer.get());

	//Load gamestate-specific sprites
	pong_gamestate_gameover.loadSprites(renderer.get());
	pong_gamestate_loadscreen.loadSprites(renderer.get());
	pong_gamestate_menu.loadSprites(renderer.get());
	pong_gamestate_paused.loadSprites(renderer.get());
	pong_gamestate_playing.loadSprites(renderer.get());
	pong_gamestate_scored.loadSprites(renderer.get());

	//Load generic sprites
	menu_background = renderer->createRawSprite(); //Global Background
	menu_background->loadTexture("Resources_Temp\\background.jpg");
	menu_background->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	menu_background->height((int)settings::GAMEWINDOW_MAX_HEIGHT);
	monitor_overlay = renderer->createRawSprite(); //Global "monitor" effect overlay
	monitor_overlay->loadTexture("Resources_Temp\\overlay_monitor_effect.png");
	monitor_overlay->width((int)settings::GAMEWINDOW_MAX_WIDTH);
	monitor_overlay->height((int)settings::GAMEWINDOW_MAX_HEIGHT);

	//Handle inputs
	key_callback_id = inputs->addCallbackFnc(
		ASGE::E_KEY, &Pong::keyHandler, this);

	return true;
}


/*
Handle user inputs
*/
void Pong::keyHandler(ASGE::SharedEventData data)
{
	//Get key
	auto key = static_cast<const ASGE::KeyEvent*>(data.get());

	//Handle gamestate-specific inputs
	switch (pongGamestate::current_gamestate)
	{
		case gamestate::IS_IN_MENU:
		{
			pong_gamestate_menu.keyHandler(data);
			break;
		}
		case gamestate::IS_PLAYING:
		{
			pong_gamestate_playing.keyHandler(data);
			break;
		}
		case gamestate::IS_PAUSED:
		{
			pong_gamestate_paused.keyHandler(data);
			break;
		}
		case gamestate::PLAYER_HAS_WON:
		{
			pong_gamestate_scored.keyHandler(data);
			break;
		}
		case gamestate::IS_GAME_OVER:
		{
			pong_gamestate_gameover.keyHandler(data);
			break;
		}
	}
}


/*
Update the scene
*/
void Pong::update(const ASGE::GameTime & us)
{
	//Close game & cleanup (if requested)
	if (pongGamestate::has_requested_shutdown) {
		pong_filehandler.ClearupFiles();
		while (pong_filehandler.cleanup_counter != 45)
		{
			//Wait to delete
		}
		signalExit();
	}

	//Update timers
	if (pongGamestate::current_gamestate == gamestate::IS_PLAYING)
	{
		pongVariables::game_timer += (us.delta_time.count() / 1000.f);
	}
	pongVariables::global_game_timer += (us.delta_time.count() / 1000.f);


	//Update gamestate-specific elements
	switch (pongGamestate::current_gamestate)
	{
		case gamestate::IS_PLAYING:
		{
			pong_gamestate_playing.updateState(us);
			break;
		}
		case gamestate::IS_PAUSED:
		{
			pong_gamestate_paused.updateState(us);
			break;
		}
	}


	/*
	Timed game mode scripts
	*/
	if (pongGamemodes::current_gamemode == gamemode::GAMEMODE_TIMED)
	{
		if (pongVariables::game_timer > 60)
		{
			pongDirections::right_paddle_moving = false;
			pongDirections::left_paddle_moving = false;
			pongGamestate::current_gamestate = gamestate::IS_GAME_OVER;
			pongVariables::freeze_ball = true;
		}
	}


	/*
	Score-based game mode scripts
	*/
	if (pongGamemodes::current_gamemode == gamemode::GAMEMODE_SCORE)
	{
		if (pongScores::p1 == 5 || pongScores::p2 == 5)
		{
			pongDirections::right_paddle_moving = false;
			pongDirections::left_paddle_moving = false;
			pongGamestate::current_gamestate = gamestate::IS_GAME_OVER;
			pongVariables::freeze_ball = true;
		}
	}
}


/*
Render the scene
*/
void Pong::render(const ASGE::GameTime & us)
{
	//VFX (only when called)
	pong_vhs.renderFX(renderer.get());

	//Render global background (when not doing VFX)
	if (pongAnimationState::state != animationState::IS_PERFORMING)
		renderer->renderSprite(*menu_background);

	//Render gamestate-specific elements
	switch (pongGamestate::current_gamestate)
	{
		case gamestate::IS_IN_LOADSCREEN:
		{
			pong_gamestate_loadscreen.renderState(us, renderer.get());
			break;
		}
		case gamestate::IS_IN_MENU:
		{
			pong_gamestate_menu.renderState(us, renderer.get());
			break;
		}
		case gamestate::IS_PLAYING:
		{
			pong_gamestate_playing.renderState(us, renderer.get());
			break;
		}
		case gamestate::IS_PAUSED:
		{
			pong_gamestate_paused.renderState(us, renderer.get());
			break;
		}
		case gamestate::PLAYER_HAS_WON:
		{
			pong_gamestate_scored.renderState(us, renderer.get());
			break;
		}
		case gamestate::IS_GAME_OVER:
		{
			pong_gamestate_gameover.renderState(us, renderer.get());
			break;
		}
	}

	//Render global foreground overlay
	renderer->renderSprite(*monitor_overlay);

	//Debug output
	if (pongGamestate::show_debug_text)
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText(("Gamestate: " + std::to_string((int)pongGamestate::current_gamestate)).c_str(), 150, 550, 0.5, ASGE::COLOURS::WHITE);
		renderer->renderText(("Anim Start: " + std::to_string((int)pongFX::time_started)).c_str(), 150, 600, 0.5, ASGE::COLOURS::WHITE);
		renderer->renderText(("Anim State: " + std::to_string((int)pongAnimationState::state)).c_str(), 150, 650, 0.5, ASGE::COLOURS::WHITE);
	}
}


/*
Load our assets
*/
void Pong::loadAssets()
{
	//Load FONTS
	pong_filehandler.FetchFile("Jixellation.ttf");

	//Load SOUNDS
	pong_filehandler.FetchFile("BEEP_005.wav");
	pong_filehandler.FetchFile("BEEP_009.wav");
	pong_filehandler.FetchFile("BEEP_011.wav");
	pong_filehandler.FetchFile("BEEP_016.wav");
	pong_filehandler.FetchFile("BEEP_018.wav");
	pong_filehandler.FetchFile("BEEP_021.wav");
	pong_filehandler.FetchFile("Interactive_Terminal_Startup_SHORTENED.wav");
	pong_filehandler.FetchFile("Interactive_Terminal_Telem_02.wav");
	pong_filehandler.FetchFile("Interactive_Terminal_Telem_04.wav");
	pong_filehandler.FetchFile("Interactive_Terminal_Telem_06.wav");
	pong_filehandler.FetchFile("Interactive_Terminal_Telem_07.wav");

	//Load IMAGES
	pong_filehandler.FetchFile("whitepixel.jpg");
	pong_filehandler.FetchFile("overlay_monitor_effect.png");
	pong_filehandler.FetchFile("background.jpg");
	pong_filehandler.FetchFile("background_static00.jpg");
	pong_filehandler.FetchFile("background_static01.jpg");
	pong_filehandler.FetchFile("background_static02.jpg");
	pong_filehandler.FetchFile("background_static03.jpg");
	pong_filehandler.FetchFile("background_static04.jpg");
	pong_filehandler.FetchFile("overlay_loading_s.png");
	pong_filehandler.FetchFile("overlay_loading_s0.png");
	pong_filehandler.FetchFile("overlay_loading_s1.png");
	pong_filehandler.FetchFile("overlay_loading_s2.png");
	pong_filehandler.FetchFile("overlay_loading_s3.png");
	pong_filehandler.FetchFile("overlay_loading_s4.png");
	pong_filehandler.FetchFile("overlay_loading_s5.png");
	pong_filehandler.FetchFile("overlay_mode_oneplayer.png");
	pong_filehandler.FetchFile("overlay_mode_twoplayer.png");
	pong_filehandler.FetchFile("overlay_mode_controls.png");
	pong_filehandler.FetchFile("overlay_mode_scores.png");
	pong_filehandler.FetchFile("overlay_ingame_regular.png");
	pong_filehandler.FetchFile("overlay_ingame_timed.png");
	pong_filehandler.FetchFile("overlay_ingame_points.png");
	pong_filehandler.FetchFile("overlay_ingame_scorebox.png");
	pong_filehandler.FetchFile("overlay_ingame_paused.png");
	pong_filehandler.FetchFile("overlay_ingame_win_p1.png");
	pong_filehandler.FetchFile("overlay_ingame_win_p2.png");
	pong_filehandler.FetchFile("overlay_ingame_win_human.png");
	pong_filehandler.FetchFile("overlay_ingame_win_cpu.png");
	pong_filehandler.FetchFile("overlay_ingame_win_draw.png");
	pong_filehandler.FetchFile("overlay_ingame_score_p1.png");
	pong_filehandler.FetchFile("overlay_ingame_score_p2.png");
	pong_filehandler.FetchFile("overlay_ingame_score_human.png");
	pong_filehandler.FetchFile("overlay_ingame_score_cpu.png");
}