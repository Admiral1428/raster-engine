#ifndef PYRAMID_HPP
#define PYRAMID_HPP

#include "shape.hpp"

// class defining a pyramid
class Pyramid : public Shape
{
public:
    Pyramid(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
            const vector<Color> &_colors, const bool &_dim_light = false);
    Pyramid(const Pyramid &p);
    Pyramid &operator=(const Pyramid &);
    void make_shape() override;
};

#endif