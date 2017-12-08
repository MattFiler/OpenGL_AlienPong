#include "../structs.h"

#ifndef DEFINE_ALIENPONG_MENUSTATE
#define DEFINE_ALIENPONG_MENUSTATE

/*
Set all pongMenuState values
*/

//Menu pages and tabs
menuState pongMenuState::menu_page = menuState::MENU_PAGE_1;
menuState pongMenuState::menu_tab = menuState::MENU_TAB_1;

//Menu selections
menuOption pongMenuState::menu_option = menuOption::MENU_OPTION_PVP_INFINITE;

#endif