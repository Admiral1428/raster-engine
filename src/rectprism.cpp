#include "rectprism.hpp"

RectPrism::RectPrism(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
                     const vector<Color> &_colors, const bool &_dim_light)
    : Shape(_x, _y, _z, _w, _h, _d, _colors, _dim_light)
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

    Surface front_left(Eigen::Vector4f(x - width / 2.0f, y - height / 2.0f, z + depth / 2.0f, 1.0f),
                       Eigen::Vector4f(x - width / 2.0f, y + height / 2.0f, z + depth / 2.0f, 1.0f),
                       Eigen::Vector4f(x + width / 2.0f, y - height / 2.0f, z + depth / 2.0f, 1.0f), colors[0], diminish_light);
    Surface front_right(Eigen::Vector4f(x - width / 2.0f, y + height / 2.0f, z + depth / 2.0f, 1.0f),
                        Eigen::Vector4f(x + width / 2.0f, y - height / 2.0f, z + depth / 2.0f, 1.0f),
                        Eigen::Vector4f(x + width / 2.0f, y + height / 2.0f, z + depth / 2.0f, 1.0f), colors[0], diminish_light);
    Surface rear_left(Eigen::Vector4f(x - width / 2.0f, y - height / 2.0f, z - (translate_clip + depth / 2.0f), 1.0f),
                      Eigen::Vector4f(x - width / 2.0f, y + height / 2.0f, z - (translate_clip + depth / 2.0f), 1.0f),
                      Eigen::Vector4f(x + width / 2.0f, y + height / 2.0f, z - (translate_clip + depth / 2.0f), 1.0f), colors[1], diminish_light);
    Surface rear_right(Eigen::Vector4f(x - width / 2.0f, y - height / 2.0f, z - depth / 2.0f, 1.0f),
                       Eigen::Vector4f(x + width / 2.0f, y - height / 2.0f, z - depth / 2.0f, 1.0f),
                       Eigen::Vector4f(x + width / 2.0f, y + height / 2.0f, z - depth / 2.0f, 1.0f), colors[1], diminish_light);
    Surface left_near(Eigen::Vector4f(x - (translate_clip + width / 2.0f), y - height / 2.0f, z + depth / 2.0f, 1.0f),
                      Eigen::Vector4f(x - (translate_clip + width / 2.0f), y + height / 2.0f, z + depth / 2.0f, 1.0f),
                      Eigen::Vector4f(x - (translate_clip + width / 2.0f), y - height / 2.0f, z - depth / 2.0f, 1.0f), colors[2], diminish_light);
    Surface left_far(Eigen::Vector4f(x - (translate_clip + width / 2.0f), y - height / 2.0f, z - depth / 2.0f, 1.0f),
                     Eigen::Vector4f(x - (translate_clip + width / 2.0f), y + height / 2.0f, z - depth / 2.0f, 1.0f),
                     Eigen::Vector4f(x - (translate_clip + width / 2.0f), y + height / 2.0f, z + depth / 2.0f, 1.0f), colors[2], diminish_light);
    Surface right_near(Eigen::Vector4f(x + (translate_clip + width / 2.0f), y - height / 2.0f, z + depth / 2.0f, 1.0f),
                       Eigen::Vector4f(x + (translate_clip + width / 2.0f), y + height / 2.0f, z + depth / 2.0f, 1.0f),
                       Eigen::Vector4f(x + (translate_clip + width / 2.0f), y + height / 2.0f, z - depth / 2.0f, 1.0f), colors[3], diminish_light);
    Surface right_far(Eigen::Vector4f(x + (translate_clip + width / 2.0f), y - height / 2.0f, z - depth / 2.0f, 1.0f),
                      Eigen::Vector4f(x + (translate_clip + width / 2.0f), y + height / 2.0f, z - depth / 2.0f, 1.0f),
                      Eigen::Vector4f(x + (translate_clip + width / 2.0f), y - height / 2.0f, z + depth / 2.0f, 1.0f), colors[3], diminish_light);
    Surface top_near(Eigen::Vector4f(x - width / 2.0f, y + (translate_clip + height / 2.0f), z + depth / 2.0f, 1.0f),
                     Eigen::Vector4f(x - width / 2.0f, y + (translate_clip + height / 2.0f), z - depth / 2.0f, 1.0f),
                     Eigen::Vector4f(x + width / 2.0f, y + (translate_clip + height / 2.0f), z + depth / 2.0f, 1.0f), colors[4], diminish_light);
    Surface top_far(Eigen::Vector4f(x - width / 2.0f, y + (translate_clip + height / 2.0f), z - depth / 2.0f, 1.0f),
                    Eigen::Vector4f(x + width / 2.0f, y + (translate_clip + height / 2.0f), z - depth / 2.0f, 1.0f),
                    Eigen::Vector4f(x + width / 2.0f, y + (translate_clip + height / 2.0f), z + depth / 2.0f, 1.0f), colors[4], diminish_light);
    Surface bottom_near(Eigen::Vector4f(x - width / 2.0f, y - (translate_clip + height / 2.0f), z + depth / 2.0f, 1.0f),
                        Eigen::Vector4f(x + width / 2.0f, y - (translate_clip + height / 2.0f), z + depth / 2.0f, 1.0f),
                        Eigen::Vector4f(x + width / 2.0f, y - (translate_clip + height / 2.0f), z - depth / 2.0f, 1.0f), colors[5], diminish_light);
    Surface bottom_far(Eigen::Vector4f(x - width / 2.0f, y - (translate_clip + height / 2.0f), z + depth / 2.0f, 1.0f),
                       Eigen::Vector4f(x - width / 2.0f, y - (translate_clip + height / 2.0f), z - depth / 2.0f, 1.0f),
                       Eigen::Vector4f(x + width / 2.0f, y - (translate_clip + height / 2.0f), z - depth / 2.0f, 1.0f), colors[5], diminish_light);

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