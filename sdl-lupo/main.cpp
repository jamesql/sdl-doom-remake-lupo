#include <stdio.h>
#include <SDL.h>
#include <cstdlib>
#include "e_config.h"
#include "types.h"
#include <vector>



int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* w = SDL_CreateWindow("DEMO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    application m_sdlApplication = {
        w,
        nullptr,
        0
    };

    const std::vector< SDL_Vertex > verts =
    {
        { SDL_FPoint{ 400, 150 }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ 200, 450 }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
        { SDL_FPoint{ 600, 450 }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
    };

    m_sdlApplication.r = SDL_CreateRenderer(m_sdlApplication.w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(m_sdlApplication.r, 0, 0, 0, 255);
    SDL_RenderClear(m_sdlApplication.r);
    SDL_RenderGeometry(m_sdlApplication.r, nullptr, verts.data(), verts.size(), nullptr, 0);
    SDL_RenderPresent(m_sdlApplication.r);

    if (NULL == m_sdlApplication.w)
    {
        printf("Could not create window\n");
        SDL_GetError();
        return 1;
    }

    // replace with game loop
    while (1)
    {
        if (SDL_PollEvent(&m_sdlApplication.event)) {
            if (SDL_QUIT == m_sdlApplication.event.type) break;
        }
    }

    SDL_DestroyWindow(m_sdlApplication.w);
    SDL_DestroyRenderer(m_sdlApplication.r);
    SDL_Quit();

    return EXIT_SUCCESS;
}