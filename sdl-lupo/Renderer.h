#pragma once

#include <SDL.h>
#include "e_config.h"
#include "types.h"
#include <vector>

class Renderer {
private: 
	application m_sdlApp;
	std::vector<vec2> pixels;

public:
	Renderer(application& app) : m_sdlApp{ app } {}
	Renderer() {}
	void addPixel(vec2 point);
	void addPixel(float x, float y);
	void drawAll();
	void clear();
	void drawLine(vec2 firstPoint, vec2 secondPoint);
	void fillRect(SDL_Rect* rec, int r, int g, int b);
	void drawTriangle(vec2 firstPoint, vec2 secondPoint, vec2 thirdPoint);

};