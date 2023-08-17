#include <stdio.h>
#include <SDL.h>
#include <cstdlib>
#include "e_config.h"
#include "types.h"
#include <vector>
#include "Renderer.h"
using namespace Renderer;

float pitch = 0.0f, yaw = 0.0f;

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* w = SDL_CreateWindow("DEMO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    application m_sdlApplication = {
        w,
        nullptr,
        0
    };

    m_sdlApplication.r = SDL_CreateRenderer(m_sdlApplication.w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (NULL == m_sdlApplication.w)
    {
        printf("Could not create window\n");
        SDL_GetError();
        return 1;
    }

    Rasterizer raster;

    raster.setDisplay(m_sdlApplication.r, WIDTH, HEIGHT);
    raster.focalLength = 0.2;
    raster.backfaceCull = 0;

    raster.cam.locate(0, 0, 1);

    //Object test
    Mesh vulcanMesh;
    vulcanMesh.loadPly("C:\\Users\\james\\source\\repos\\sdl-lupo\\sdl-lupo\\models\\vulc1.ply");
    RenderObject craft(&vulcanMesh);
    craft.vz = -0.1;
    craft.locate(-1, 0, -4);

    Mesh deloreanMesh;
    deloreanMesh.loadPly("C:\\Users\\james\\source\\repos\\sdl-lupo\\sdl-lupo\\models\\delor1.ply");
    RenderObject car(&deloreanMesh);
    car.vz = -0.1;
    car.locate(1, 0, -1);

    // replace with game loop
    while (1)
    {
        if (SDL_PollEvent(&m_sdlApplication.event)) {
            // Get Camera Location
            if (SDL_MOUSEMOTION == m_sdlApplication.event.type) {

            }
            if (SDL_QUIT == m_sdlApplication.event.type) break;
        }
    }

    SDL_DestroyWindow(m_sdlApplication.w);
    SDL_DestroyRenderer(m_sdlApplication.r);
    SDL_Quit();

    return EXIT_SUCCESS;
}