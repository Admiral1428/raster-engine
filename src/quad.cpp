#include "Quad.hpp"

Quad::Quad(const vector<float> &_p0, const vector<float> &_p1, const vector<float> &_p2, const vector<float> &_p3,
           const vector<Color> &_colors, const bool &_dim_light)
    : Shape(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, _colors, _dim_light, {}), p0(_p0), p1(_p1), p2(_p2), p3(_p3)
{
    make_shape();
}

Quad::Quad(const Quad &r) : Shape(r)
{
    p0 = r.p0;
    p1 = r.p1;
    p2 = r.p2;
    p3 = r.p3;
    make_shape();
}

Quad &Quad::operator=(const Quad &r)
{
    if (this != &r)
    {
        Shape::operator=(r);
        p0 = r.p0;
        p1 = r.p1;
        p2 = r.p2;
        p3 = r.p3;
        make_shape();
    }
    return *this;
}

void Quad::make_shape()
{
    Surface first_half;
    Surface second_half;

    // p0, p1, p3
    first_half = Surface(Eigen::Vector4f(p0[0], p0[1], p0[2], 1.0f),
                         Eigen::Vector4f(p1[0], p1[1], p1[2], 1.0f),
                         Eigen::Vector4f(p3[0], p3[1], p3[2], 1.0f), colors[0], diminish_light);
    // p1, p2, p3
    second_half = Surface(Eigen::Vector4f(p1[0], p1[1], p1[2], 1.0f),
                          Eigen::Vector4f(p2[0], p2[1], p2[2], 1.0f),
                          Eigen::Vector4f(p3[0], p3[1], p3[2], 1.0f), colors[0], diminish_light);

    surfaces.push_back(first_half);
    surfaces.push_back(second_half);
}