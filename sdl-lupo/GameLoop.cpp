#include "GameLoop.h"
#include <iostream>

float randomFloat()
{
	return (float)(rand()) / (float)(rand());
}

void GameLoop::start()
{

	while (1) {
		SDL_Event event;
		for (int i = 0; i < 100; i++) {
			canvas.addPixel({ 300.f + i, 400.f + i });
		}

		GameLoop::loop();

		if (SDL_PollEvent(&event)) {
			if (SDL_QUIT == event.type) break;
		}
	}
}

void GameLoop::loop()
{
	canvas.drawAll();
	canvas.clear();
}
