#include <SDL3/SDL.h>
#include <iostream>
#include "constants.h"
#include "surface.hpp"
#include "renderer.hpp"
#include "rectprism.hpp"
#include "input.hpp"
#include "map.hpp"

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

    // Initialize map and surfaces vector
    Map map;
    vector<Surface> all_surfaces;

    Renderer engine(0.3f, 100.0f, 90.0f, WIDTH, HEIGHT);
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
                process_input(event, map.get_rect_prism(0), need_redraw);
            }
        }

        if (need_redraw)
        {
            // Draw background
            SDL_SetRenderDrawColor(renderer, BACK_COLOR.r, BACK_COLOR.g, BACK_COLOR.b, BACK_COLOR.a);
            // Clear screen
            SDL_RenderClear(renderer);

            // Get map surfaces
            all_surfaces = map.get_map_surfaces();

            // Draw surfaces
            engine.draw_surfaces(*renderer, all_surfaces);

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