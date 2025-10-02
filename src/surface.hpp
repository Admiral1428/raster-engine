#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <vector>
#include "constants.h"
#include "point.h"

using std::vector;

// class defining a triangular surface
class Surface
{
private:
    Point p0; // original coordinates
    Point p1;
    Point p2;
    Color color;

public:
    Surface(); // default constructor (initializes object to default state with no arguments)
    Surface(const Point &_p0, const Point &_p1, const Point &_p2, const Color &_color = RED);
    Surface(const Surface &);            // copy constructor
    ~Surface();                          // destructor
    Surface &operator=(const Surface &); // copy/assignment operator
    void set_color(const Color &c);
    const Color get_color() const;
    void translate(float dx, float dy, float dz);
    vector<Point> get_points();
};

// implementation
Surface::Surface() : p0({0.0f, 0.0f, 0.0f}), p1({0.0f, 0.0f, 0.0f}), p2({0.0f, 0.0f, 0.0f}) {}
Surface::Surface(const Point &_p0, const Point &_p1, const Point &_p2, const Color &_color)
    : p0(_p0), p1(_p1), p2(_p2), color(_color) {}
Surface::Surface(const Surface &s)
{
    p0 = s.p0;
    p1 = s.p1;
    p2 = s.p2;
    color = s.color;
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

#endif