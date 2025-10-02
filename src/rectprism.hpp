#ifndef RECTPRISM_HPP
#define RECTPRISM_HPP

#include <vector>
#include <cstdlib>
#include "point.h"
#include "surface.hpp"
#include "constants.h"

using std::vector;

// class defining a triangular RectPrism
class RectPrism
{
private:
    float center_x;
    float center_y;
    float center_z;
    float width;
    float height;
    float depth;
    vector<Surface> surfaces;

public:
    RectPrism(); // default constructor (initializes object to default state with no arguments)
    RectPrism(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d);
    RectPrism(const RectPrism &);            // copy constructor
    ~RectPrism();                            // destructor
    RectPrism &operator=(const RectPrism &); // copy/assignment operator
    void make_shape();
    void translate(float dx, float dy, float dz);
    vector<Surface> &get_surfaces();
};

// implementation
RectPrism::RectPrism() : center_x(0), center_y(0), center_z(0), width(1), height(1), depth(1) {}
RectPrism::RectPrism(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d)
    : center_x(_x), center_y(_y), center_z(_z), width(_w), height(_h), depth(_d)
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
    }
    return *this;
}

void RectPrism::make_shape()
{
    Surface front_left(Point{center_x - width / 2, center_y - height / 2, center_z + depth / 2, 1.0f},
                       Point{center_x - width / 2, center_y + height / 2, center_z + depth / 2, 1.0f},
                       Point{center_x + width / 2, center_y - height / 2, center_z + depth / 2, 1.0f}, RED);
    Surface front_right(Point{center_x - width / 2, center_y + height / 2, center_z + depth / 2, 1.0f},
                        Point{center_x + width / 2, center_y - height / 2, center_z + depth / 2, 1.0f},
                        Point{center_x + width / 2, center_y + height / 2, center_z + depth / 2, 1.0f}, RED);
    Surface rear_left(Point{center_x - width / 2, center_y - height / 2, center_z - depth / 2, 1.0f},
                      Point{center_x - width / 2, center_y + height / 2, center_z - depth / 2, 1.0f},
                      Point{center_x + width / 2, center_y + height / 2, center_z - depth / 2, 1.0f}, MAGENTA);
    Surface rear_right(Point{center_x - width / 2, center_y - height / 2, center_z - depth / 2, 1.0f},
                       Point{center_x + width / 2, center_y - height / 2, center_z - depth / 2, 1.0f},
                       Point{center_x + width / 2, center_y + height / 2, center_z - depth / 2, 1.0f}, MAGENTA);
    Surface left_near(Point{center_x - width / 2, center_y - height / 2, center_z + depth / 2, 1.0f},
                      Point{center_x - width / 2, center_y + height / 2, center_z + depth / 2, 1.0f},
                      Point{center_x - width / 2, center_y - height / 2, center_z - depth / 2, 1.0f}, BLUE);
    Surface left_far(Point{center_x - width / 2, center_y - height / 2, center_z - depth / 2, 1.0f},
                     Point{center_x - width / 2, center_y + height / 2, center_z - depth / 2, 1.0f},
                     Point{center_x - width / 2, center_y + height / 2, center_z + depth / 2, 1.0f}, BLUE);
    Surface right_near(Point{center_x + width / 2, center_y - height / 2, center_z + depth / 2, 1.0f},
                       Point{center_x + width / 2, center_y + height / 2, center_z + depth / 2, 1.0f},
                       Point{center_x + width / 2, center_y + height / 2, center_z - depth / 2, 1.0f}, CYAN);
    Surface right_far(Point{center_x + width / 2, center_y - height / 2, center_z - depth / 2, 1.0f},
                      Point{center_x + width / 2, center_y + height / 2, center_z - depth / 2, 1.0f},
                      Point{center_x + width / 2, center_y - height / 2, center_z + depth / 2, 1.0f}, CYAN);
    Surface bottom_near(Point{center_x - width / 2, center_y - height / 2, center_z + depth / 2, 1.0f},
                        Point{center_x + width / 2, center_y - height / 2, center_z + depth / 2, 1.0f},
                        Point{center_x + width / 2, center_y - height / 2, center_z - depth / 2, 1.0f}, YELLOW);
    Surface bottom_far(Point{center_x - width / 2, center_y - height / 2, center_z + depth / 2, 1.0f},
                       Point{center_x - width / 2, center_y - height / 2, center_z - depth / 2, 1.0f},
                       Point{center_x + width / 2, center_y - height / 2, center_z - depth / 2, 1.0f}, YELLOW);
    Surface top_near(Point{center_x - width / 2, center_y + height / 2, center_z + depth / 2, 1.0f},
                     Point{center_x - width / 2, center_y + height / 2, center_z - depth / 2, 1.0f},
                     Point{center_x + width / 2, center_y + height / 2, center_z + depth / 2, 1.0f}, GREEN);
    Surface top_far(Point{center_x - width / 2, center_y + height / 2, center_z - depth / 2, 1.0f},
                    Point{center_x + width / 2, center_y + height / 2, center_z - depth / 2, 1.0f},
                    Point{center_x + width / 2, center_y + height / 2, center_z + depth / 2, 1.0f}, GREEN);

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