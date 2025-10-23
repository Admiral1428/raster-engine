#include "Quad.hpp"

Quad::Quad(const vector<float> &_p0, const vector<float> &_p1, const vector<float> &_p2, const vector<float> &_p3,
           const vector<Color> &_colors, const bool &_dim_light)
    : Shape(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, _colors, _dim_light, {}), p0(_p0), p1(_p1), p2(_p2), p3(_p3)
{
    make_shape();
}

Quad::Quad(const Quad &r) : Shape(r)
{
    p0 = r.p0;
    p1 = r.p1;
    p2 = r.p2;
    p3 = r.p3;
    make_shape();
}

Quad &Quad::operator=(const Quad &r)
{
    if (this != &r)
    {
        Shape::operator=(r);
        p0 = r.p0;
        p1 = r.p1;
        p2 = r.p2;
        p3 = r.p3;
        make_shape();
    }
    return *this;
}

void Quad::make_shape()
{
    // Use 4 surfaces instead of 2 to minimize distortion when mapping textures
    Surface first;
    Surface second;
    Surface third;
    Surface fourth;

    vector<float> pmid = {(p0[0] + p1[0] + p2[0] + p3[0]) / 4.0f,
                          (p0[1] + p1[1] + p2[1] + p3[1]) / 4.0f,
                          (p0[2] + p1[2] + p2[2] + p3[2]) / 4.0f};

    // p1, p2, mid
    first = Surface(Eigen::Vector4f(p1[0], p1[1], p1[2], 1.0f),
                    Eigen::Vector4f(p2[0], p2[1], p2[2], 1.0f),
                    Eigen::Vector4f(pmid[0], pmid[1], pmid[2], 1.0f), colors[0], diminish_light);

    // p2, p3, mid
    second = Surface(Eigen::Vector4f(p2[0], p2[1], p2[2], 1.0f),
                     Eigen::Vector4f(p3[0], p3[1], p3[2], 1.0f),
                     Eigen::Vector4f(pmid[0], pmid[1], pmid[2], 1.0f), colors[0], diminish_light);

    // p3, p0, mid
    third = Surface(Eigen::Vector4f(p3[0], p3[1], p3[2], 1.0f),
                    Eigen::Vector4f(p0[0], p0[1], p0[2], 1.0f),
                    Eigen::Vector4f(pmid[0], pmid[1], pmid[2], 1.0f), colors[0], diminish_light);

    // p0, p1, mid
    fourth = Surface(Eigen::Vector4f(p0[0], p0[1], p0[2], 1.0f),
                     Eigen::Vector4f(p1[0], p1[1], p1[2], 1.0f),
                     Eigen::Vector4f(pmid[0], pmid[1], pmid[2], 1.0f), colors[0], diminish_light);

    surfaces.push_back(first);
    surfaces.push_back(second);
    surfaces.push_back(third);
    surfaces.push_back(fourth);
}

void Quad::set_texture_properties(const string &texture_name, const Eigen::Vector2f &uv0, const Eigen::Vector2f &uv1,
                                  const Eigen::Vector2f &uv2, const Eigen::Vector2f &uv3)
{
    // Use 4 surfaces instead of 2 to minimize distortion when mapping textures
    Eigen::Vector2f uvmid = Eigen::Vector2f((uv0(0) + uv1(0) + uv2(0) + uv3(0)) / 4.0f,
                                            (uv0(1) + uv1(1) + uv2(1) + uv3(1)) / 4.0f);

    // p1, p2, mid
    surfaces[0].set_texture_properties(texture_name,
                                       Eigen::Vector2f(uv1(0), uv1(1)),
                                       Eigen::Vector2f(uv2(0), uv2(1)),
                                       Eigen::Vector2f(uvmid(0), uvmid(1)));

    // p2, p3, mid
    surfaces[1].set_texture_properties(texture_name,
                                       Eigen::Vector2f(uv2(0), uv2(1)),
                                       Eigen::Vector2f(uv3(0), uv3(1)),
                                       Eigen::Vector2f(uvmid(0), uvmid(1)));

    // p3, p0, mid
    surfaces[2].set_texture_properties(texture_name,
                                       Eigen::Vector2f(uv3(0), uv3(1)),
                                       Eigen::Vector2f(uv0(0), uv0(1)),
                                       Eigen::Vector2f(uvmid(0), uvmid(1)));

    // p0, p1, mid
    surfaces[3].set_texture_properties(texture_name,
                                       Eigen::Vector2f(uv0(0), uv0(1)),
                                       Eigen::Vector2f(uv1(0), uv1(1)),
                                       Eigen::Vector2f(uvmid(0), uvmid(1)));
}