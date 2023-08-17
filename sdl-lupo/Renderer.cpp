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

	void Renderer::fillRect(SDL_Rect* rec, int r, int g, int b) {
		SDL_SetRenderDrawColor(Renderer::m_sdlApp.r, r, g, b, 255);
		SDL_RenderFillRect(Renderer::m_sdlApp.r, rec);
	}
