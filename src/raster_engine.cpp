#include <SDL3/SDL.h>
#include <iostream>
#include "constants.h"
#include "surface.hpp"
#include "renderer.hpp"
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
    if (!(SDL_CreateWindowAndRenderer("Raster Engine", WIDTH, HEIGHT, window_flags, &window, &renderer)))
    {
        SDL_Log("Could not create window and renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    bool need_redraw = true;

    RectPrism rect(1.5f, 1.5f, -5.0f, 2.0f, 2.0f, 2.0f);

    Renderer engine(0.1f, 100.0f, 90.0f, WIDTH, HEIGHT);
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
                engine.set_width_height(event.window.data1, event.window.data2);
                need_redraw = true;
            }
            else if (event.type == SDL_EVENT_KEY_DOWN)
            {
                float translate_amount = 0.05f;
                if (event.key.key == SDLK_A)
                {
                    rect.translate(-1 * translate_amount, 0.0f, 0.0f);
                    need_redraw = true;
                }
                else if (event.key.key == SDLK_D)
                {
                    rect.translate(translate_amount, 0.0f, 0.0f);
                    need_redraw = true;
                }
                else if (event.key.key == SDLK_W)
                {
                    rect.translate(0.0f, 0.0f, translate_amount);
                    need_redraw = true;
                }
                else if (event.key.key == SDLK_S)
                {
                    rect.translate(0.0f, 0.0f, -1 * translate_amount);
                    need_redraw = true;
                }
                else if (event.key.key == SDLK_Q)
                {
                    rect.translate(0.0f, translate_amount, 0.0f);
                    need_redraw = true;
                }
                else if (event.key.key == SDLK_E)
                {
                    rect.translate(0.0f, -1 * translate_amount, 0.0f);
                    need_redraw = true;
                }
            }
        }

        // rect.translate(0.0f, 0.0f, 0.05f);
        // need_redraw = true;

        if (need_redraw)
        {
            // Black background
            SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
            // Clear screen
            SDL_RenderClear(renderer);

            // vector<Surface> surfaces = {triangle_near, triangle_far};
            // Draw surfaces
            engine.draw_surfaces(*renderer, rect.get_surfaces());
            // engine.draw_surfaces(*renderer, surfaces);

            // Update the screen
            SDL_RenderPresent(renderer);

            // Reset flag
            need_redraw = false;
        }
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}