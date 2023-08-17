#include <stdio.h>
#include <SDL.h>
#include <cstdlib>
#include "e_config.h"
#include "types.h"
#include <vector>
#include "Renderer.h"
#include <numeric>
#include "GameLoop.h"

struct connection {
    int x, y;
};

std::vector<SDL_FPoint> points;

application m_sdlApplication = {
    nullptr,
    nullptr,
    0
};

void rotate(vec3& point, float x = 1, float y = 1, float z = 1) {
    float rad = 0;

    rad = x;
    point.y = cos(rad) * point.y - sin(rad) * point.z;
    point.z = sin(rad) * point.y + cos(rad) * point.z;

    rad = y;
    point.x = cos(rad) * point.x + sin(rad) * point.z;
    point.z = -sin(rad) * point.x + cos(rad) * point.z;

    rad = z;
    point.x = cos(rad) * point.x - sin(rad) * point.y;
    point.y = sin(rad) * point.x + cos(rad) * point.y;
}

void pixel(float x, float y) {
    points.push_back({x, y});
}

void show() {
    SDL_SetRenderDrawColor(m_sdlApplication.r, 0, 0, 0, 255);
    SDL_RenderClear(m_sdlApplication.r);

    SDL_SetRenderDrawColor(m_sdlApplication.r, 255, 255, 255, 255);
    for (auto& point : points) {
        SDL_RenderDrawPointF(m_sdlApplication.r, point.x, point.y);
    }

    SDL_RenderPresent(m_sdlApplication.r);
}

void clear() {
    points.clear();
}

void line(SDL_FPoint firstPoint, SDL_FPoint secondPoint) {
    float dx = secondPoint.x - firstPoint.x;
    float dy = secondPoint.y - firstPoint.y;

    float len = sqrt(dx * dx + dy * dy);

    float ang = atan2(dy, dx);

    for (float i = 0; i < len; i++) {
        pixel(firstPoint.x + cos(ang) * i, firstPoint.y + sin(ang) * i);
    }
}

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);

    m_sdlApplication.w = SDL_CreateWindow("DEMO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    m_sdlApplication.r = SDL_CreateRenderer(m_sdlApplication.w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (NULL == m_sdlApplication.w)
    {
        printf("Could not create window\n");
        SDL_GetError();
        return 1;
    }

    GameLoop gameLoop(m_sdlApplication);

    gameLoop.start();

    SDL_DestroyWindow(m_sdlApplication.w);
    SDL_DestroyRenderer(m_sdlApplication.r);
    SDL_Quit();

    return EXIT_SUCCESS;
}