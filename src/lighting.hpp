#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include <Eigen/Dense>
#include <algorithm>
#include "constants.h"
#include "point.hpp"
#include "light.hpp"

using std::clamp;

Color diminish_light(float &z_buffer_val, Color &surf_color);
float color_interp(const float &start, const float &end, const float &p);
Color get_sky_color(float angle);
float get_brightness(Light &light_source, const Eigen::Vector4f &p0,
                     const Eigen::Vector4f &p1, const Eigen::Vector4f &p2,
                     const float min_brightness, const float max_brightness);
Color apply_light(float &brightness, Color &surf_color);

#endif