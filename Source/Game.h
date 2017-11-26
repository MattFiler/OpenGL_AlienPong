#pragma once
#include <string>
#include <Engine/OGLGame.h>

struct GameFont;


/*

//////// PONG - Created by Matt Filer ////////
//////////////// GAME HEADER /////////////////

*/



/*
TODO:
	Implement vector class
	Point line checker to account for frame lag
	Jixellation.ttf font import?
*/



class Pong :
	public ASGE::OGLGame
{
public:
	Pong();
	~Pong();
	virtual bool init() override;

private:
	void keyHandler(ASGE::SharedEventData data);
	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;


	bool isTouchingPaddle(const ASGE::Sprite* sprite, float x, float y, std::string spriteName) const;
	bool hasHitEdge(std::string edgeName) const;
	int calculateReturnAngle(const ASGE::Sprite* paddle, bool include_reverses) const;
	void handleWin(std::string winner_name);
	void resetGame();


	bool exit = false;                  /**< Exit boolean. If true the game loop will exit. */
	int  key_callback_id = -1;	        /**< Key Input Callback ID. */


	ASGE::Sprite* paddle1 = nullptr;    /**< Sprite Object. Paddle 1. */
	ASGE::Sprite* paddle2 = nullptr;    /**< Sprite Object. Paddle 2. */
	ASGE::Sprite* ball1 = nullptr;      /**< Sprite Object. Ball. */
	
	ASGE::Sprite* menu_background = nullptr;  //Menu background
	ASGE::Sprite* menu_background_s00 = nullptr;  //Menu background s00
	ASGE::Sprite* menu_background_s01 = nullptr;  //Menu background s01
	ASGE::Sprite* menu_background_s02 = nullptr;  //Menu background s02
	ASGE::Sprite* menu_background_s03 = nullptr;  //Menu background s03
	ASGE::Sprite* menu_background_s04 = nullptr;  //Menu background s04

	ASGE::Sprite* menu_overlay_loading = nullptr; //Menu loading overlay
	ASGE::Sprite* menu_overlay_loading_s0 = nullptr; //Menu loading overlay S0
	ASGE::Sprite* menu_overlay_loading_s1 = nullptr; //Menu loading overlay S1
	ASGE::Sprite* menu_overlay_loading_s2 = nullptr; //Menu loading overlay S2
	ASGE::Sprite* menu_overlay_loading_s3 = nullptr; //Menu loading overlay S3
	ASGE::Sprite* menu_overlay_loading_s4 = nullptr; //Menu loading overlay S4
	ASGE::Sprite* menu_overlay_loading_s5 = nullptr; //Menu loading overlay S5

	ASGE::Sprite* menu_overlay_twoPlayer = nullptr; //Menu TwoPlayer overlay
	ASGE::Sprite* menu_overlay_onePlayer = nullptr; //Menu OnePlayer overlay
	ASGE::Sprite* menu_overlay_controls = nullptr; //Menu controls overlay
	ASGE::Sprite* menu_overlay_scoreboard = nullptr; //Menu scores overlay
	 
	ASGE::Sprite* menu_overlay_mode_regular = nullptr; //in-game MODE overlay regular
	ASGE::Sprite* menu_overlay_mode_timed = nullptr; //in-game MODE overlay timed
	ASGE::Sprite* menu_overlay_mode_score = nullptr; //in-game MODE overlay score

	ASGE::Sprite* menu_overlay_paused = nullptr; //in-game PAUSE screen

	ASGE::Sprite* monitor_overlay = nullptr;  //monitor overlay effect

	ASGE::Sprite* menu_overlay_win_p1 = nullptr; //in-game WIN screen - P1
	ASGE::Sprite* menu_overlay_win_p2 = nullptr; //in-game WIN screen - P2
	ASGE::Sprite* menu_overlay_win_player = nullptr; //in-game WIN screen - PLAYER
	ASGE::Sprite* menu_overlay_win_cpu = nullptr; //in-game WIN screen - CPU
	ASGE::Sprite* menu_overlay_win_draw = nullptr; //in-game WIN screen - DRAW

	ASGE::Sprite* menu_overlay_score_p1 = nullptr; //in-game SCORE screen - P1
	ASGE::Sprite* menu_overlay_score_p2 = nullptr; //in-game SCORE screen - P2
	ASGE::Sprite* menu_overlay_score_player = nullptr; //in-game SCORE screen - PLAYER
	ASGE::Sprite* menu_overlay_score_cpu = nullptr; //in-game SCORE screen - CPU


	//Global game values and settings
	enum game_definitions { GAMEWINDOW_MAX_WIDTH = 1024, GAMEWINDOW_MAX_HEIGHT = 768, 
							PADDLE_HEIGHT = 150, PADDLE_WIDTH = 10, 
							BALL_SIZE = 10,
							DEFAULT_ANGLE_MULTIPLIER = 2, HIGH_ANGLE_MULTIPLIER = 3,
							DEFAULT_SPEED = 600, HIGH_SPEED = 1000,
							CPU_SLOW_SPEED_REFRESH = 4, CPU_MEDIUM_SPEED_REFRESH = 3, CPU_FAST_SPEED_REFRESH = 2,
							CPU_MODIFIER_EASY = 3, CPU_MODIFIER_MEDIUM = 2, CPU_MODIFIER_HARD = 1};


	//Movement, angles & directions
	enum directions { NO_DIRECTION, UP, DOWN, LEFT, RIGHT };
	int ball_direction = RIGHT;
	int left_paddle_direction = NO_DIRECTION;
	int right_paddle_direction = NO_DIRECTION;

	bool right_paddle_moving = false;
	bool left_paddle_moving = false;

	int movement_angle = 0;
	int movement_angle_raw = 0;
	

	//Gamestates
	enum gamestates { IS_IN_MENU, IS_PAUSED, IS_IN_LOADSCREEN, IS_GAME_OVER, IS_PLAYING, PLAYER_HAS_WON };
	int gamestate = IS_IN_LOADSCREEN;


	//Gamemodes
	enum gamemodes { NO_GAMEMODE, GAMEMODE_INFINITE, GAMEMODE_TIMED, GAMEMODE_SCORE };
	int gamemode = NO_GAMEMODE;
	bool is_against_cpu = false;


	//Menu options
	enum menu_options { MENU_OPTION_PVP_INFINITE = 0, MENU_OPTION_PVP_TIMED = 5, MENU_OPTION_PVP_SCORE = 10,
						MENU_OPTION_CPU_INFINITE = 15, MENU_OPTION_CPU_TIMED = 20, MENU_OPTION_CPU_SCORE = 25};
	int menu_option = MENU_OPTION_PVP_INFINITE;


	//Menu states
	enum menu_states { MENU_PAGE_1, MENU_PAGE_2, MENU_TAB_1, MENU_TAB_2 };
	int menu_page = MENU_PAGE_1;
	int menu_tab = MENU_TAB_1;


	//Player type
	enum player { PLAYER_NULL, PLAYER_P1, PLAYER_P2, PLAYER_HUMAN, PLAYER_CPU };
	int winner = PLAYER_NULL;


	//Scores
	int player_1_points = 0;
	int player_2_points = 0;

	int scoreboard_score_p1 = 0;
	int scoreboard_score_p2 = 0;
	int scoreboard_score_player = 0;
	int scoreboard_score_cpu = 0;


	//Custom FX
	bool is_performing_effect = false;
	bool has_requested_effect = false;
	float time_effect_started = 0.0;
	float effect_time_in_seconds = 0.07;
	bool effect_has_finished_cycle = false;


	//Timers and runtime modifiers
	bool freeze_ball = true;
	float game_timer = 0;
	float global_game_timer = 0;
	int cpu_speed_modifier_check = 0;
	float cpu_speed_modifier = 2;


	//Audio checks
	bool has_performed_startup_sound = false;
};

