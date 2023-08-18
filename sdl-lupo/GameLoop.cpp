#include "GameLoop.h"
#include <iostream>
#include "Util.h"

#define R 0.0174533

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

	GameLoop::drawTestMap();

	// draw ray
	canvas.drawLine(pos, {pos.x+delta.x*5, pos.y+delta.y*5});

	// draw actual rays
	float ang = cam.getAngle();
	vec2 camPos = cam.getPos();

	float startAngle = ang - 30 * R;
	float endAngle = ang + 29 * R;

	float curAng;
	// draw 3d walls
	int r = 0;

	for (curAng = startAngle; curAng <= endAngle; curAng += R) {
		RaycastData ray = Raycaster::drawRays(camPos, Util::fixAngRad(curAng), ang);
		printf(" %f \n", ray.dis);
		int lineH = (TempMap::cSize * 320) / ray.dis;
		if (lineH > 320) lineH = 320;
		int lineOff = 160 - lineH/2;
		for (int i = 0; i < 8; i++) {
			canvas.drawLine({ r * 8.f + 530 + i, lineH + 0.0f + lineOff }, { r * 8.f + 530 + i, lineOff + 0.0f });
		}
		canvas.drawLine(camPos, ray.castEnd);
		r++;
	}

	canvas.drawAll();
	canvas.clear();

	GameLoop::frame++;
}

// drawMap() 

void GameLoop::drawTestMap() {
	int x, y, xo, yo;
	int r=0, g=0, b = 0;
	for (y = 0; y < TempMap::mapY; y++) {
		for (x = 0; x < TempMap::mapX; x++) {
			r = 0, g = 0, b = 0;
			if (TempMap::map[y * TempMap::mapX + x] == 1) {
				r = 255;
			}
			else b = 255;

			xo = x * TempMap::cSize;
			yo = y * TempMap::cSize;

			SDL_Rect rec = {xo, yo, 64, 64};

			canvas.addRect(rec, r, g, b);
		}
	}
}
