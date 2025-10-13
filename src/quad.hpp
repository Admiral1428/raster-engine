#ifndef QUAD_HPP
#define QUAD_HPP

#include <Eigen/Dense>
#include "shape.hpp"

// class defining a flat quadrilateral
class Quad : public Shape
{
private:
    vector<float> p0;
    vector<float> p1;
    vector<float> p2;
    vector<float> p3;

public:
    Quad(const vector<float> &_p0, const vector<float> &_p1, const vector<float> &_p2, const vector<float> &_p3,
         const vector<Color> &_colors, const bool &_dim_light = false);
    Quad(const Quad &p);
    Quad &operator=(const Quad &);
    void make_shape() override;
};

#endif