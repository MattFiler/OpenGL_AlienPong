#pragma once

#ifndef ENUMS_MENUOPTION_H
#define ENUMS_MENUOPTION_H

/*
	Define our menu options. 
*/
enum class menuOption : int
{
	MENU_OPTION_PVP_INFINITE = 0, //Page 2, Tab 1 - Infinite Player VS Player
	MENU_OPTION_PVP_TIMED = 5, //Page 2, Tab 1 - Timed Player VS Player
	MENU_OPTION_PVP_SCORE = 10, //Page 2, Tab 1 - First to 5 Player VS Player
	MENU_OPTION_PVP_CRAZY = 15,

	MENU_OPTION_CPU_INFINITE = 20, //Page 2, Tab 2 - Infinite CPU VS Player
	MENU_OPTION_CPU_TIMED = 25, //Page 2, Tab 2 - Timed CPU VS Player
	MENU_OPTION_CPU_SCORE = 30, //Page 2, Tab 2 - First to 5 CPU VS Player
	MENU_OPTION_CPU_CRAZY = 35
};

#endif