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
					controls.w = true;
					break;
				case SDLK_a:
					controls.a = true;
					break;
				case SDLK_s:
					controls.s = true;
					break;
				case SDLK_d:
					controls.d = true;
					break;
				}
			}

			if (SDL_KEYUP == event.type) {
				switch (event.key.keysym.sym) {
				case SDLK_w:
					controls.w = false;
					break;
				case SDLK_a:
					controls.a = false;
					break;
				case SDLK_s:
					controls.s = false;
					break;
				case SDLK_d:
					controls.d = false;
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

	canvas.drawAll();
	canvas.clear();
}
