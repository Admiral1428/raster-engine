#include "pyramid.hpp"

Pyramid::Pyramid(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
                 const vector<Color> &_colors, const bool &_dim_light)
    : Shape(_x, _y, _z, _w, _h, _d, _colors, _dim_light)
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

    Surface front(Eigen::Vector4f(x - width / 2, y, z + depth / 2, 1.0f),
                  Eigen::Vector4f(x + width / 2, y, z + depth / 2, 1.0f),
                  Eigen::Vector4f(x, y + height, z, 1.0f), colors[0], diminish_light);
    Surface rear(Eigen::Vector4f(x - width / 2, y, z - (translate_clip + depth / 2), 1.0f),
                 Eigen::Vector4f(x + width / 2, y, z - (translate_clip + depth / 2), 1.0f),
                 Eigen::Vector4f(x, y + height, (z - translate_clip), 1.0f), colors[1], diminish_light);
    Surface left(Eigen::Vector4f(x - (translate_clip + width / 2), y, z + depth / 2, 1.0f),
                 Eigen::Vector4f(x - (translate_clip + width / 2), y, z - depth / 2, 1.0f),
                 Eigen::Vector4f(x - translate_clip, y + height, z, 1.0f), colors[2], diminish_light);
    Surface right(Eigen::Vector4f(x + (translate_clip + width / 2), y, z + depth / 2, 1.0f),
                  Eigen::Vector4f(x + (translate_clip + width / 2), y, z - depth / 2, 1.0f),
                  Eigen::Vector4f(x + translate_clip, y + height, z, 1.0f), colors[3], diminish_light);
    Surface bottom_near(Eigen::Vector4f(x - width / 2, y - translate_clip, z + depth / 2, 1.0f),
                        Eigen::Vector4f(x + width / 2, y - translate_clip, z + depth / 2, 1.0f),
                        Eigen::Vector4f(x + width / 2, y - translate_clip, z - depth / 2, 1.0f), colors[4], diminish_light);
    Surface bottom_far(Eigen::Vector4f(x - width / 2, y - translate_clip, z + depth / 2, 1.0f),
                       Eigen::Vector4f(x - width / 2, y - translate_clip, z - depth / 2, 1.0f),
                       Eigen::Vector4f(x + width / 2, y - translate_clip, z - depth / 2, 1.0f), colors[4], diminish_light);

    surfaces.push_back(front);
    surfaces.push_back(rear);
    surfaces.push_back(left);
    surfaces.push_back(right);
    surfaces.push_back(bottom_near);
    surfaces.push_back(bottom_far);
}