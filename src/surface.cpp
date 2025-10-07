#include "surface.hpp"

// implementation
Surface::Surface() : p0({0.0f, 0.0f, 0.0f}), p1({0.0f, 0.0f, 0.0f}), p2({0.0f, 0.0f, 0.0f}) {}
Surface::Surface(const Point &_p0, const Point &_p1, const Point &_p2, const Color &_color, const bool &_dim_light)
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
    p0.x += dx;
    p0.y += dy;
    p0.z += dz;

    p1.x += dx;
    p1.y += dy;
    p1.z += dz;

    p2.x += dx;
    p2.y += dy;
    p2.z += dz;
}

vector<Point> Surface::get_points()
{
    return {p0, p1, p2};
}

bool &Surface::get_diminish_light()
{
    return diminish_light;
}