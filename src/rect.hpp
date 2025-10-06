#ifndef RECT_HPP
#define RECT_HPP

#include <vector>
#include <cstdlib>
#include "point.h"
#include "surface.hpp"
#include "constants.h"

using std::vector;

// class defining a flat rectangle
class Rect
{
private:
    float center_x;
    float center_y;
    float center_z;
    float width;
    float height;
    float depth;
    Color color;
    vector<Surface> surfaces;
    bool diminish_light;

public:
    Rect(); // default constructor (initializes object to default state with no arguments)
    Rect(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
         const Color &_color, const bool &_dim_light = false);
    Rect(const Rect &);            // copy constructor
    ~Rect();                       // destructor
    Rect &operator=(const Rect &); // copy/assignment operator
    void make_shape();
    void translate(float dx, float dy, float dz);
    vector<Surface> &get_surfaces();
};

// implementation
Rect::Rect() : center_x(0), center_y(0), center_z(0), width(1), height(1), depth(1), color(GREEN), diminish_light(false) {}
Rect::Rect(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
           const Color &_color, const bool &_dim_light)
    : center_x(_x), center_y(_y), center_z(_z), width(_w), height(_h), depth(_d), color(_color), diminish_light(_dim_light)
{
    make_shape();
}
Rect::Rect(const Rect &r)
{
    center_x = r.center_x;
    center_y = r.center_y;
    center_z = r.center_z;
    width = r.width;
    height = r.height;
    depth = r.depth;
    color = r.color;
    diminish_light = r.diminish_light;
    make_shape();
}

Rect::~Rect() {}

Rect &Rect::operator=(const Rect &r)
{
    if (this != &r)
    {
        center_x = r.center_x;
        center_y = r.center_y;
        center_z = r.center_z;
        width = r.width;
        height = r.height;
        depth = r.depth;
        color = r.color;
        diminish_light = r.diminish_light;
        make_shape();
    }
    return *this;
}

void Rect::make_shape()
{
    int false_count = 0;
    vector<bool> bools = {width == 0.0f, height == 0.0f, depth == 0.0f};

    for (auto b : bools)
    {
        if (b)
        {
            ++false_count;
        }
    }

    if (false_count == 1)
    {
        Surface first_half;
        Surface second_half;

        // Flat rectangle aligned with depth-height plane
        if (width == 0.0f)
        {
            first_half = Surface(Point{center_x, center_y - height / 2, center_z + depth / 2, 1.0f},
                                 Point{center_x, center_y + height / 2, center_z + depth / 2, 1.0f},
                                 Point{center_x, center_y - height / 2, center_z - depth / 2, 1.0f}, color, diminish_light);
            second_half = Surface(Point{center_x, center_y + height / 2, center_z - depth / 2, 1.0f},
                                  Point{center_x, center_y + height / 2, center_z + depth / 2, 1.0f},
                                  Point{center_x, center_y - height / 2, center_z - depth / 2, 1.0f}, color, diminish_light);
        }
        // Flat rectangle aligned with width-depth plane
        else if (height == 0.0f)
        {
            first_half = Surface(Point{center_x - width / 2, center_y, center_z + depth / 2, 1.0f},
                                 Point{center_x + width / 2, center_y, center_z + depth / 2, 1.0f},
                                 Point{center_x + width / 2, center_y, center_z - depth / 2, 1.0f}, color, diminish_light);
            second_half = Surface(Point{center_x - width / 2, center_y, center_z + depth / 2, 1.0f},
                                  Point{center_x - width / 2, center_y, center_z - depth / 2, 1.0f},
                                  Point{center_x + width / 2, center_y, center_z - depth / 2, 1.0f}, color, diminish_light);
        }
        // Flat rectangle aligned with width-height plane
        else if (depth == 0.0f)
        {
            first_half = Surface(Point{center_x - width / 2, center_y - height / 2, center_z, 1.0f},
                                 Point{center_x + width / 2, center_y - height / 2, center_z, 1.0f},
                                 Point{center_x + width / 2, center_y + height / 2, center_z, 1.0f}, color, diminish_light);
            second_half = Surface(Point{center_x - width / 2, center_y - height / 2, center_z, 1.0f},
                                  Point{center_x - width / 2, center_y + height / 2, center_z, 1.0f},
                                  Point{center_x + width / 2, center_y + height / 2, center_z, 1.0f}, color, diminish_light);
        }

        surfaces.push_back(first_half);
        surfaces.push_back(second_half);
    }
}

void Rect::translate(float dx, float dy, float dz)
{
    for (auto &surface : surfaces)
    {
        surface.translate(dx, dy, dz);
    }
}

vector<Surface> &Rect::get_surfaces()
{
    return surfaces;
}

#endif