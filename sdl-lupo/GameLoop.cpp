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
					cam.move(cam.getDelta());
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
	canvas.drawLine({ 200,200 }, { 500,500 });

	canvas.drawTriangle({ 150,30 }, { 300,200 }, {450, 30});
	canvas.drawTriangle({ 300,90 }, { 600,500 }, { 900, 20 });

	canvas.drawAll();
	canvas.clear();

	GameLoop::frame++;
}
