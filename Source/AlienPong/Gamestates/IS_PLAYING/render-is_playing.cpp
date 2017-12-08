#include "main-is_playing.h"

/*
Render everything for gamestate
*/
void gamestateIsPlaying::renderState(const ASGE::GameTime & us, ASGE::Renderer* renderer)
{
	if (pong_gamemode.current_gamemode == gamemode::GAMEMODE_INFINITE)
		renderer->renderSprite(*menu_overlay_mode_regular); //MODE OVERLAY: regular
	else if (pong_gamemode.current_gamemode == gamemode::GAMEMODE_SCORE)
		renderer->renderSprite(*menu_overlay_mode_score); //MODE OVERLAY: score
	else if (pong_gamemode.current_gamemode == gamemode::GAMEMODE_TIMED)
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
	if (pong_gamemode.is_against_cpu)
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText("Player", (int)settings::GAMEWINDOW_MAX_WIDTH - 50 - 175, (int)settings::GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText((std::to_string(pong_scores.p1)).c_str(), (int)settings::GAMEWINDOW_MAX_WIDTH - 80, (int)settings::GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText("CPU", (int)settings::GAMEWINDOW_MAX_WIDTH - 50 - 175, (int)settings::GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText((std::to_string(pong_scores.p2)).c_str(), (int)settings::GAMEWINDOW_MAX_WIDTH - 80, (int)settings::GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
	}
	else
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText("Player 1", (int)settings::GAMEWINDOW_MAX_WIDTH - 50 - 175, (int)settings::GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText((std::to_string(pong_scores.p1)).c_str(), (int)settings::GAMEWINDOW_MAX_WIDTH - 80, (int)settings::GAMEWINDOW_MAX_HEIGHT - 90, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText("Player 2", (int)settings::GAMEWINDOW_MAX_WIDTH - 50 - 175, (int)settings::GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
		renderer->renderText((std::to_string(pong_scores.p2)).c_str(), (int)settings::GAMEWINDOW_MAX_WIDTH - 80, (int)settings::GAMEWINDOW_MAX_HEIGHT - 54, 0.4, ASGE::COLOURS::WHITE);
	}

	//Render Timer
	if (pong_gamemode.current_gamemode == gamemode::GAMEMODE_TIMED)
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText((std::to_string(int((60 - pong_variables.game_timer) + 0.5)) + " Seconds Remaining").c_str(), 50, (int)settings::GAMEWINDOW_MAX_HEIGHT - 50, 0.4, ASGE::COLOURS::WHITE);
	}
	if (pong_gamemode.current_gamemode == gamemode::GAMEMODE_CRAZY)
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText((std::to_string(int((pong_variables.game_timer) + 0.5)) + " Seconds Played").c_str(), 50, (int)settings::GAMEWINDOW_MAX_HEIGHT - 50, 0.4, ASGE::COLOURS::WHITE);
	}

	//Debug output
	if (pongGamestate::show_debug_text)
	{
		renderer->setFont(GameFont::fonts[0]->id);
		renderer->renderText(("Ball Direction: " + std::to_string((int)pong_directions.ball_direction)).c_str(), 150, 200, 0.5, ASGE::COLOURS::WHITE);
		renderer->renderText(("Movement Angle: " + std::to_string((int)pong_directions.movement_angle)).c_str(), 150, 250, 0.5, ASGE::COLOURS::WHITE);
		renderer->renderText(("Ball XPos: " + std::to_string((int)ball1->xPos())).c_str(), 150, 300, 0.5, ASGE::COLOURS::WHITE);
		renderer->renderText(("Ball YPos: " + std::to_string((int)ball1->yPos())).c_str(), 150, 350, 0.5, ASGE::COLOURS::WHITE);
		renderer->renderText(("World Speed: " + std::to_string((int)settings::DEFAULT_SPEED)).c_str(), 150, 400, 0.5, ASGE::COLOURS::WHITE);
		renderer->renderText(("Ball Calc'd Speed: " + std::to_string(((int)settings::DEFAULT_SPEED - pong_directions.movement_angle_raw) * (us.delta_time.count() / 1000.f))).c_str(), 150, 450, 0.5, ASGE::COLOURS::WHITE);
		renderer->renderText(("Frame Time: " + std::to_string((float)(us.delta_time.count() / 1000.f))).c_str(), 150, 500, 0.5, ASGE::COLOURS::WHITE);
	}
}