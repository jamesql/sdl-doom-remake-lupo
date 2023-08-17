#include "Camera.h"

void Camera::move(vec2 movement)
{
	this->pos = this->pos + movement;
}

void Camera::setPos(vec2 newPos)
{
	this->pos = newPos;
}

vec2 Camera::getPos()
{
	return this->pos;
}

void Camera::adjustAngle(float dAng)
{
	// Adjust angle
	this->ang += dAng;
	// Normalize angle
	if (this->ang < 0) this->ang += 2 * M_PI;
	if (this->ang > 2 * M_PI) this->ang -= 2 * M_PI;

	// Adjust deltas
	this->delta.x = cos(this->ang) * 5;
	this->delta.y = sin(this->ang) * 5;
}

vec2 Camera::getDelta() {
	return this->delta;
}

float Camera::getAngle()
{
	return this->ang;
}
