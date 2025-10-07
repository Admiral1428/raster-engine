#ifndef RECTPRISM_HPP
#define RECTPRISM_HPP

#include "shape.hpp"

// class defining a rectangular prism
class RectPrism : public Shape
{
public:
    RectPrism(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
              const vector<Color> &_colors, const bool &_dim_light = false);
    RectPrism(const RectPrism &p);
    RectPrism &operator=(const RectPrism &);
    void make_shape() override;
};

#endif