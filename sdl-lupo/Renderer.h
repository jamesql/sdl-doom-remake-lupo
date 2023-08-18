#pragma once

#include <SDL.h>
#include "e_config.h"
#include "types.h"
#include <vector>

class Renderer {
private: 
	application m_sdlApp;
	std::vector<Pixel> pixels;
	std::vector<Rectangle> rects;
	std::vector<Line> lines;

public:
	Renderer(application& app) : m_sdlApp{ app } {}
	Renderer() {}
	void addPixel(Pixel point);
	void addPixel(float x, float y, mColor col);
	void drawAll();
	void clear();
	void drawLine(vec2 firstPoint, vec2 secondPoint, mColor c);
	void addRect(SDL_Rect rec, int r, int g, int b);
	void drawTriangle(vec2 firstPoint, vec2 secondPoint, vec2 thirdPoint);
	void drawWideLine(vec2 firstPoint, vec2 secondPoint, int width);
	application getApp();

};