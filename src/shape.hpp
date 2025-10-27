#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>
#include <cstdlib>
#include <string>
#include <Eigen/Dense>
#include "point.hpp"
#include "surface.hpp"
#include "constants.h"

using std::string;
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
    vector<string> skip_surfaces; // strings specifying which components to skip

public:
    Shape(); // default constructor (initializes object to default state with no arguments)
    Shape(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
          const vector<Color> &_colors, const bool &_dim_light = false, const vector<string> &_skip_surfs = {});
    Shape(const Shape &);            // copy constructor
    virtual ~Shape();                // destructor
    Shape &operator=(const Shape &); // copy/assignment operator
    virtual void make_shape() = 0;   // method to be overwritten
    void translate(const float &dx, const float &dy, const float &dz);
    void rotate(const float &roll, const float &pitch, const float &yaw, const string &order);
    vector<Surface> &get_surfaces();
    void set_min_brightness(const float &val);
    void set_max_brightness(const float &val);
};

#endif