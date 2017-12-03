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

	//Sprite resets
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

	//Load sprites


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

	
}


/*
Update the scene
*/
void Pong::update(const ASGE::GameTime & us)
{
	
}


/*
Render the scene
*/
void Pong::render(const ASGE::GameTime &)
{
	
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