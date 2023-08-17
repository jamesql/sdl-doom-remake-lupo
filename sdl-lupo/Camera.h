#pragma once

#include "types.h"
#include <SDL.h>

class Camera
{
private:
	vec2 pos;
	vec2 delta;
	float ang = 0;
public:
	Camera(vec2 initPos) : pos{ initPos }  {}
	Camera() { pos = { 0,0 }; }
	void move(vec2 movement);
	void setPos(vec2 newPos);
	vec2 getPos();
	void adjustAngle(float dAng);
	vec2 getDelta();
};

