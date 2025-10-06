#ifndef PYRAMID_HPP
#define PYRAMID_HPP

#include <vector>
#include <cstdlib>
#include "point.h"
#include "surface.hpp"
#include "constants.h"

using std::vector;

// class defining a rectangular prism
class Pyramid
{
private:
    float center_x;
    float bottom_y;
    float center_z;
    float width;
    float height;
    float depth;
    vector<Color> colors; // front, rear, left, right, bottom
    vector<Surface> surfaces;
    bool diminish_light;

public:
    Pyramid(); // default constructor (initializes object to default state with no arguments)
    Pyramid(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
            const vector<Color> &_colors, const bool &_dim_light = false);
    Pyramid(const Pyramid &);            // copy constructor
    ~Pyramid();                          // destructor
    Pyramid &operator=(const Pyramid &); // copy/assignment operator
    void make_shape();
    void translate(float dx, float dy, float dz);
    vector<Surface> &get_surfaces();
};

// implementation
Pyramid::Pyramid() : center_x(0), bottom_y(0), center_z(0), width(1), height(1), depth(1),
                     colors({RED, MAGENTA, BLUE, CYAN, YELLOW}), diminish_light(false) {}
Pyramid::Pyramid(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
                 const vector<Color> &_colors, const bool &_dim_light)
    : center_x(_x), bottom_y(_y), center_z(_z), width(_w), height(_h), depth(_d), colors(_colors), diminish_light(_dim_light)
{
    make_shape();
}
Pyramid::Pyramid(const Pyramid &r)
{
    center_x = r.center_x;
    bottom_y = r.bottom_y;
    center_z = r.center_z;
    width = r.width;
    height = r.height;
    depth = r.depth;
    colors = r.colors;
    diminish_light = r.diminish_light;
    make_shape();
}

Pyramid::~Pyramid() {}

Pyramid &Pyramid::operator=(const Pyramid &r)
{
    if (this != &r)
    {
        center_x = r.center_x;
        bottom_y = r.bottom_y;
        center_z = r.center_z;
        width = r.width;
        height = r.height;
        depth = r.depth;
        colors = r.colors;
        diminish_light = r.diminish_light;
        make_shape();
    }
    return *this;
}

void Pyramid::make_shape()
{
    float translate_clip = TOL_SHIFT_SURFACE;

    // shift rear surfaces into page to avoid z-fighting
    // shift left surfaces left in x to avoid z-fighting
    // shift right surfaces right in x to avoid z-fighting
    // shift bottom surfaces down in y to avoid z-fighthing

    Surface front(Point{center_x - width / 2, bottom_y, center_z + depth / 2, 1.0f},
                  Point{center_x + width / 2, bottom_y, center_z + depth / 2, 1.0f},
                  Point{center_x, bottom_y + height, center_z, 1.0f}, colors[0], diminish_light);
    Surface rear(Point{center_x - width / 2, bottom_y, center_z - (translate_clip + depth / 2), 1.0f},
                 Point{center_x + width / 2, bottom_y, center_z - (translate_clip + depth / 2), 1.0f},
                 Point{center_x, bottom_y + height, (center_z - translate_clip), 1.0f}, colors[1], diminish_light);
    Surface left(Point{center_x - (translate_clip + width / 2), bottom_y, center_z + depth / 2, 1.0f},
                 Point{center_x - (translate_clip + width / 2), bottom_y, center_z - depth / 2, 1.0f},
                 Point{center_x - translate_clip, bottom_y + height, center_z, 1.0f}, colors[2], diminish_light);
    Surface right(Point{center_x + (translate_clip + width / 2), bottom_y, center_z + depth / 2, 1.0f},
                  Point{center_x + (translate_clip + width / 2), bottom_y, center_z - depth / 2, 1.0f},
                  Point{center_x + translate_clip, bottom_y + height, center_z, 1.0f}, colors[3], diminish_light);
    Surface bottom_near(Point{center_x - width / 2, bottom_y - translate_clip, center_z + depth / 2, 1.0f},
                        Point{center_x + width / 2, bottom_y - translate_clip, center_z + depth / 2, 1.0f},
                        Point{center_x + width / 2, bottom_y - translate_clip, center_z - depth / 2, 1.0f}, colors[4], diminish_light);
    Surface bottom_far(Point{center_x - width / 2, bottom_y - translate_clip, center_z + depth / 2, 1.0f},
                       Point{center_x - width / 2, bottom_y - translate_clip, center_z - depth / 2, 1.0f},
                       Point{center_x + width / 2, bottom_y - translate_clip, center_z - depth / 2, 1.0f}, colors[4], diminish_light);

    surfaces.push_back(front);
    surfaces.push_back(rear);
    surfaces.push_back(left);
    surfaces.push_back(right);
    surfaces.push_back(bottom_near);
    surfaces.push_back(bottom_far);
}

void Pyramid::translate(float dx, float dy, float dz)
{
    for (auto &surface : surfaces)
    {
        surface.translate(dx, dy, dz);
    }
}

vector<Surface> &Pyramid::get_surfaces()
{
    return surfaces;
}

#endif