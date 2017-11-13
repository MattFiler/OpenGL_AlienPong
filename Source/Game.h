#pragma once
#include <string>
#include <Engine/OGLGame.h>

struct GameFont;

/**
*  Pong. An OpenGL Game based on ASGE.
*/

class Pong:
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

	bool exit = false;                  /**< Exit boolean. If true the game loop will exit. */

	int  key_callback_id = -1;	        /**< Key Input Callback ID. */

	ASGE::Sprite* paddle1 = nullptr;    /**< Sprite Object. Paddle 1. */
	ASGE::Sprite* paddle2 = nullptr;    /**< Sprite Object. Paddle 2. */
	ASGE::Sprite* ball1 = nullptr;      /**< Sprite Object. Ball. */
	ASGE::Sprite* menuTitle = nullptr;  /**< Sprite Object. Menu text. */

    //Paddle and ball sizes
	int paddle_height = 150;
	int paddle_width = 10;
	int ball_size = 10;

	//Movement direction: left = 0, right = 1.
	int movement_direction = 1;
	int movement_angle = 0;
	int movement_angle_raw = 0;

	//Angle/speed settings
	int angle_variant = 140;
	int angle_base = 25;
	int speed_base = 300;

	//Score
	int player_1_points = 0;
	int player_2_points = 0;

	//Menu
	bool is_in_menu = true;
	int menu_option = 0;

	//Gamestates
	bool gamestate_freeplay = false;
	bool gamestate_timedgameplay = false;
	bool gamestate_firsttofive = false;
};

