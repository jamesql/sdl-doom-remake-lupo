#include "Renderer.h"
#include <SDL.h>
	
	void Renderer::addPixel(Pixel p) {
		pixels.push_back(p);
	}

	void Renderer::addPixel(float x, float y, mColor col) {
		pixels.push_back({ { x, y }, col});
	}

	void Renderer::drawAll() {
		SDL_SetRenderDrawColor(Renderer::m_sdlApp.r, 0, 0, 0, 255);
		SDL_RenderClear(Renderer::m_sdlApp.r);

		// draw rects
		for (auto& rec : rects)
		{
			SDL_SetRenderDrawColor(Renderer::m_sdlApp.r, rec.r, rec.g, rec.b, rec.a);
			SDL_RenderFillRect(Renderer::m_sdlApp.r, &rec.rec);
		}

		for (auto& point : pixels) {
			mColor c = point.col;
			SDL_SetRenderDrawColor(Renderer::m_sdlApp.r, c.r, c.g, c.b, c.a);
			SDL_RenderDrawPointF(Renderer::m_sdlApp.r, point.loc.x, point.loc.y);
		}


		SDL_RenderPresent(Renderer::m_sdlApp.r);
	}

	void Renderer::clear() {
		pixels.clear();
		rects.clear();
	}

	void Renderer::drawLine(vec2 firstPoint, vec2 secondPoint, mColor c) {
		float dx = secondPoint.x - firstPoint.x;
		float dy = secondPoint.y - firstPoint.y;

		float len = sqrt(dx * dx + dy * dy);

		float ang = atan2(dy, dx);

		for (float i = 0; i < len; i++) {
			addPixel(firstPoint.x + cos(ang) * i, firstPoint.y + sin(ang) * i, c);
		}
	}

	

	void Renderer::drawTriangle(vec2 firstPoint, vec2 secondPoint, vec2 thirdPoint) {
		drawLine(firstPoint, secondPoint, { 255, 0, 0, 255 });
		drawLine(secondPoint, thirdPoint, { 255, 0, 0, 255 });
		drawLine(thirdPoint, firstPoint, {255, 0, 0, 255});
	}

	void Renderer::drawWideLine(vec2 firstPoint, vec2 secondPoint, int width)
	{
		//SDL_RenderDrawLines()
	}

	application Renderer::getApp()
	{
		return this->m_sdlApp;
	}

	void Renderer::addRect(SDL_Rect rec, int r, int g, int b) {
		rects.push_back(Rectangle{rec,r,g,b,255});
	}
