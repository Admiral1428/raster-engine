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
#include "boat.hpp"
#include "airplane.hpp"
#include "prop.hpp"
#include "map_textures.hpp"

using std::array;

void run_title(SDL_Renderer &_renderer)
{
    SDL_Texture *image_texture = IMG_LoadTexture(&_renderer, "../assets/images/main_title_screen.png");
    SDL_RenderClear(&_renderer);                              // Clear the renderer
    SDL_RenderTexture(&_renderer, image_texture, NULL, NULL); // Render texture to full window
    SDL_RenderPresent(&_renderer);                            // Present the rendered content to the screen

    bool quit_title = false;

    SDL_Event title_event;

    while (!quit_title)
    {
        SDL_WaitEvent(&title_event);
        if (title_event.type == SDL_EVENT_KEY_DOWN || title_event.type == SDL_EVENT_QUIT)
        {
            quit_title = true;
        }
    }

    SDL_DestroyTexture(image_texture);
    image_texture = NULL;
}

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

    // Initialize function key states
    array<bool, 13> f_keys_pressed = {};

    // Initialize chosen render resolution
    int cur_res_index = 0;

    // Initialize render mode
    int render_mode_index = 0;
    string render_mode = RENDER_MODES[render_mode_index];

    // Create a window and renderer
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE);
    if (!(SDL_CreateWindowAndRenderer("Raster Engine", RENDER_RES_OPTS[2].width, RENDER_RES_OPTS[2].height, window_flags, &window, &renderer)))
    {
        SDL_Log("Could not create window and renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Set logical presentation resolution
    SDL_SetRenderLogicalPresentation(renderer, RENDER_RES_OPTS[cur_res_index].width,
                                     RENDER_RES_OPTS[cur_res_index].height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    bool quit = false;
    bool need_redraw = true;

    // Initialize textures, map, surfaces vector, and renderer
    load_textures();
    Map map;
    vector<Surface> map_surfaces = map.get_map_surfaces();
    Renderer engine(0.3f, 1000.0f, 90.0f, RENDER_RES_OPTS[cur_res_index].width,
                    RENDER_RES_OPTS[cur_res_index].height, render_mode);

    // Initialize moving objects
    vector<Surface> boat_surfaces;
    vector<Surface> airplane_surfaces;
    vector<Surface> prop_surfaces;
    Boat boat(-32.0f, -3.0f, 60.0f, "small", 0.0f, 90.0f, 0.0f, "roll-pitch-yaw", -2.0f);
    Airplane airplane(-30.0f, 20.0f, 0.0f, "small", 0.0f, 90.0f, -30.0f, "roll-pitch-yaw", -15.0f);

    // Moving propeller location based on the static airplane defined in the map class
    Prop prop(-5.0f, -1.25f, 18.5f, "small", 0.0f, -240.0f, 16.0f, "yaw-pitch-roll", 540.0f);

    // Initialize vector to contain all surfaces
    vector<Surface> all_surfaces;

    // Move initial position relative to origin
    engine.move_view(Eigen::Vector3f(-4.0f, 0.0f, 1.5f), 0.0f, 0.0f);

    // // View of airplane
    // engine.move_view(Eigen::Vector3f(-2.63169956f, -1.12747788f, 17.5182972f), 6.85870695f, 127.83371f);

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
    float debug_dt;

    // Debug info timing, initialize as 6 seconds prior
    Uint64 last_debug_time = SDL_GetPerformanceCounter() - (6 * perf_freq);

    // Title screen flag
    bool show_title = true;

    // Main game loop
    while (!quit)
    {
        // delta time since last frame
        current_frame_time = SDL_GetPerformanceCounter();
        frame_dt = static_cast<float>(current_frame_time - last_frame_time) / perf_freq;
        last_frame_time = current_frame_time;

        // delta time since performance counter
        debug_dt = static_cast<float>(current_frame_time - last_debug_time) / perf_freq;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_EVENT_WINDOW_RESIZED)
            {
                float aspect_ratio = (float)RENDER_RES_OPTS[2].width / RENDER_RES_OPTS[2].height;
                int new_width = event.window.data1;
                int new_height = event.window.data2;

                // Calculate height based on new width, maintaining aspect ratio
                int calculated_height = (int)(new_width / aspect_ratio);
                if (calculated_height <= new_height)
                {
                    new_height = calculated_height;
                }
                else
                {
                    new_width = (int)(new_height * aspect_ratio);
                }

                SDL_SetWindowSize(window, new_width, new_height);
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
                process_f_key_down(key_states, engine, *renderer, *window, need_redraw,
                                   f_keys_pressed, last_debug_time, cur_res_index,
                                   render_mode_index, show_title);
            }
            else if (event.type == SDL_EVENT_KEY_UP)
            {
                process_f_key_up(event, f_keys_pressed);
                if (event.key.scancode < SDL_SCANCODE_COUNT)
                {
                    key_states[event.key.scancode] = false;
                }
            }
        }

        // show title screen
        if (show_title)
        {
            run_title(*renderer);
            show_title = false;
        }

        // reset mouse delta
        mouse_delta = {0.0f, 0.0f};
        // only check mouse input if window active (i.e., not alt-tabbed)
        if (window_focused)
        {
            mouse_check(last_mouse_time, perf_freq, mouse_delta);
        }
        process_input(key_states, mouse_delta, frame_dt, engine, need_redraw);

        // move objects
        boat.move(frame_dt);
        airplane.move(frame_dt);
        prop.move(frame_dt);
        boat_surfaces = boat.get_surfaces();
        airplane_surfaces = airplane.get_surfaces();
        prop_surfaces = prop.get_surfaces();

        need_redraw = true;

        if (need_redraw)
        {
            // // Draw background
            SDL_SetRenderDrawColor(renderer, BACK_COLOR.r, BACK_COLOR.g, BACK_COLOR.b, BACK_COLOR.a);
            // Clear screen
            SDL_RenderClear(renderer);

            // Get surfaces
            all_surfaces.clear();
            all_surfaces.insert(all_surfaces.end(), map_surfaces.begin(), map_surfaces.end());
            all_surfaces.insert(all_surfaces.end(), boat_surfaces.begin(), boat_surfaces.end());
            all_surfaces.insert(all_surfaces.end(), airplane_surfaces.begin(), airplane_surfaces.end());
            all_surfaces.insert(all_surfaces.end(), prop_surfaces.begin(), prop_surfaces.end());

            // Update animations
            TEXTURES.at("water").update_animation();
            TEXTURES.at("waterfall").update_animation();
            TEXTURES.at("cloth").update_animation();

            // Draw surfaces
            engine.draw_surfaces(*renderer, all_surfaces);

            // Draw settings if recently changed
            if (debug_dt < 5.0f)
            {
                draw_settings_info(engine, *renderer, *window, frame_dt);
            }

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