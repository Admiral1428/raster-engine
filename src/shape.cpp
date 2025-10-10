#include "shape.hpp"

Shape::Shape() {}
Shape::Shape(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
             const vector<Color> &_colors, const bool &_dim_light, const vector<string> &_skip_surfs)
    : x(_x), y(_y), z(_z), width(_w), height(_h), depth(_d), colors(_colors), diminish_light(_dim_light), skip_surfaces(_skip_surfs) {}

Shape::Shape(const Shape &r)
{
    x = r.x;
    y = r.y;
    z = r.z;
    width = r.width;
    height = r.height;
    depth = r.depth;
    colors = r.colors;
    diminish_light = r.diminish_light;
    skip_surfaces = r.skip_surfaces;
}

Shape::~Shape() {}

Shape &Shape::operator=(const Shape &r)
{
    if (this != &r)
    {
        x = r.x;
        y = r.y;
        z = r.z;
        width = r.width;
        height = r.height;
        depth = r.depth;
        colors = r.colors;
        diminish_light = r.diminish_light;
        skip_surfaces = r.skip_surfaces;
    }
    return *this;
}

void Shape::translate(const float &dx, const float &dy, const float &dz)
{
    for (auto &surface : surfaces)
    {
        surface.translate(dx, dy, dz);
    }
}

void Shape::rotate(const float &roll, const float &pitch, const float &yaw, const string &order)
{
    for (auto &surface : surfaces)
    {
        surface.rotate(roll, pitch, yaw, order);
    }
}

vector<Surface> &Shape::get_surfaces()
{
    return surfaces;
}