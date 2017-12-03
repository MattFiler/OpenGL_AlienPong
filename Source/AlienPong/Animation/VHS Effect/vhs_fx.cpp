#include "vhs_fx.h"

/*
	Define default values
*/
pongVHS::pongVHS()
{
	pongfx_state = animationState::IS_IDLE;
	time_started = 0;
	time_in_seconds = 0.07;
}


/*
	Render FX if requested (and not already performing)
*/
void pongVHS::renderFX() {
	std::shared_ptr<ASGE::Renderer> renderer;

	if (pongfx_state == animationState::HAS_BEEN_REQUESTED || //Has requested effect?
		((time_started + time_in_seconds) < pong_vars.global_game_timer && pongfx_state == animationState::IS_PERFORMING) //Is in time range for performing effect?
		)
	{
		if (pongfx_state != animationState::HAS_FINISHED)
		{
			if (pongfx_state == animationState::HAS_BEEN_REQUESTED)
			{
				time_started = pong_vars.global_game_timer; //Log start time (if not already performing)
			}
			pongfx_state == animationState::IS_IDLE;

			//Run animation
			if (pong_vars.global_game_timer - time_started < 0.01)
			{
				renderer->renderSprite(*pong_sprite_static.menu_background_s00);
				pongfx_state == animationState::IS_PERFORMING;
			}
			if (pong_vars.global_game_timer - time_started < 0.03 && pong_vars.global_game_timer - time_started >= 0.01)
			{
				renderer->renderSprite(*pong_sprite_static.menu_background_s01);
				pongfx_state == animationState::IS_PERFORMING;
			}
			if (pong_vars.global_game_timer - time_started < 0.04 && pong_vars.global_game_timer - time_started >= 0.03)
			{
				renderer->renderSprite(*pong_sprite_static.menu_background_s02);
				pongfx_state == animationState::IS_PERFORMING;
			}
			if (pong_vars.global_game_timer - time_started < 0.06 && pong_vars.global_game_timer - time_started >= 0.04)
			{
				renderer->renderSprite(*pong_sprite_static.menu_background_s03);
				pongfx_state == animationState::IS_PERFORMING;
			}
			if (pong_vars.global_game_timer - time_started < 0.07 && pong_vars.global_game_timer - time_started >= 0.06)
			{
				renderer->renderSprite(*pong_sprite_static.menu_background_s04);
				pongfx_state == animationState::HAS_FINISHED;
			}
		}
	}
}