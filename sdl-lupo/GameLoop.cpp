#include "GameLoop.h"
#include <iostream>


void GameLoop::start()
{

	while (1) {
		SDL_Event event;


		if (SDL_PollEvent(&event)) {
			if (SDL_QUIT == event.type) break;

			if (SDL_KEYDOWN == event.type) {
				switch (event.key.keysym.sym) {
				case SDLK_w:
					cam.move(cam.getDelta());
					break;
				case SDLK_a:
					cam.adjustAngle(-0.1);
					break;
				case SDLK_s:
					vec2 v = cam.getDelta();
					cam.move({ -v.x, -v.y });
					break;
				case SDLK_d:
					cam.adjustAngle(0.1);
					break;
				}
			}

		}

		GameLoop::loop();
	}
}

void GameLoop::loop()
{
	vec2 pos = cam.getPos();
	vec2 delta = cam.getDelta();

	// draw ray
	canvas.drawLine(pos, {pos.x+delta.x*5, pos.y+delta.y*5});

	// draw actual rays
	vec2 ray = Raycaster::drawRays(cam.getPos(), cam.getAngle());
	canvas.drawLine(cam.getPos(), ray);

	canvas.drawAll();
	canvas.clear();

	GameLoop::frame++;
}
