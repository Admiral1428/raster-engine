#include "shape.hpp"

Shape::Shape() : x(0), y(0), z(0), width(1), height(1), depth(1),
                 colors({RED, MAGENTA, BLUE, CYAN, YELLOW}), diminish_light(false) {}
Shape::Shape(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
             const vector<Color> &_colors, const bool &_dim_light)
    : x(_x), y(_y), z(_z), width(_w), height(_h), depth(_d), colors(_colors), diminish_light(_dim_light) {}

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
    }
    return *this;
}

void Shape::translate(float dx, float dy, float dz)
{
    for (auto &surface : surfaces)
    {
        surface.translate(dx, dy, dz);
    }
}

vector<Surface> &Shape::get_surfaces()
{
    return surfaces;
}