#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL3/SDL.h>
#include <Eigen/Dense>
#include "point.hpp"
#include "renderer.hpp"
#include <numbers>
#include <cmath>
#include <array>
#include <string>

using std::array;
using std::round;
using std::to_string;

void mouse_check(Uint64 &last_mouse_time, const float &perf_freq, vector<float> &mouse_delta);
void process_input(array<bool, SDL_SCANCODE_COUNT> &key_states, const vector<float> &mouse_delta,
                   const float &frame_dt, Renderer &engine, bool &need_redraw);
void process_f_key_down(array<bool, SDL_SCANCODE_COUNT> &key_states, Renderer &engine, SDL_Renderer &renderer,
                        SDL_Window &window, bool &need_redraw, array<bool, 13> &f_keys_pressed, Uint64 &last_debug_time,
                        int &cur_res_index, int &render_mode_index, bool &show_title);
void process_f_key_up(const SDL_Event &event, array<bool, 13> &f_keys_pressed);
void draw_settings_info(Renderer &engine, SDL_Renderer &renderer, SDL_Window &window, const float &frame_dt,
                        const float &day_night_angle);

#endif