#include <SDL3/SDL.h>
#include <Eigen/Dense>
#include <iostream>
#include <array>
#include <string>
#include "constants.h"
#include "surface.hpp"
#include "renderer.hpp"
#include "rectprism.hpp"
#include "input.hpp"
#include "map.hpp"

using std::array;

int main(int argc, char *argv[])
{
    // Eigen::Vector4fers to window and renderer
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    // Initialize SDL
    if (!(SDL_Init(SDL_INIT_VIDEO)))
    {
        SDL_Log("Could not initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Initialize key down states
    array<bool, SDL_SCANCODE_COUNT> key_states = {};

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

    // Initialize map, surfaces vector, and renderer
    Map map;
    vector<Surface> all_surfaces;
    Renderer engine(0.3f, 100.0f, 90.0f, WIDTH, HEIGHT);

    // Move initial position relative to origin
    engine.move_view(Eigen::Vector3f(-4.0f, 0.0f, 1.5f), 0.0f, 0.0f);

    // Set mouse behavior and initialize event
    SDL_SetWindowRelativeMouseMode(window, true);
    SDL_Event event;

    // Mouse input variables
    bool window_focused;
    vector<float> mouse_delta;
    Uint64 last_mouse_time = SDL_GetPerformanceCounter();

    // Frame timing
    Uint64 last_frame_time = last_mouse_time;
    const float perf_freq = static_cast<float>(SDL_GetPerformanceFrequency());
    Uint64 current_frame_time;
    float frame_dt;

    // Main game loop
    while (!quit)
    {
        // delta time since last frame
        current_frame_time = SDL_GetPerformanceCounter();
        frame_dt = static_cast<float>(current_frame_time - last_frame_time) / perf_freq;
        last_frame_time = current_frame_time;

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
            if (event.type == SDL_EVENT_WINDOW_FOCUS_GAINED)
            {
                window_focused = true;
                SDL_SetWindowRelativeMouseMode(window, true);
            }
            else if (event.type == SDL_EVENT_WINDOW_FOCUS_LOST)
            {
                window_focused = false;
                SDL_SetWindowRelativeMouseMode(window, false);
            }
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                if (event.key.scancode < SDL_SCANCODE_COUNT)
                {
                    key_states[event.key.scancode] = true;
                }
            }
            else if (event.type == SDL_EVENT_KEY_UP)
            {
                if (event.key.scancode < SDL_SCANCODE_COUNT)
                {
                    key_states[event.key.scancode] = false;
                }
            }
        }

        // reset mouse delta
        mouse_delta = {0.0f, 0.0f};
        // only check mouse input if window active (i.e., not alt-tabbed)
        if (window_focused)
        {
            mouse_check(last_mouse_time, perf_freq, mouse_delta);
        }
        process_input(key_states, mouse_delta, frame_dt, engine, need_redraw);

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