#include "lighting.hpp"

Color diminish_light(float &z_buffer_val, Color &surf_color)
{
    Color final_color = surf_color;
    float factor{1.0f};
    if (z_buffer_val > Z_DARK)
        factor = DARK_FACTOR;
    else if (z_buffer_val >= Z_BRIGHT)
        factor = (1.0f - DARK_FACTOR) * (z_buffer_val - Z_DARK) / (Z_BRIGHT - Z_DARK) + DARK_FACTOR;

    final_color.r *= factor;
    final_color.g *= factor;
    final_color.b *= factor;

    return final_color;
}