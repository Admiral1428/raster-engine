#include "input.hpp"

void process_input(SDL_Event &event, RectPrism &rect, bool &need_redraw)
{
    float translate_amount = 0.05f;
    if (event.key.key == SDLK_A)
    {
        rect.translate(-1 * translate_amount, 0.0f, 0.0f);
        need_redraw = true;
    }
    else if (event.key.key == SDLK_D)
    {
        rect.translate(translate_amount, 0.0f, 0.0f);
        need_redraw = true;
    }
    else if (event.key.key == SDLK_W)
    {
        rect.translate(0.0f, 0.0f, translate_amount);
        need_redraw = true;
    }
    else if (event.key.key == SDLK_S)
    {
        rect.translate(0.0f, 0.0f, -1 * translate_amount);
        need_redraw = true;
    }
    else if (event.key.key == SDLK_Q)
    {
        rect.translate(0.0f, translate_amount, 0.0f);
        need_redraw = true;
    }
    else if (event.key.key == SDLK_E)
    {
        rect.translate(0.0f, -1 * translate_amount, 0.0f);
        need_redraw = true;
    }
}