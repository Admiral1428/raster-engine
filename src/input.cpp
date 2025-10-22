#include "input.hpp"

void mouse_check(Uint64 &last_mouse_time, const float &perf_freq, vector<float> &mouse_delta)
{
    Uint64 cur_mouse_time = SDL_GetPerformanceCounter();
    float mouse_dt = static_cast<float>(cur_mouse_time - last_mouse_time) / perf_freq;

    // get mouse deltas
    if (mouse_dt >= (1.0f / MOUSE_HZ))
    {
        SDL_GetRelativeMouseState(&mouse_delta[0], &mouse_delta[1]);

        last_mouse_time = cur_mouse_time;
    }
}

void process_input(array<bool, SDL_SCANCODE_COUNT> &key_states, const vector<float> &mouse_delta,
                   const float &frame_dt, Renderer &engine, bool &need_redraw)
{
    float translate_amount = TRANSLATE_SPEED * frame_dt;
    float rotate_amount = ROTATE_SPEED * frame_dt;
    vector<float> mouse_rotate_amounts = {mouse_delta[0] * MOUSE_SENS_FACTOR * rotate_amount,
                                          mouse_delta[1] * MOUSE_SENS_FACTOR * rotate_amount};

    if (mouse_delta[0] != 0.0f || mouse_delta[1] != 0.0f)
    {
        engine.move_view(Eigen::Vector3f(0.0f, 0.0f, 0.0f), -mouse_rotate_amounts[1], -mouse_rotate_amounts[0]);
        need_redraw = true;
    }
    if (key_states[SDL_SCANCODE_UP])
    {
        engine.move_view(Eigen::Vector3f(0.0f, 0.0f, 0.0f), rotate_amount, 0.0f);
        need_redraw = true;
    }
    if (key_states[SDL_SCANCODE_DOWN])
    {
        engine.move_view(Eigen::Vector3f(0.0f, 0.0f, 0.0f), -rotate_amount, 0.0f);
        need_redraw = true;
    }
    if (key_states[SDL_SCANCODE_LEFT])
    {
        engine.move_view(Eigen::Vector3f(0.0f, 0.0f, 0.0f), 0.0f, rotate_amount);
        need_redraw = true;
    }
    if (key_states[SDL_SCANCODE_RIGHT])
    {
        engine.move_view(Eigen::Vector3f(0.0f, 0.0f, 0.0f), 0.0f, -rotate_amount);
        need_redraw = true;
    }
    if (key_states[SDL_SCANCODE_A])
    {
        vector<Eigen::Vector3f> new_dirs = engine.get_view_directions();
        engine.move_view(translate_amount * new_dirs[1], 0.0f, 0.0f);
        need_redraw = true;
    }
    if (key_states[SDL_SCANCODE_D])
    {
        vector<Eigen::Vector3f> new_dirs = engine.get_view_directions();
        engine.move_view(-translate_amount * new_dirs[1], 0.0f, 0.0f);
        need_redraw = true;
    }
    if (key_states[SDL_SCANCODE_W])
    {
        vector<Eigen::Vector3f> new_dirs = engine.get_view_directions();
        engine.move_view(translate_amount * new_dirs[0], 0.0f, 0.0f);
        need_redraw = true;
    }
    if (key_states[SDL_SCANCODE_S])
    {
        vector<Eigen::Vector3f> new_dirs = engine.get_view_directions();
        engine.move_view(-translate_amount * new_dirs[0], 0.0f, 0.0f);
        need_redraw = true;
    }
}

void process_f_key_down(array<bool, SDL_SCANCODE_COUNT> &key_states, Renderer &engine, SDL_Renderer &renderer,
                        bool &need_redraw, array<bool, 13> &f_keys_pressed, Uint64 &last_debug_time, int &cur_res_index,
                        int &render_mode_index)
{
    if (key_states[SDL_SCANCODE_F1] && !f_keys_pressed[1])
    {
        engine.cycle_fov();
        need_redraw = true;
        f_keys_pressed[1] = true;

        last_debug_time = SDL_GetPerformanceCounter();
    }
    else if (key_states[SDL_SCANCODE_F2] && !f_keys_pressed[2])
    {
        if (cur_res_index < RENDER_RES_OPTS.size() - 1)
        {
            cur_res_index += 1;
        }
        else
        {
            cur_res_index = 0;
        }

        float new_width = RENDER_RES_OPTS[cur_res_index].width;
        float new_height = RENDER_RES_OPTS[cur_res_index].height;

        engine.set_width_height(new_width, new_height);
        SDL_SetRenderLogicalPresentation(&renderer, new_width, new_height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
        last_debug_time = SDL_GetPerformanceCounter();
    }
    else if (key_states[SDL_SCANCODE_F3] && !f_keys_pressed[3])
    {
        if (render_mode_index < RENDER_MODES.size() - 1)
        {
            render_mode_index += 1;
        }
        else
        {
            render_mode_index = 0;
        }
        engine.set_render_mode(RENDER_MODES[render_mode_index]);

        last_debug_time = SDL_GetPerformanceCounter();
    }
}

void process_f_key_up(array<bool, SDL_SCANCODE_COUNT> &key_states, array<bool, 13> &f_keys_pressed)
{
    if (key_states[SDL_SCANCODE_F1])
    {
        f_keys_pressed[1] = false;
    }

    if (key_states[SDL_SCANCODE_F2])
    {
        f_keys_pressed[2] = false;
    }

    if (key_states[SDL_SCANCODE_F3])
    {
        f_keys_pressed[3] = false;
    }
}

void draw_settings_info(Renderer &engine, SDL_Renderer &renderer, SDL_Window &window, const float &frame_dt)
{
    // Field of view
    string fov_string = "Field of view = " + to_string(engine.get_fov());
    const char *fov_c_str = fov_string.c_str();
    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255); // BLACK text
    SDL_RenderDebugText(&renderer, 0, 0, fov_c_str);

    // Render resolution
    string render_res = "Render resolution = " +
                        to_string(static_cast<int>(engine.get_width())) + " x " +
                        to_string(static_cast<int>(engine.get_height()));
    const char *render_res_c_str = render_res.c_str();
    SDL_RenderDebugText(&renderer, 0, 10, render_res_c_str);

    // Window resolution
    int window_width, window_height;
    SDL_GetWindowSize(&window, &window_width, &window_height);

    string window_res = "Window resolution = " +
                        to_string(window_width) + " x " +
                        to_string(window_height);
    const char *window_res_c_str = window_res.c_str();
    SDL_RenderDebugText(&renderer, 0, 20, window_res_c_str);

    // Frametime and framerate
    string frame_time = "Frametime (ms): " + to_string(frame_dt * 1000.0f);
    string fps = "Frames per second: " + to_string(1.0f / frame_dt);
    const char *frame_time_c_str = frame_time.c_str();
    const char *fps_c_str = fps.c_str();
    SDL_RenderDebugText(&renderer, 0, 30, frame_time_c_str);
    SDL_RenderDebugText(&renderer, 0, 40, fps_c_str);

    // Render mode
    string render_mode_text = "Render mode: " + engine.get_render_mode();
    const char *render_mode_c_str = render_mode_text.c_str();
    SDL_RenderDebugText(&renderer, 0, 50, render_mode_c_str);
}