#include "rectprism.hpp"

RectPrism::RectPrism(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
                     const vector<Color> &_colors, const bool &_dim_light, const vector<string> &_skip_surfs)
    : Shape(_x, _y, _z, _w, _h, _d, _colors, _dim_light, _skip_surfs)
{
    make_shape();
}

RectPrism::RectPrism(const RectPrism &r) : Shape(r)
{
    make_shape();
}

RectPrism &RectPrism::operator=(const RectPrism &r)
{
    if (this != &r)
    {
        Shape::operator=(r);
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

    // x, y, z all at shape center

    // front
    auto check_front = find(skip_surfaces.begin(), skip_surfaces.end(), "front");
    if (check_front == skip_surfaces.end())
    {
        Rect front(x, y, z + 0.5f * depth, width, height, 0.0f, {colors[0]}, diminish_light);
        vector<Surface> front_surfaces = front.get_surfaces();
        surfaces.insert(surfaces.end(), front_surfaces.begin(), front_surfaces.end());
    }

    // rear
    auto check_rear = find(skip_surfaces.begin(), skip_surfaces.end(), "rear");
    if (check_rear == skip_surfaces.end())
    {
        Rect rear(0.0f, 0.0f, 0.0f, width, height, 0.0f, {colors[1]}, diminish_light);
        rear.rotate(180.0f, 0.0f, 0.0f, "roll-pitch-yaw");
        rear.translate(x, y, z - (translate_clip + 0.5f * depth));
        vector<Surface> rear_surfaces = rear.get_surfaces();
        surfaces.insert(surfaces.end(), rear_surfaces.begin(), rear_surfaces.end());
    }

    // right
    auto check_right = find(skip_surfaces.begin(), skip_surfaces.end(), "right");
    if (check_right == skip_surfaces.end())
    {
        Rect right(x + (translate_clip + 0.5f * width), y, z, 0.0f, height, depth, {colors[2]}, diminish_light);
        vector<Surface> right_surfaces = right.get_surfaces();
        surfaces.insert(surfaces.end(), right_surfaces.begin(), right_surfaces.end());
    }

    // left
    auto check_left = find(skip_surfaces.begin(), skip_surfaces.end(), "left");
    if (check_left == skip_surfaces.end())
    {
        Rect left(0.0f, 0.0f, 0.0f, 0.0f, height, depth, {colors[3]}, diminish_light);
        left.rotate(0.0f, 0.0f, 180.0f, "roll-pitch-yaw");
        left.translate(x - (translate_clip + 0.5f * width), y, z);
        vector<Surface> left_surfaces = left.get_surfaces();
        surfaces.insert(surfaces.end(), left_surfaces.begin(), left_surfaces.end());
    }

    // top
    auto check_top = find(skip_surfaces.begin(), skip_surfaces.end(), "top");
    if (check_top == skip_surfaces.end())
    {
        Rect top(x, y + (translate_clip + 0.5f * height), z, width, 0.0f, depth, {colors[4]}, diminish_light);
        vector<Surface> top_surfaces = top.get_surfaces();
        surfaces.insert(surfaces.end(), top_surfaces.begin(), top_surfaces.end());
    }

    // bottom
    auto check_bottom = find(skip_surfaces.begin(), skip_surfaces.end(), "bottom");
    if (check_bottom == skip_surfaces.end())
    {
        Rect bottom(0.0f, 0.0f, 0.0f, width, 0.0f, depth, {colors[5]}, diminish_light);
        bottom.rotate(180.0f, 0.0f, 0.0f, "roll-pitch-yaw");
        bottom.translate(x, y - (translate_clip + 0.5f * height), z);
        vector<Surface> bottom_surfaces = bottom.get_surfaces();
        surfaces.insert(surfaces.end(), bottom_surfaces.begin(), bottom_surfaces.end());
    }
}