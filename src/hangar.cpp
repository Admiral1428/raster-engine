#include "Hangar.hpp"

Hangar::Hangar(const float &_x, const float &_y, const float &_z, const float &_rol,
               const float &_pit, const float &_yaw, const string &_rot)
    : Shape(_x, _y, _z, 0.0f, 0.0f, 0.0f, {}, false, {}),
      roll(_rol), pitch(_pit), yaw(_yaw), rot_order(_rot)
{
    make_shape();
}

Hangar::Hangar(const Hangar &h) : Shape(h)
{
    yaw = h.yaw;
    pitch = h.pitch;
    roll = h.roll;
    rot_order = h.rot_order;
    make_shape();
}

Hangar &Hangar::operator=(const Hangar &h)
{
    if (this != &h)
    {
        Shape::operator=(h);
        yaw = h.yaw;
        pitch = h.pitch;
        roll = h.roll;
        rot_order = h.rot_order;
        make_shape();
    }
    return *this;
}

void Hangar::make_shape()
{
    // Hangar position x, y, z is location of center of bottom
    // roll = rotation about x-axis
    // pitch = rotation about y-axis
    // yaw = rotation about z-axis

    // Initialize vectors to store shapes of each type
    vector<RectPrism> rect_prisms;
    vector<Rect> rects;
    vector<Surface> triangles;

    // Reserve space for vectors
    rect_prisms.reserve(4);
    rects.reserve(4);
    triangles.reserve(2);

    // floor
    rects.push_back(Rect(0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 7.0f, {DKGRAY}));
    rects.back().set_texture_properties("dark_gray_rock", 10.0f, 7.0f);

    // exterior walls (left, right)
    rect_prisms.push_back(RectPrism(-5.0f, 3.0f, 0.0f, 0.4f, 6.0f, 7.0f, {WHITE, GRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"}));
    rect_prisms.back().set_texture_properties("bright_stone", 6.0f, 7.0f, "left");
    rect_prisms.back().set_texture_properties("stone", 6.0f, 7.0f, "right");
    rect_prisms.back().set_texture_properties("metal", 1.0f, 1.0f, "front");
    rect_prisms.back().set_texture_properties("metal", 1.0f, 1.0f, "rear");

    rect_prisms.push_back(RectPrism(5.0f, 3.0f, 0.0f, 0.4f, 6.0f, 7.0f, {WHITE, GRAY, GRAY, NIGHTGRAY, {}}, false, {"bottom"}));
    rect_prisms.back().set_texture_properties("bright_stone", 6.0f, 7.0f, "right");
    rect_prisms.back().set_texture_properties("stone", 6.0f, 7.0f, "left");
    rect_prisms.back().set_texture_properties("metal", 1.0f, 1.0f, "front");
    rect_prisms.back().set_texture_properties("metal", 1.0f, 1.0f, "rear");

    // back lower wall (near, far)
    rects.push_back(Rect(0.0f, 3.0f, -3.4f, 9.8f, 6.0f, 0.0f, {DKGRAY}));
    rects.back().set_texture_properties("stone", 10.0f, 6.0f);

    rects.push_back(Rect(0.0f, 0.0f, 0.0f, 9.8f, 6.0f, 0.0f, {GRAY}));
    rects.back().rotate(0.0f, 180.0f, 0.0f, "roll-pitch-yaw");
    rects.back().translate(0.0f, 3.0f, -3.51f);
    rects.back().set_texture_properties("bright_stone", 10.0f, 6.0f);

    // back upper wall (near, far)
    triangles.push_back(Surface(Eigen::Vector4f(-5.0f, 6.0f, -3.4f, 1.0f), Eigen::Vector4f(0.0f, 8.5f, -3.4f, 1.0f), Eigen::Vector4f(5.0f, 6.0f, -3.4f, 1.0f), {DKGRAY}));
    triangles.back().set_texture_properties("stone", Eigen::Vector2f(0.0f, 2.5f), Eigen::Vector2f(5.0f, 0.0f), Eigen::Vector2f(10.0f, 2.5f));

    triangles.push_back(Surface(Eigen::Vector4f(5.0f, 6.0f, -3.51f, 1.0f), Eigen::Vector4f(0.0f, 8.5f, -3.51f, 1.0f), Eigen::Vector4f(-5.0f, 6.0f, -3.51f, 1.0f), {GRAY}));
    triangles.back().set_texture_properties("bright_stone", Eigen::Vector2f(10.0f, 2.5f), Eigen::Vector2f(5.0f, 0.0f), Eigen::Vector2f(0.0f, 2.5f));

    // left roof
    rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 6.92f, 0.4f, 7.5f, {WHITE, WHITE, NIGHTGRAY, GRAY, GRAY, NIGHTGRAY}));
    rect_prisms.back().rotate(0.0f, 0.0f, 27.0f, "roll-pitch-yaw");
    rect_prisms.back().translate(-3.0f, 7.1f, 0.01f);
    rect_prisms.back().set_texture_properties("metal_horz", 1.0f, 1.0f, "front");
    rect_prisms.back().set_texture_properties("metal_horz", 1.0f, 1.0f, "rear");
    rect_prisms.back().set_texture_properties("metal_horz", 1.0f, 1.0f, "left");
    rect_prisms.back().set_texture_properties("roof", 7.0f, 7.5f, "top");
    rect_prisms.back().set_texture_properties("ceiling", 1.0f, 10.0f, "bottom");

    // right roof
    rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 6.92f, 0.4f, 7.5f, {WHITE, WHITE, GRAY, NIGHTGRAY, GRAY, NIGHTGRAY}));
    rect_prisms.back().rotate(0.0f, 0.0f, -27.0f, "roll-pitch-yaw");
    rect_prisms.back().translate(3.0f, 7.1f, 0.0f);
    rect_prisms.back().set_texture_properties("metal_horz", 1.0f, 1.0f, "front");
    rect_prisms.back().set_texture_properties("metal_horz", 1.0f, 1.0f, "rear");
    rect_prisms.back().set_texture_properties("metal_horz", 1.0f, 1.0f, "right");
    rect_prisms.back().set_texture_properties("roof", 7.0f, 7.5f, "top");
    rect_prisms.back().set_texture_properties("ceiling", 1.0f, 10.0f, "bottom");

    // front taxiway
    rects.push_back(Rect(0.0f, 0.0f, 7.5f, 8.0f, 0.0f, 8.0f, {NIGHTGRAY}, true));
    rects.back().set_texture_properties("gray_rock", 8.0f, 8.0f);

    // Populate the surfaces vector with all surfaces
    vector<Surface> shape_surfaces;
    for (auto &shape : rect_prisms)
    {
        shape_surfaces.clear();
        shape_surfaces = shape.get_surfaces();
        surfaces.insert(surfaces.end(), shape_surfaces.begin(), shape_surfaces.end());
    }
    for (auto &shape : rects)
    {
        shape_surfaces.clear();
        shape_surfaces = shape.get_surfaces();
        surfaces.insert(surfaces.end(), shape_surfaces.begin(), shape_surfaces.end());
    }
    for (auto &shape : triangles)
    {
        surfaces.push_back(shape);
    }

    // apply rotations
    rotate(roll, pitch, yaw, rot_order);

    // apply translations
    translate(x, y, z);
}