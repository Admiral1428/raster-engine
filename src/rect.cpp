#include "rect.hpp"

Rect::Rect(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
           const vector<Color> &_colors, const bool &_dim_light, const vector<string> &_skip_surf)
    : Shape(_x, _y, _z, _w, _h, _d, _colors, _dim_light, _skip_surf)
{
    make_shape();
}

Rect::Rect(const Rect &r) : Shape(r)
{
    make_shape();
}

Rect &Rect::operator=(const Rect &r)
{
    if (this != &r)
    {
        Shape::operator=(r);
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

        // x, y, z all at shape center

        // Flat rectangle aligned with depth-height plane (normal facing +x right)
        if (width == 0.0f)
        {
            first_half = Surface(Eigen::Vector4f(x, y - height / 2, z + depth / 2, 1.0f),
                                 Eigen::Vector4f(x, y + height / 2, z + depth / 2, 1.0f),
                                 Eigen::Vector4f(x, y - height / 2, z - depth / 2, 1.0f), colors[0], diminish_light);
            second_half = Surface(Eigen::Vector4f(x, y - height / 2, z - depth / 2, 1.0f),
                                  Eigen::Vector4f(x, y + height / 2, z + depth / 2, 1.0f),
                                  Eigen::Vector4f(x, y + height / 2, z - depth / 2, 1.0f), colors[0], diminish_light);
        }
        // Flat rectangle aligned with width-depth plane (normal facing +y up)
        else if (height == 0.0f)
        {
            first_half = Surface(Eigen::Vector4f(x + width / 2, y, z - depth / 2, 1.0f),
                                 Eigen::Vector4f(x + width / 2, y, z + depth / 2, 1.0f),
                                 Eigen::Vector4f(x - width / 2, y, z + depth / 2, 1.0f), colors[0], diminish_light);
            second_half = Surface(Eigen::Vector4f(x - width / 2, y, z + depth / 2, 1.0f),
                                  Eigen::Vector4f(x - width / 2, y, z - depth / 2, 1.0f),
                                  Eigen::Vector4f(x + width / 2, y, z - depth / 2, 1.0f), colors[0], diminish_light);
        }
        // Flat rectangle aligned with width-height plane (normal facing +z out)
        else if (depth == 0.0f)
        {
            first_half = Surface(Eigen::Vector4f(x + width / 2, y + height / 2, z, 1.0f),
                                 Eigen::Vector4f(x + width / 2, y - height / 2, z, 1.0f),
                                 Eigen::Vector4f(x - width / 2, y - height / 2, z, 1.0f), colors[0], diminish_light);
            second_half = Surface(Eigen::Vector4f(x - width / 2, y - height / 2, z, 1.0f),
                                  Eigen::Vector4f(x - width / 2, y + height / 2, z, 1.0f),
                                  Eigen::Vector4f(x + width / 2, y + height / 2, z, 1.0f), colors[0], diminish_light);
        }

        surfaces.push_back(first_half);
        surfaces.push_back(second_half);
    }
}