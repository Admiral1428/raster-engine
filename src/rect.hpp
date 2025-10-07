#ifndef RECT_HPP
#define RECT_HPP

#include "shape.hpp"

// class defining a flat rectangle
class Rect : public Shape
{
public:
    Rect(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
         const vector<Color> &_colors, const bool &_dim_light = false);
    Rect(const Rect &p);
    Rect &operator=(const Rect &);
    void make_shape() override;
};

#endif