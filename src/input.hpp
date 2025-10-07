#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL3/SDL.h>
#include "rectprism.hpp"
#include "surface.hpp"

using std::vector;

void process_input(SDL_Event &event, RectPrism &rect, bool &need_redraw);

#endif