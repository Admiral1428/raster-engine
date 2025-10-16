#include "octprism.hpp"

OctPrism::OctPrism(const float &_x, const float &_y, const float &_z, const float &_w, const float &_h, const float &_d,
                   const vector<Color> &_colors, const bool &_dim_light, const vector<string> &_skip_surfs)
    : Shape(_x, _y, _z, _w, _h, _d, _colors, _dim_light, _skip_surfs)
{
    make_shape();
}

OctPrism::OctPrism(const OctPrism &r) : Shape(r)
{
    make_shape();
}

OctPrism &OctPrism::operator=(const OctPrism &r)
{
    if (this != &r)
    {
        Shape::operator=(r);
        make_shape();
    }
    return *this;
}

void OctPrism::make_shape()
{
    float translate_clip = TOL_SHIFT_SURFACE;

    // shift rear surface into page to avoid z-fighting
    // shift front surface out of page to avoid z-fighting

    // x, y, z all at shape center

    // Define 8 vertices in clockwise order
    vector<vector<float>> ver;
    ver.push_back({0.5f * width * (2.0f - sqrt(2.0f)), 0.5f * height}); // top right
    ver.push_back({0.5f * width, 0.5f * height * (2.0f - sqrt(2.0f))});
    ver.push_back({0.5f * width, -0.5f * height * (2.0f - sqrt(2.0f))});
    ver.push_back({0.5f * width * (2.0f - sqrt(2.0f)), -0.5f * height});
    ver.push_back({-0.5f * width * (2.0f - sqrt(2.0f)), -0.5f * height});
    ver.push_back({-0.5f * width, -0.5f * height * (2.0f - sqrt(2.0f))});
    ver.push_back({-0.5f * width, 0.5f * height * (2.0f - sqrt(2.0f))});
    ver.push_back({-0.5f * width * (2.0f - sqrt(2.0f)), 0.5f * height}); // top left

    // Create 8 triangles
    Surface tri_01(Eigen::Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
                   Eigen::Vector4f(ver[0][0], ver[0][1], 0.0f, 1.0f),
                   Eigen::Vector4f(ver[1][0], ver[1][1], 0.0f, 1.0f), {colors[0]}, diminish_light);
    Surface tri_12(Eigen::Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
                   Eigen::Vector4f(ver[1][0], ver[1][1], 0.0f, 1.0f),
                   Eigen::Vector4f(ver[2][0], ver[2][1], 0.0f, 1.0f), {colors[0]}, diminish_light);
    Surface tri_23(Eigen::Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
                   Eigen::Vector4f(ver[2][0], ver[2][1], 0.0f, 1.0f),
                   Eigen::Vector4f(ver[3][0], ver[3][1], 0.0f, 1.0f), {colors[0]}, diminish_light);
    Surface tri_34(Eigen::Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
                   Eigen::Vector4f(ver[3][0], ver[3][1], 0.0f, 1.0f),
                   Eigen::Vector4f(ver[4][0], ver[4][1], 0.0f, 1.0f), {colors[0]}, diminish_light);
    Surface tri_45(Eigen::Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
                   Eigen::Vector4f(ver[4][0], ver[4][1], 0.0f, 1.0f),
                   Eigen::Vector4f(ver[5][0], ver[5][1], 0.0f, 1.0f), {colors[0]}, diminish_light);
    Surface tri_56(Eigen::Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
                   Eigen::Vector4f(ver[5][0], ver[5][1], 0.0f, 1.0f),
                   Eigen::Vector4f(ver[6][0], ver[6][1], 0.0f, 1.0f), {colors[0]}, diminish_light);
    Surface tri_67(Eigen::Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
                   Eigen::Vector4f(ver[6][0], ver[6][1], 0.0f, 1.0f),
                   Eigen::Vector4f(ver[7][0], ver[7][1], 0.0f, 1.0f), {colors[0]}, diminish_light);
    Surface tri_70(Eigen::Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
                   Eigen::Vector4f(ver[7][0], ver[7][1], 0.0f, 1.0f),
                   Eigen::Vector4f(ver[0][0], ver[0][1], 0.0f, 1.0f), {colors[0]}, diminish_light);

    // front
    auto check_front = find(skip_surfaces.begin(), skip_surfaces.end(), "front");
    if (check_front == skip_surfaces.end())
    {
        Surface tri_front_01 = tri_01;
        Surface tri_front_12 = tri_12;
        Surface tri_front_23 = tri_23;
        Surface tri_front_34 = tri_34;
        Surface tri_front_45 = tri_45;
        Surface tri_front_56 = tri_56;
        Surface tri_front_67 = tri_67;
        Surface tri_front_70 = tri_70;

        // shift surfaces
        tri_front_01.translate(x, y, z + 0.5f * depth + TOL_SHIFT_SURFACE);
        tri_front_12.translate(x, y, z + 0.5f * depth + TOL_SHIFT_SURFACE);
        tri_front_23.translate(x, y, z + 0.5f * depth + TOL_SHIFT_SURFACE);
        tri_front_34.translate(x, y, z + 0.5f * depth + TOL_SHIFT_SURFACE);
        tri_front_45.translate(x, y, z + 0.5f * depth + TOL_SHIFT_SURFACE);
        tri_front_56.translate(x, y, z + 0.5f * depth + TOL_SHIFT_SURFACE);
        tri_front_67.translate(x, y, z + 0.5f * depth + TOL_SHIFT_SURFACE);
        tri_front_70.translate(x, y, z + 0.5f * depth + TOL_SHIFT_SURFACE);

        surfaces.push_back(tri_front_01);
        surfaces.push_back(tri_front_12);
        surfaces.push_back(tri_front_23);
        surfaces.push_back(tri_front_34);
        surfaces.push_back(tri_front_45);
        surfaces.push_back(tri_front_56);
        surfaces.push_back(tri_front_67);
        surfaces.push_back(tri_front_70);
    }

    // rear
    auto check_rear = find(skip_surfaces.begin(), skip_surfaces.end(), "rear");
    if (check_rear == skip_surfaces.end())
    {
        Surface tri_rear_01 = tri_01;
        Surface tri_rear_12 = tri_12;
        Surface tri_rear_23 = tri_23;
        Surface tri_rear_34 = tri_34;
        Surface tri_rear_45 = tri_45;
        Surface tri_rear_56 = tri_56;
        Surface tri_rear_67 = tri_67;
        Surface tri_rear_70 = tri_70;

        // rotate surfaces to make visible
        tri_rear_01.rotate(180.0f, 0.0f, 0.0f, "roll-pitch-yaw");
        tri_rear_12.rotate(180.0f, 0.0f, 0.0f, "roll-pitch-yaw");
        tri_rear_23.rotate(180.0f, 0.0f, 0.0f, "roll-pitch-yaw");
        tri_rear_34.rotate(180.0f, 0.0f, 0.0f, "roll-pitch-yaw");
        tri_rear_45.rotate(180.0f, 0.0f, 0.0f, "roll-pitch-yaw");
        tri_rear_56.rotate(180.0f, 0.0f, 0.0f, "roll-pitch-yaw");
        tri_rear_67.rotate(180.0f, 0.0f, 0.0f, "roll-pitch-yaw");
        tri_rear_70.rotate(180.0f, 0.0f, 0.0f, "roll-pitch-yaw");

        // shift surfaces
        tri_rear_01.translate(x, y, z - (0.5f * depth + TOL_SHIFT_SURFACE));
        tri_rear_12.translate(x, y, z - (0.5f * depth + TOL_SHIFT_SURFACE));
        tri_rear_23.translate(x, y, z - (0.5f * depth + TOL_SHIFT_SURFACE));
        tri_rear_34.translate(x, y, z - (0.5f * depth + TOL_SHIFT_SURFACE));
        tri_rear_45.translate(x, y, z - (0.5f * depth + TOL_SHIFT_SURFACE));
        tri_rear_56.translate(x, y, z - (0.5f * depth + TOL_SHIFT_SURFACE));
        tri_rear_67.translate(x, y, z - (0.5f * depth + TOL_SHIFT_SURFACE));
        tri_rear_70.translate(x, y, z - (0.5f * depth + TOL_SHIFT_SURFACE));

        surfaces.push_back(tri_rear_01);
        surfaces.push_back(tri_rear_12);
        surfaces.push_back(tri_rear_23);
        surfaces.push_back(tri_rear_34);
        surfaces.push_back(tri_rear_45);
        surfaces.push_back(tri_rear_56);
        surfaces.push_back(tri_rear_67);
        surfaces.push_back(tri_rear_70);
    }

    // outer surfaces
    auto check_outer = find(skip_surfaces.begin(), skip_surfaces.end(), "outer");
    if (check_outer == skip_surfaces.end())
    {
        // rectangle between vertices, front and rear
        Quad rect_01({ver[0][0], ver[0][1], 0.5f * depth}, {ver[0][0], ver[0][1], -0.5f * depth},
                     {ver[1][0], ver[1][1], -0.5f * depth}, {ver[1][0], ver[1][1], 0.5f * depth}, {colors[1]}, diminish_light);

        Quad rect_12({ver[1][0], ver[1][1], 0.5f * depth}, {ver[1][0], ver[1][1], -0.5f * depth},
                     {ver[2][0], ver[2][1], -0.5f * depth}, {ver[2][0], ver[2][1], 0.5f * depth}, {colors[1]}, diminish_light);

        Quad rect_23({ver[2][0], ver[2][1], 0.5f * depth}, {ver[2][0], ver[2][1], -0.5f * depth},
                     {ver[3][0], ver[3][1], -0.5f * depth}, {ver[3][0], ver[3][1], 0.5f * depth}, {colors[1]}, diminish_light);

        Quad rect_34({ver[3][0], ver[3][1], 0.5f * depth}, {ver[3][0], ver[3][1], -0.5f * depth},
                     {ver[4][0], ver[4][1], -0.5f * depth}, {ver[4][0], ver[4][1], 0.5f * depth}, {colors[1]}, diminish_light);

        Quad rect_45({ver[4][0], ver[4][1], 0.5f * depth}, {ver[4][0], ver[4][1], -0.5f * depth},
                     {ver[5][0], ver[5][1], -0.5f * depth}, {ver[5][0], ver[5][1], 0.5f * depth}, {colors[1]}, diminish_light);

        Quad rect_56({ver[5][0], ver[5][1], 0.5f * depth}, {ver[5][0], ver[5][1], -0.5f * depth},
                     {ver[6][0], ver[6][1], -0.5f * depth}, {ver[6][0], ver[6][1], 0.5f * depth}, {colors[1]}, diminish_light);

        Quad rect_67({ver[6][0], ver[6][1], 0.5f * depth}, {ver[6][0], ver[6][1], -0.5f * depth},
                     {ver[7][0], ver[7][1], -0.5f * depth}, {ver[7][0], ver[7][1], 0.5f * depth}, {colors[1]}, diminish_light);

        Quad rect_70({ver[7][0], ver[7][1], 0.5f * depth}, {ver[7][0], ver[7][1], -0.5f * depth},
                     {ver[0][0], ver[0][1], -0.5f * depth}, {ver[0][0], ver[0][1], 0.5f * depth}, {colors[1]}, diminish_light);

        // shift surfaces
        rect_01.translate(x, y, z);
        rect_12.translate(x, y, z);
        rect_23.translate(x, y, z);
        rect_34.translate(x, y, z);
        rect_45.translate(x, y, z);
        rect_56.translate(x, y, z);
        rect_67.translate(x, y, z);
        rect_70.translate(x, y, z);

        vector<Surface> rect_01_surfaces = rect_01.get_surfaces();
        surfaces.insert(surfaces.end(), rect_01_surfaces.begin(), rect_01_surfaces.end());

        vector<Surface> rect_12_surfaces = rect_12.get_surfaces();
        surfaces.insert(surfaces.end(), rect_12_surfaces.begin(), rect_12_surfaces.end());

        vector<Surface> rect_23_surfaces = rect_23.get_surfaces();
        surfaces.insert(surfaces.end(), rect_23_surfaces.begin(), rect_23_surfaces.end());

        vector<Surface> rect_34_surfaces = rect_34.get_surfaces();
        surfaces.insert(surfaces.end(), rect_34_surfaces.begin(), rect_34_surfaces.end());

        vector<Surface> rect_45_surfaces = rect_45.get_surfaces();
        surfaces.insert(surfaces.end(), rect_45_surfaces.begin(), rect_45_surfaces.end());

        vector<Surface> rect_56_surfaces = rect_56.get_surfaces();
        surfaces.insert(surfaces.end(), rect_56_surfaces.begin(), rect_56_surfaces.end());

        vector<Surface> rect_67_surfaces = rect_67.get_surfaces();
        surfaces.insert(surfaces.end(), rect_67_surfaces.begin(), rect_67_surfaces.end());

        vector<Surface> rect_70_surfaces = rect_70.get_surfaces();
        surfaces.insert(surfaces.end(), rect_70_surfaces.begin(), rect_70_surfaces.end());
    }
}