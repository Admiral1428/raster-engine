#include "input.hpp"

void mouse_check(Uint64 &last_mouse_time, const float &perf_freq, vector<float> &mouse_delta)
{
    Uint64 cur_mouse_time = SDL_GetPerformanceCounter();
    float mouse_dt = static_cast<float>(cur_mouse_time - last_mouse_time) / perf_freq;

    // reset then get mouse deltas
    mouse_delta = {0.0f, 0.0f};
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