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

	bool exit = false;                 /**< Exit boolean. If true the game loop will exit. */

	int  key_callback_id = -1;	        /**< Key Input Callback ID. */

	ASGE::Sprite* paddle1 = nullptr;  /**< Sprite Object. Paddle 1. */
	ASGE::Sprite* paddle2 = nullptr;  /**< Sprite Object. Paddle 2. */
	ASGE::Sprite* ball1 = nullptr;  /**< Sprite Object. Ball. */
};

