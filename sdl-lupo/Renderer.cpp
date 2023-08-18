#include "Renderer.h"

	
	void Renderer::addPixel(vec2 point) {
		pixels.push_back(point);
	}

	void Renderer::addPixel(float x, float y) {
		pixels.push_back({ x, y });
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

		// draw v lines - todo?

		SDL_SetRenderDrawColor(Renderer::m_sdlApp.r, 255, 255, 255, 255);
		for (auto& point : pixels) {
			SDL_RenderDrawPointF(Renderer::m_sdlApp.r, point.x, point.y);
		}


		SDL_RenderPresent(Renderer::m_sdlApp.r);
	}

	void Renderer::clear() {
		pixels.clear();
	}

	void Renderer::drawLine(vec2 firstPoint, vec2 secondPoint) {
		float dx = secondPoint.x - firstPoint.x;
		float dy = secondPoint.y - firstPoint.y;

		float len = sqrt(dx * dx + dy * dy);

		float ang = atan2(dy, dx);

		for (float i = 0; i < len; i++) {
			addPixel(firstPoint.x + cos(ang) * i, firstPoint.y + sin(ang) * i );
		}
	}

	

	void Renderer::drawTriangle(vec2 firstPoint, vec2 secondPoint, vec2 thirdPoint) {
		drawLine(firstPoint, secondPoint);
		drawLine(secondPoint, thirdPoint);
		drawLine(thirdPoint, firstPoint);
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
