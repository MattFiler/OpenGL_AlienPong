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
	Implement point line checker to account for frame lag
	Implement new menu system
		Jixellation.ttf font import
		Scoreboard
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

	// Inherited via OGLGame
	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;
	bool isTouchingPaddle(const ASGE::Sprite* sprite, float x, float y, std::string spriteName) const;
	bool hasHitEdge(std::string edgeName) const;
	int calculateReturnAngle(const ASGE::Sprite* paddle, bool include_reverses) const;
	void handleWin(std::string winner);

	bool exit = false;                  /**< Exit boolean. If true the game loop will exit. */

	int  key_callback_id = -1;	        /**< Key Input Callback ID. */

	ASGE::Sprite* paddle1 = nullptr;    /**< Sprite Object. Paddle 1. */
	ASGE::Sprite* paddle2 = nullptr;    /**< Sprite Object. Paddle 2. */
	ASGE::Sprite* ball1 = nullptr;      /**< Sprite Object. Ball. */
	
	//Menu backgrounds and overlays
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

	//Paddle and ball sizes
	int paddle_height = 150;
	int paddle_width = 10;
	int ball_size = 10;

	//Paddle controls
	bool right_paddle_moving = false;
	bool right_paddle_moving_up = false;
	bool left_paddle_moving = false;
	bool left_paddle_moving_up = false;

	//Movement direction: left = 0, right = 1.
	int movement_direction = 1;
	int movement_angle = 0;
	int movement_angle_raw = 0;

	//Angle/speed settings
	int angle_variant = 140;
	int angle_base = 25;
	int speed_base = 600; 

	//Score
	int player_1_points = 0;
	int player_2_points = 0;

	//Menu
	bool is_in_menu = true;
	int menu_option = 0;
	bool player_has_won = false;
	int winner_id = 0;
	bool is_in_loadscreen = true;
	bool swap_tabs = false;
	bool showing_first_menu = true;

	//Custom FX
	bool is_performing_effect = false;
	bool has_requested_effect = false;
	float time_effect_started = 0.0;
	float effect_time_in_seconds = 0.07;
	bool effect_has_finished_cycle = false;

	//Gamestates
	bool gamestate_freeplay = false;
	bool gamestate_timedgameplay = false;
	bool gamestate_firsttofive = false;
	bool gamestate_vscpu = false;
	int cpu_speed_modifier = 2;
	int cpu_speed_modifier_check = 0;
	int cpu_speed_refresh_rate = 3;
	bool game_over = false;
	float game_timer = 0;
	float global_game_timer = 0;
	bool is_paused = false;

	//Audio checks
	bool has_performed_startup_sound = false;

	//Scores
	int scoreboard_score_p1 = 0;
	int scoreboard_score_p2 = 0;
	int scoreboard_score_player = 0;
	int scoreboard_score_cpu = 0;
};

