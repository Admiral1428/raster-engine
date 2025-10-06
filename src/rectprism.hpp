#ifndef RECTPRISM_HPP
#define RECTPRISM_HPP

#include <vector>
#include <cstdlib>
#include "point.h"
#include "surface.hpp"
#include "constants.h"

using std::vector;

// class defining a rectangular prism
class RectPrism
{
private:
    float center_x;
    float center_y;
    float center_z;
    float width;
    float height;
    float depth;
    vector<Color> colors; // front, rear, left, right, top, bottom
    vector<Surface> surfaces;
    bool diminish_light;

public:
    RectPrism(); // default constructor (initializes object to default state with no arguments)
    RectPrism(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
              const vector<Color> &_colors, const bool &_dim_light = false);
    RectPrism(const RectPrism &);            // copy constructor
    ~RectPrism();                            // destructor
    RectPrism &operator=(const RectPrism &); // copy/assignment operator
    void make_shape();
    void translate(float dx, float dy, float dz);
    vector<Surface> &get_surfaces();
};

// implementation
RectPrism::RectPrism() : center_x(0), center_y(0), center_z(0), width(1), height(1), depth(1),
                         colors({RED, MAGENTA, BLUE, CYAN, GREEN, YELLOW}), diminish_light(false) {}
RectPrism::RectPrism(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
                     const vector<Color> &_colors, const bool &_dim_light)
    : center_x(_x), center_y(_y), center_z(_z), width(_w), height(_h), depth(_d), colors(_colors), diminish_light(_dim_light)
{
    make_shape();
}
RectPrism::RectPrism(const RectPrism &r)
{
    center_x = r.center_x;
    center_y = r.center_y;
    center_z = r.center_z;
    width = r.width;
    height = r.height;
    depth = r.depth;
    colors = r.colors;
    diminish_light = r.diminish_light;
    make_shape();
}

RectPrism::~RectPrism() {}

