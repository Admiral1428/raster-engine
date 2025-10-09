#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL3/SDL.h>
#include <Eigen/Dense>
#include "point.hpp"
#include "renderer.hpp"
#include <numbers>
#include <cmath>
#include <array>

using std::array;

void mouse_check(Uint64 &last_mouse_time, const float &perf_freq, vector<float> &mouse_delta);
void process_input(array<bool, SDL_SCANCODE_COUNT> &key_states, const vector<float> &mouse_delta,
                   const float &frame_dt, Renderer &engine, bool &need_redraw);

#endif