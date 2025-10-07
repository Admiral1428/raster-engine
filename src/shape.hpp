#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <cstdlib>
#include "point.hpp"
#include "surface.hpp"
#include "constants.h"

using std::vector;

// class defining a generic shape
class Shape
{
protected:
    float x;
    float y;
    float z;
    float width;
    float height;
    float depth;
    vector<Color> colors; // front, rear, left, right, bottom
    vector<Surface> surfaces;
    bool diminish_light;

public:
    Shape(); // default constructor (initializes object to default state with no arguments)
    Shape(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
          const vector<Color> &_colors, const bool &_dim_light = false);
    Shape(const Shape &);            // copy constructor
    virtual ~Shape();                // destructor
    Shape &operator=(const Shape &); // copy/assignment operator
    virtual void make_shape() = 0;   // method to be overwritten
    void translate(float dx, float dy, float dz);
    vector<Surface> &get_surfaces();
};

#endif