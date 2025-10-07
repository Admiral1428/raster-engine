#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <vector>
#include "constants.h"
#include "point.hpp"

using std::vector;

// class defining a triangular surface
class Surface
{
private:
    Point p0; // original coordinates
    Point p1;
    Point p2;
    Color color;
    bool diminish_light;

public:
    Surface(); // default constructor (initializes object to default state with no arguments)
    Surface(const Point &_p0, const Point &_p1, const Point &_p2, const Color &_color = RED, const bool &_dim_light = false);
    Surface(const Surface &);            // copy constructor
    ~Surface();                          // destructor
    Surface &operator=(const Surface &); // copy/assignment operator
    void set_color(const Color &c);
    const Color get_color() const;
    void translate(float dx, float dy, float dz);
    vector<Point> get_points();
    bool &get_diminish_light();
};

#endif