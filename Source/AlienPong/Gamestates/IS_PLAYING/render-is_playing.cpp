#include "main-is_playing.h"

/*
Render everything for gamestate
*/
void gamestateIsPlaying::renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer)
{
	if (pongGamemodes::current_gamemode == gamemode::GAMEMODE_INFINITE)
		renderer->renderSprite(*menu_overlay_mode_regular); //MODE OVERLAY: regular
	if (pongGamemodes::current_gamemode == gamemode::GAMEMODE_SCORE)
		renderer->renderSprite(*menu_overlay_mode_score); //MODE OVERLAY: score
	if (pongGamemodes::current_gamemode == gamemode::GAMEMODE_TIMED)
		renderer->renderSprite(*menu_overlay_mode_timed); //MODE OVERLAY: timed

	//Render score box
	renderer->renderSprite(*menu_overlay_score_box);

	//Render paddle 1
	renderer->renderSprite(*paddle1);

	//Render paddle 2
	renderer->renderSprite(*paddle2);

	//Render ball 1
	renderer->renderSprite(*ball1);

	//Render Points
	if (pongGamemodes::is_against_cpu)
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText("Player", (int)settings::GAMEWINDOW_MAX_WIDTH - 50 - 175, (int)settings::GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText((std::to_string(pongScores::p1)).c_str(), (int)settings::GAMEWINDOW_MAX_WIDTH - 80, (int)settings::GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText("CPU", (int)settings::GAMEWINDOW_MAX_WIDTH - 50 - 175, (int)settings::GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText((std::to_string(pongScores::p2)).c_str(), (int)settings::GAMEWINDOW_MAX_WIDTH - 80, (int)settings::GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
	}
	else
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText("Player 1", (int)settings::GAMEWINDOW_MAX_WIDTH - 50 - 175, (int)settings::GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText((std::to_string(pongScores::p1)).c_str(), (int)settings::GAMEWINDOW_MAX_WIDTH - 80, (int)settings::GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText("Player 2", (int)settings::GAMEWINDOW_MAX_WIDTH - 50 - 175, (int)settings::GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText((std::to_string(pongScores::p2)).c_str(), (int)settings::GAMEWINDOW_MAX_WIDTH - 80, (int)settings::GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
	}

	//Render Timer
	if (pongGamemodes::current_gamemode == gamemode::GAMEMODE_TIMED)
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText((std::to_string(int((60 - pongVariables::game_timer) + 0.5)) + " Seconds Remaining").c_str(), 50, (int)settings::GAMEWINDOW_MAX_HEIGHT - 50, 0.4, ASGE::COLOURS::WHITE);
	}
}