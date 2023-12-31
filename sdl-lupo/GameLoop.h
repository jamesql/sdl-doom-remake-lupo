#pragma once

#include <SDL.h>
#include "Renderer.h"
#include "Camera.h"
#include "Raycaster.h"

class GameLoop
{
protected:
	int frame = 0;
	Renderer canvas;
	Camera cam;
	application m_sdlApp;
	
public:
	void start();
	void loop();
	void drawTestMap();

	GameLoop(application& app) : m_sdlApp{ app } {
		this->canvas = Renderer(app);
	}


};

