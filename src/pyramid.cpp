#include "pyramid.hpp"

Pyramid::Pyramid(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
                 const vector<Color> &_colors, const bool &_dim_light, const vector<string> &_skip_surfs)
    : Shape(_x, _y, _z, _w, _h, _d, _colors, _dim_light, _skip_surfs)
{
    make_shape();
}

Pyramid::Pyramid(const Pyramid &p) : Shape(p)
{
    make_shape();
}

Pyramid &Pyramid::operator=(const Pyramid &p)
{
    if (this != &p)
    {
        Shape::operator=(p);
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

    // for this shape, x and z are at shape center
    // y is at bottom surface center

    // front surface of pyramid
    auto check_front = find(skip_surfaces.begin(), skip_surfaces.end(), "front");
    if (check_front == skip_surfaces.end())
    {
        Surface front(Eigen::Vector4f(x, y + height, z, 1.0f),
                      Eigen::Vector4f(x + width / 2, y, z + depth / 2, 1.0f),
                      Eigen::Vector4f(x - width / 2, y, z + depth / 2, 1.0f), colors[0], diminish_light);
        surfaces.push_back(front);
    }

    // rear surface of pyramid
    auto check_rear = find(skip_surfaces.begin(), skip_surfaces.end(), "rear");
    if (check_rear == skip_surfaces.end())
    {
        Surface rear(Eigen::Vector4f(x - width / 2, y, z - (translate_clip + depth / 2), 1.0f),
                     Eigen::Vector4f(x + width / 2, y, z - (translate_clip + depth / 2), 1.0f),
                     Eigen::Vector4f(x, y + height, (z - translate_clip), 1.0f), colors[1], diminish_light);
        surfaces.push_back(rear);
    }

    // left surface of pyramid
    auto check_left = find(skip_surfaces.begin(), skip_surfaces.end(), "left");
    if (check_left == skip_surfaces.end())
    {
        Surface left(Eigen::Vector4f(x - (translate_clip + width / 2), y, z + depth / 2, 1.0f),
                     Eigen::Vector4f(x - (translate_clip + width / 2), y, z - depth / 2, 1.0f),
                     Eigen::Vector4f(x - translate_clip, y + height, z, 1.0f), colors[2], diminish_light);
        auto check_front = find(skip_surfaces.begin(), skip_surfaces.end(), "front");
        surfaces.push_back(left);
    }

    // right surface of pyramid
    auto check_right = find(skip_surfaces.begin(), skip_surfaces.end(), "right");
    if (check_right == skip_surfaces.end())
    {
        Surface right(Eigen::Vector4f(x + translate_clip, y + height, z, 1.0f),
                      Eigen::Vector4f(x + (translate_clip + width / 2), y, z - depth / 2, 1.0f),
                      Eigen::Vector4f(x + (translate_clip + width / 2), y, z + depth / 2, 1.0f), colors[3], diminish_light);
        surfaces.push_back(right);
    }

    // bottom surface of pyramid (a rectangle)
    auto check_bottom = find(skip_surfaces.begin(), skip_surfaces.end(), "bottom");
    if (check_bottom == skip_surfaces.end())
    {
        Rect bottom(0.0f, 0.0f, 0.0f, width, 0.0f, depth, {colors[4]}, diminish_light);
        bottom.rotate(180.0f, 0.0f, 0.0f, "roll-pitch-yaw");
        bottom.translate(x, y - translate_clip, z);
        vector<Surface> bottom_surfaces = bottom.get_surfaces();
        surfaces.insert(surfaces.end(), bottom_surfaces.begin(), bottom_surfaces.end());
    }
}