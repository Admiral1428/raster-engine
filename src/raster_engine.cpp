#include <SDL3/SDL.h>
#include "constants.h"
#include "surface.hpp"

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
    float width_scale{1.0};
    float height_scale{1.0};
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
                width_scale = static_cast<float>(event.window.data1) / WINDOW_WIDTH;
                height_scale = static_cast<float>(event.window.data2) / WINDOW_HEIGHT;
            }
        }

        // Black background
        SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        // Clear screen
        SDL_RenderClear(renderer);

        // White dots
        Surface s1{Point{int(500 * width_scale), int(300 * height_scale), 0},
                   Point{int(500 * width_scale), int(800 * height_scale), 0},
                   Point{int(1000 * width_scale), int(800 * height_scale), 0}};
        s1.draw_vertices(*renderer, WHITE);
        s1.draw_edges(*renderer, RED);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}