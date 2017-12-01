#pragma once
#include <memory>
#include <Engine/OGLGame.h>

/*
	// PONG REWORK 3 //

	---INTERACTIVE
	Handle our in-game ball.
*/

#ifndef INT_BALL_H
#define INT_BALL_H

class pongBall
{
public:
	pongBall();
	void testRender(std::shared_ptr<ASGE::Renderer> renderer);
	int testVar;
};

#endif