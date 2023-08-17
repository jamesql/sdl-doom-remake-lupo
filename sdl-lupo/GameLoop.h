#pragma once

#include <SDL.h>
#include "Renderer.h"

class GameLoop
{
private:
	int frame = 0;
	Renderer canvas;
	application m_sdlApp;
	
public:
	void start();
	void loop();

	GameLoop(application& app) : m_sdlApp{ app } {
		this->canvas = Renderer(app);
	}


};

