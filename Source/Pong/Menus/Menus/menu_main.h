#pragma once
#include <Engine/OGLGame.h>
#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include "Pong/Definitions/enums/gamemode.h"
#include "Pong/Definitions/enums/gamestate.h"
#include "Pong/Definitions/enums/direction.h"
#include "Pong/Definitions/enums/settings.h"
#include "Pong/Definitions/enums/menuState.h"
#include "Pong/Definitions/enums/menuOption.h"
#include "Pong/Definitions/enum_values/gamestate.h"
#include "Pong/Definitions/enum_values/direction.h"
#include "Pong/Definitions/enum_values/gamemode.h"
#include "Pong/Definitions/GameVars/scores.h"
#include "Pong/Definitions/GameVars/core.h"
#include "Pong/Interactive/Objects/ui_sfx.h"
#include "Pong/Scene Manager/scene.h"
#include "PongPAK.h"

/*
	// PONG REWORK 3 //

	---INTERACTIVE/MENUS
	Main Menu.
*/

#ifndef MENU_MAIN_H
#define MENU_MAIN_H

class pongMenuMain
{
public:
	pongMenuMain();

	void handleInputs();
	void handleRender();

	//Menu Option & State
	menuOption current_menu_option = menuOption::MENU_OPTION_PVP_INFINITE;
	menuState current_menu_page = menuState::MENU_PAGE_1;
	menuState current_menu_tab = menuState::MENU_TAB_1;
private:
	GameVars_Core pong_vars;
	pongUISFX sound_fx;
	GameVars_Scores pong_points;
	gamestateValues gamestate;
	directionValues direction;
	gamemodeValues gamemode;
	PongPAK file_handler;

	sceneManager scenemanager;
	sceneBackground scenemanager_background;
	sceneDynamicForeground scenemanger_foreground_dynamic;
	sceneForeground scenemanager_foreground;
	sceneStaticForeground scenemanager_foreground_static;
};

#endif