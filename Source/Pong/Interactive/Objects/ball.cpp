#include "ball.h"

pongBall::pongBall()
{
	testVar = 0;
}

void pongBall::testRender(std::shared_ptr<ASGE::Renderer> renderer) {
	//renderer->renderSprite();
	testVar = 1;
}