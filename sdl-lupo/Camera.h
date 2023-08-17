#pragma once

#include "types.h"
#include <SDL.h>

class Camera
{
private:
	vec3 pos;
public:
	Camera(vec3 initPos) : pos{ initPos }  {}
	Camera() { pos = { 0,0,0 }; }
};

