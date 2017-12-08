#pragma once
#include "../enums/menuState.h"
#include "../enums/menuOption.h"

#ifndef ENUM_VALS_MENUSTATE_H
#define ENUM_VALS_MENUSTATE_H

/*
Define our menu data
*/
struct pongMenuState
{
	static menuState menu_page;
	static menuState menu_tab;

	static menuOption menu_option;
};

#endif