#pragma once

#include <string>

#include <Engine/OGLGame.h>
#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>
#include <Engine\Renderer.h>

#include "Pong/Scene Manager/scene.h"
#include "Pong/Definitions/GameVars.h"
#include "Pong/Definitions/enum_values.h"
#include "Pong/Definitions/enums.h"
#include "GameFont.h"
#include "Pong/Menus/menus.h"
#include "Pong/Animation/vhs_fx.h"
#include "PongPAK.h"
#include "Pong/Interactive/interactive.h"

struct GameFont;

/*

//////// PONG - Created by Matt Filer ////////
//////////////// GAME HEADER /////////////////

*/

#ifndef GAME_H
#define GAME_H

class Pong :
	public ASGE::OGLGame
{
public:
	Pong();
	~Pong();
	virtual bool init() override;

private:
	gamestateValues gamestate;
	pongUISFX sound_fx;
	GameVars_FX pong_fx;
	GameVars_Core pong_vars;

	sceneManager scenemanager;
	sceneBackground scenemanager_background;
	sceneDynamicForeground scenemanger_foreground_dynamic;
	sceneForeground scenemanager_foreground;
	sceneStaticForeground scenemanager_foreground_static;
	GameVars_Scores pong_points;

	pongPaddles paddle;

	directionValues direction;
	gamemodeValues gamemode;
	playerValues player;

	PongPAK file_handler;

	pongMenuMain main_menu;

	pongVHS vhs_fx;

	void keyHandler(ASGE::SharedEventData data);
	virtual void update(const ASGE::GameTime &) override;
	virtual void render(const ASGE::GameTime &) override;

	bool isTouchingPaddle(const ASGE::Sprite* sprite, float x, float y, std::string spriteName);
	int calculateReturnAngle(const ASGE::Sprite* paddle, bool include_reverses) const;
	void handleWin(std::string winner_name);
	void resetGame();
	void loadAssets();
	bool hasHitEdge(std::string edgeName) const;

	bool exit = false;                  /**< Exit boolean. If true the game loop will exit. */
	int  key_callback_id = -1;	        /**< Key Input Callback ID. */
};

#endif