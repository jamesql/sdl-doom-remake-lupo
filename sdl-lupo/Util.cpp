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

float Util::fixAngRad(float ang) {
	if (ang > 6.26573) ang -= 6.28319;
	if (ang < 0) ang += 6.28319;
	return ang;

}

float Util::distance(vec2 firstPoint, vec2 secondPoint, int ang)
{
	return sqrt( (secondPoint.x - firstPoint.x) * (secondPoint.x - firstPoint.x) + (secondPoint.y-firstPoint.y) * (secondPoint.y - firstPoint.y));
}
