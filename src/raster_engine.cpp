#include <SDL3/SDL.h>
#include <iostream>
#include "constants.h"
#include "surface.hpp"
#include "camera.hpp"
#include "rectprism.hpp"

using std::cout;

int main(int argc, char *argv[])
{
    // Pointers to window and renderer
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    // Initialize SDL
    if (!(SDL_Init(SDL_INIT_VIDEO)))
    {
        SDL_Log("Could not initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window and renderer
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE);
    if (!(SDL_CreateWindowAndRenderer("Raster Engine", WINDOW_WIDTH, WINDOW_HEIGHT, window_flags, &window, &renderer)))
    {
        SDL_Log("Could not create window and renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool quit = false;

    RectPrism rect(1.5f, 1.5f, -5.0f, 2.0f, 2.0f, 2.0f);
    // RectPrism rect(0.0f, 0.0f, -0.6f, 1.0f, 1.0f, 1.0f);

    Camera cam(0.1f, 100.0f, 90.0f);
    float width = WINDOW_WIDTH;
    float height = WINDOW_HEIGHT;
    SDL_Event event;

    // Main game loop
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_EVENT_WINDOW_RESIZED)
            {
                width = static_cast<float>(event.window.data1);
                height = static_cast<float>(event.window.data2);
            }
            else if (event.type == SDL_EVENT_KEY_DOWN)
            {
                float translate_amount = 0.05f;
                if (event.key.key == SDLK_A)
                {
                    rect.translate(-1 * translate_amount, 0.0f, 0.0f);
                }
                else if (event.key.key == SDLK_D)
                {
                    rect.translate(translate_amount, 0.0f, 0.0f);
                }
                else if (event.key.key == SDLK_W)
                {
                    rect.translate(0.0f, 0.0f, translate_amount);
                }
                else if (event.key.key == SDLK_S)
                {
                    rect.translate(0.0f, 0.0f, -1 * translate_amount);
                }
                else if (event.key.key == SDLK_Q)
                {
                    rect.translate(0.0f, translate_amount, 0.0f);
                }
                else if (event.key.key == SDLK_E)
                {
                    rect.translate(0.0f, -1 * translate_amount, 0.0f);
                }
            }
        }

        // Black background
        SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        // Clear screen
        SDL_RenderClear(renderer);

        // Draw surface vertices and lines
        array<array<float, 4>, 4> proj_matrix = cam.get_projection_matrix();
        for (auto &surface : rect.get_surfaces())
        {
            surface.transform_to_camera(proj_matrix, width, height);
            surface.draw_vertices(*renderer, width, height);
            surface.draw_edges(*renderer, width, height);
        }

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}