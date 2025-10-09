#include "surface.hpp"

// implementation
Surface::Surface() {}
Surface::Surface(const Eigen::Vector4f &_p0, const Eigen::Vector4f &_p1, const Eigen::Vector4f &_p2, const Color &_color, const bool &_dim_light)
    : p0(_p0), p1(_p1), p2(_p2), color(_color), diminish_light(_dim_light) {}
Surface::Surface(const Surface &s)
{
    p0 = s.p0;
    p1 = s.p1;
    p2 = s.p2;
    color = s.color;
    diminish_light = s.diminish_light;
}

Surface::~Surface() {}

Surface &Surface::operator=(const Surface &s)
{
    if (this != &s)
    {
        p0 = s.p0;
        p1 = s.p1;
        p2 = s.p2;
        color = s.color;
        diminish_light = s.diminish_light;
    }
    return *this;
}

void Surface::set_color(const Color &c)
{
    color = c;
}

const Color Surface::get_color() const
{
    return color;
}

void Surface::translate(float dx, float dy, float dz)
{
    p0(0) += dx;
    p0(1) += dy;
    p0(2) += dz;

    p1(0) += dx;
    p1(1) += dy;
    p1(2) += dz;

    p2(0) += dx;
    p2(1) += dy;
    p2(2) += dz;
}

vector<Eigen::Vector4f> Surface::get_points()
{
    return {p0, p1, p2};
}

bool &Surface::get_diminish_light()
{
    return diminish_light;
}