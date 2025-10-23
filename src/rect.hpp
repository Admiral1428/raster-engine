#ifndef RECT_HPP
#define RECT_HPP

#include <Eigen/Dense>
#include "shape.hpp"

// class defining a flat rectangle
class Rect : public Shape
{
public:
    Rect(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
         const vector<Color> &_colors, const bool &_dim_light = false, const vector<string> &_skip_surfs = {});
    Rect(const Rect &p);
    Rect &operator=(const Rect &);
    void make_shape() override;
    void set_texture_properties(const string &texture_name, const float &width_factor, const float &height_factor);
};

#endif