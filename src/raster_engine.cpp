#include <SDL3/SDL.h>
#include "constants.h"
#include "point.h"

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
    if (!(SDL_CreateWindowAndRenderer("Raster Engine", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)))
    {
        SDL_Log("Could not create window and renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    bool quit = false;
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
        }

        // Black background
        SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
        // Clear screen
        SDL_RenderClear(renderer);

        // White dots
        Point p1{500.0, 300.0, 0.0};
        Point p2{500.0, 800.0, 0.0};
        Point p3{1000.0, 800.0, 0.0};
        SDL_SetRenderDrawColor(renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);
        SDL_RenderPoint(renderer, p1.x, p1.y);
        SDL_RenderPoint(renderer, p2.x, p2.y);
        SDL_RenderPoint(renderer, p3.x, p3.y);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}