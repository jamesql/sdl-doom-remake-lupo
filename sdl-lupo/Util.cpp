#include "Util.h"

float Util::degToRad(int a)
{
	return 0.0f;
}

int Util::fixAng(int a) { 
	if (a > 359) a -= 360; 
	if (a < 0) a += 360; 
	return a; 
}

float Util::distance(vec2 firstPoint, vec2 secondPoint, int ang)
{
	return cos(Util::degToRad(ang)) * (secondPoint.x - firstPoint.x) - sin(Util::degToRad(ang)) * (secondPoint.y-firstPoint.y);
}
