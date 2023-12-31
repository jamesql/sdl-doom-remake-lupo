#pragma once

#include <SDL.h>

struct application {
	SDL_Window* w;
	SDL_Renderer* r;
	SDL_Event event;
};

struct vec2 {
    float x, y;

    vec2 operator+(vec2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
};

struct vec3 {
    float x, y, z;
};

struct mColor {
    int r, g, b, a;
};

struct Pixel {
    vec2 loc;
    mColor col;
};

struct Point {
	constexpr Point(float x, float y) : x { x }, y { y } {}

	float x;
	float y;

    bool operator<(const Point& p) const
    {
        if (x == p.x)
        {
            return y < p.y;
        }
        return x < p.x;
    }

    bool operator==(Point& p) {
        return x == p.x && y == p.y;
    }
};

struct Vertex : Point {
    constexpr Vertex(float x, float y) : Point{ x, y } {}
    constexpr Vertex(int x, int y) : Point {static_cast<float>(x), static_cast<float>(y)} {}
};

struct Location : Point
{
    constexpr Location(float x, float y, float z) : Point{ x, y }, z{ z } {}

    float z;
};

struct Line
{
    vec2 firstPoint;
    vec2 secondPoint;
    int width;
};

struct Rectangle {
    SDL_Rect rec;
    int r;
    int g;
    int b;
    int a;
};

struct RaycastData {
    vec2 castEnd;
    float dis;
    bool shaded;
};