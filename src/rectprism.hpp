#ifndef RECTPRISM_HPP
#define RECTPRISM_HPP

#include <Eigen/Dense>
#include "shape.hpp"
#include "rect.hpp"
#include <algorithm>

using std::find;

// class defining a rectangular prism
class RectPrism : public Shape
{
public:
    RectPrism(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
              const vector<Color> &_colors, const bool &_dim_light = false, const vector<string> &_skip_surfs = {});
    RectPrism(const RectPrism &p);
    RectPrism &operator=(const RectPrism &);
    void make_shape() override;
    void set_texture_properties(const string &texture_name, const float &width_factor, const float &height_factor,
                                const string &face);
};

#endif