#pragma once

#include "types.h"
#include <SDL.h>

class Camera
{
private:
	float ang = 1.5708;
	vec2 pos;
	// todo: init delta on camera init - default to 90 degs
	vec2 delta;

public:
	Camera(vec2 initPos) : pos{ initPos }  {}
	Camera() { pos = { 640,350 }; }
	void move(vec2 movement);
	void setPos(vec2 newPos);
	vec2 getPos();
	void adjustAngle(float dAng);
	vec2 getDelta();
	float getAngle();
};

