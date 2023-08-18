#include <stdio.h>
#include <cstdlib>
#include "e_config.h"
#include "types.h"
#include <vector>
#include "Renderer.h"
#include <numeric>
#include "GameLoop.h"
#include "../../../../Downloads/SDL2-devel-2.28.2-VC/SDL2-2.28.2/include/SDL.h"

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