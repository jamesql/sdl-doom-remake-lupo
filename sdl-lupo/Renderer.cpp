#include "Renderer.h"

	
	void Renderer::addPixel(vec2 point) {
		pixels.push_back(point);
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

	}

	void Renderer::fillRect(SDL_Rect* rec, int r, int g, int b) {
		SDL_SetRenderDrawColor(Renderer::m_sdlApp.r, r, g, b, 255);
		SDL_RenderFillRect(Renderer::m_sdlApp.r, rec);
	}