RectPrism &RectPrism::operator=(const RectPrism &r)
{
    if (this != &r)
    {
        center_x = r.center_x;
        center_y = r.center_y;
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

void RectPrism::make_shape()
{
    float translate_clip = TOL_SHIFT_SURFACE;

    // shift rear surfaces into page to avoid z-fighting
    // shift left surfaces left in x to avoid z-fighting
    // shift right surfaces right in x to avoid z-fighting
    // shift top surface up in y to avoid z-fighting
    // shift bottom surfaces down in y to avoid z-fighthing

    Surface front_left(Point{center_x - width / 2, center_y - height / 2, center_z + depth / 2, 1.0f},
                       Point{center_x - width / 2, center_y + height / 2, center_z + depth / 2, 1.0f},
                       Point{center_x + width / 2, center_y - height / 2, center_z + depth / 2, 1.0f}, colors[0], diminish_light);
    Surface front_right(Point{center_x - width / 2, center_y + height / 2, center_z + depth / 2, 1.0f},
                        Point{center_x + width / 2, center_y - height / 2, center_z + depth / 2, 1.0f},
                        Point{center_x + width / 2, center_y + height / 2, center_z + depth / 2, 1.0f}, colors[0], diminish_light);
    Surface rear_left(Point{center_x - width / 2, center_y - height / 2, center_z - (translate_clip + depth / 2), 1.0f},
                      Point{center_x - width / 2, center_y + height / 2, center_z - (translate_clip + depth / 2), 1.0f},
                      Point{center_x + width / 2, center_y + height / 2, center_z - (translate_clip + depth / 2), 1.0f}, colors[1], diminish_light);
    Surface rear_right(Point{center_x - width / 2, center_y - height / 2, center_z - depth / 2, 1.0f},
                       Point{center_x + width / 2, center_y - height / 2, center_z - depth / 2, 1.0f},
                       Point{center_x + width / 2, center_y + height / 2, center_z - depth / 2, 1.0f}, colors[1], diminish_light);
    Surface left_near(Point{center_x - (translate_clip + width / 2), center_y - height / 2, center_z + depth / 2, 1.0f},
                      Point{center_x - (translate_clip + width / 2), center_y + height / 2, center_z + depth / 2, 1.0f},
                      Point{center_x - (translate_clip + width / 2), center_y - height / 2, center_z - depth / 2, 1.0f}, colors[2], diminish_light);
    Surface left_far(Point{center_x - (translate_clip + width / 2), center_y - height / 2, center_z - depth / 2, 1.0f},
                     Point{center_x - (translate_clip + width / 2), center_y + height / 2, center_z - depth / 2, 1.0f},
                     Point{center_x - (translate_clip + width / 2), center_y + height / 2, center_z + depth / 2, 1.0f}, colors[2], diminish_light);
    Surface right_near(Point{center_x + (translate_clip + width / 2), center_y - height / 2, center_z + depth / 2, 1.0f},
                       Point{center_x + (translate_clip + width / 2), center_y + height / 2, center_z + depth / 2, 1.0f},
                       Point{center_x + (translate_clip + width / 2), center_y + height / 2, center_z - depth / 2, 1.0f}, colors[3], diminish_light);
    Surface right_far(Point{center_x + (translate_clip + width / 2), center_y - height / 2, center_z - depth / 2, 1.0f},
                      Point{center_x + (translate_clip + width / 2), center_y + height / 2, center_z - depth / 2, 1.0f},
                      Point{center_x + (translate_clip + width / 2), center_y - height / 2, center_z + depth / 2, 1.0f}, colors[3], diminish_light);
    Surface top_near(Point{center_x - width / 2, center_y + (translate_clip + height / 2), center_z + depth / 2, 1.0f},
                     Point{center_x - width / 2, center_y + (translate_clip + height / 2), center_z - depth / 2, 1.0f},
                     Point{center_x + width / 2, center_y + (translate_clip + height / 2), center_z + depth / 2, 1.0f}, colors[4], diminish_light);
    Surface top_far(Point{center_x - width / 2, center_y + (translate_clip + height / 2), center_z - depth / 2, 1.0f},
                    Point{center_x + width / 2, center_y + (translate_clip + height / 2), center_z - depth / 2, 1.0f},
                    Point{center_x + width / 2, center_y + (translate_clip + height / 2), center_z + depth / 2, 1.0f}, colors[4], diminish_light);
    Surface bottom_near(Point{center_x - width / 2, center_y - (translate_clip + height / 2), center_z + depth / 2, 1.0f},
                        Point{center_x + width / 2, center_y - (translate_clip + height / 2), center_z + depth / 2, 1.0f},
                        Point{center_x + width / 2, center_y - (translate_clip + height / 2), center_z - depth / 2, 1.0f}, colors[5], diminish_light);
    Surface bottom_far(Point{center_x - width / 2, center_y - (translate_clip + height / 2), center_z + depth / 2, 1.0f},
                       Point{center_x - width / 2, center_y - (translate_clip + height / 2), center_z - depth / 2, 1.0f},
                       Point{center_x + width / 2, center_y - (translate_clip + height / 2), center_z - depth / 2, 1.0f}, colors[5], diminish_light);

    surfaces.push_back(front_left);
    surfaces.push_back(front_right);
    surfaces.push_back(rear_left);
    surfaces.push_back(rear_right);
    surfaces.push_back(left_near);
    surfaces.push_back(left_far);
    surfaces.push_back(right_near);
    surfaces.push_back(right_far);
    surfaces.push_back(bottom_near);
    surfaces.push_back(bottom_far);
    surfaces.push_back(top_near);
    surfaces.push_back(top_far);
}

void RectPrism::translate(float dx, float dy, float dz)
{
    for (auto &surface : surfaces)
    {
        surface.translate(dx, dy, dz);
    }
}

vector<Surface> &RectPrism::get_surfaces()
{
    return surfaces;
}

#endif