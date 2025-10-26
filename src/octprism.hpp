#ifndef OCTPRISM_HPP
#define OCTPRISM_HPP

#include <Eigen/Dense>
#include "shape.hpp"
#include "quad.hpp"
#include "pyramid.hpp"
#include <algorithm>
#include <cmath>

using std::find;
using std::sqrt;

// class defining an octogonal prism (cylinder-like)
class OctPrism : public Shape
{
private:
    vector<vector<float>> vertices;

public:
    OctPrism(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
             const vector<Color> &_colors, const bool &_dim_light = false, const vector<string> &_skip_surfs = {});
    OctPrism(const OctPrism &p);
    OctPrism &operator=(const OctPrism &);
    void make_shape() override;
    void set_texture_properties(const string &texture_name);
};

#endif