#pragma once
#include <Engine/OGLGame.h>
#include <Engine/Sprite.h>
#include <Engine/Renderer.h>
#include "Pong/Definitions/enums/settings.h"
#include <memory>

/*
	// PONG REWORK 3 //

	---SCENE MANAGER
	Handle static foreground elements
*/

#ifndef SCENE_STAT_FOREGROUND_H
#define SCENE_STAT_FOREGROUND_H

class sceneStaticForeground
{
public:
	sceneStaticForeground();
	~sceneStaticForeground();

	void loadSprites(ASGE::Renderer* renderer);

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
	ASGE::Sprite* menu_overlay_score_box = nullptr; //in-game score box overlay

	ASGE::Sprite* menu_overlay_paused = nullptr; //in-game PAUSE screen

	ASGE::Sprite* menu_overlay_win_p1 = nullptr; //in-game WIN screen - P1
	ASGE::Sprite* menu_overlay_win_p2 = nullptr; //in-game WIN screen - P2
	ASGE::Sprite* menu_overlay_win_player = nullptr; //in-game WIN screen - PLAYER
	ASGE::Sprite* menu_overlay_win_cpu = nullptr; //in-game WIN screen - CPU
	ASGE::Sprite* menu_overlay_win_draw = nullptr; //in-game WIN screen - DRAW

	ASGE::Sprite* menu_overlay_score_p1 = nullptr; //in-game SCORE screen - P1
	ASGE::Sprite* menu_overlay_score_p2 = nullptr; //in-game SCORE screen - P2
	ASGE::Sprite* menu_overlay_score_player = nullptr; //in-game SCORE screen - PLAYER
	ASGE::Sprite* menu_overlay_score_cpu = nullptr; //in-game SCORE screen - CPU
};

#endif