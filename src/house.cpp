#include "house.hpp"

House::House(const float &_x, const float &_y, const float &_z, const float &_rol,
             const float &_pit, const float &_yaw, const string &_rot)
    : Shape(_x, _y, _z, 0.0f, 0.0f, 0.0f, {}, false, {}),
      roll(_rol), pitch(_pit), yaw(_yaw), rot_order(_rot)
{
    make_shape();
}

House::House(const House &h) : Shape(h)
{
    yaw = h.yaw;
    pitch = h.pitch;
    roll = h.roll;
    rot_order = h.rot_order;
    make_shape();
}

House &House::operator=(const House &h)
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

void House::make_shape()
{
    // House position x, y, z is location of center of bottom
    // roll = rotation about x-axis
    // pitch = rotation about y-axis
    // yaw = rotation about z-axis

    // Initialize vectors to store shapes of each type
    vector<RectPrism> rect_prisms;
    vector<OctPrism> oct_prisms;
    vector<Rect> rects;
    vector<Surface> triangles;

    // Reserve space for vectors
    rect_prisms.reserve(7);
    oct_prisms.reserve(1);
    rects.reserve(3);
    triangles.reserve(8);

    // exterior walls
    rect_prisms.push_back(RectPrism(0.0f, 2.0f, 0.0f, 7.0f, 4.0f, 4.0f, {WHITE, WHITE, GRAY, GRAY, {}, {}}, false, {"top", "bottom"}));
    rect_prisms.back().set_texture_properties("siding", 1.0f, 12.0f, "front");
    rect_prisms.back().set_texture_properties("siding", 1.0f, 12.0f, "rear");
    rect_prisms.back().set_texture_properties("siding", 1.0f, 12.0f, "left");
    rect_prisms.back().set_texture_properties("siding", 1.0f, 12.0f, "right");

    // attic (left and right)
    triangles.push_back(Surface(Eigen::Vector4f(-3.5f, 4.0f, -2.0f, 1.0f), Eigen::Vector4f(-3.5f, 5.8f, 0.0f, 1.0f), Eigen::Vector4f(-3.5f, 4.0f, 2.0f, 1.0f), {GRAY}, false));
    triangles.back().set_texture_properties("siding", Eigen::Vector2f(1.0f, 6.0f), Eigen::Vector2f(0.5f, 0.0f), Eigen::Vector2f(0.0f, 6.0f));

    triangles.push_back(Surface(Eigen::Vector4f(3.5f, 4.0f, 2.0f, 1.0f), Eigen::Vector4f(3.5f, 5.8f, 0.0f, 1.0f), Eigen::Vector4f(3.5f, 4.0f, -2.0f, 1.0f), {GRAY}, false));
    triangles.back().set_texture_properties("siding", Eigen::Vector2f(1.0f, 6.0f), Eigen::Vector2f(0.5f, 0.0f), Eigen::Vector2f(0.0f, 6.0f));

    // near side of roof
    rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 8.0f, 0.20f, 4.0f, {NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}));
    rect_prisms.back().rotate(38.6f, 0.0f, 0.0f, "roll-pitch-yaw");
    rect_prisms.back().translate(0.0f, 4.5f, 1.5f);
    rect_prisms.back().set_texture_properties("roof", 5.0f, 5.0f, "top");

    // far side of roof
    rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 8.0f, 0.20f, 4.0f, {NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}));
    rect_prisms.back().rotate(-38.6f, 0.0f, 0.0f, "roll-pitch-yaw");
    rect_prisms.back().translate(0.0f, 4.5f, -1.5f);
    rect_prisms.back().set_texture_properties("roof", 5.0f, 5.0f, "top");

    // front windows (left and right)
    rects.push_back(Rect(-2.0f, 2.2f, 2.01f, 1.5f, 1.4f, 0.0f, {SKY_BLUE}));
    rects.back().set_texture_properties("window", 1.0f, 1.0f);

    rects.push_back(Rect(2.0f, 2.2f, 2.01f, 1.5f, 1.4f, 0.0f, {SKY_BLUE}));
    rects.back().set_texture_properties("window", 1.0f, 1.0f);

    // front door
    rects.push_back(Rect(0.0f, 2.0f, 2.01f, 1.5f, 3.0f, 0.0f, {GRAY}));
    rects.back().set_texture_properties("door", 1.0f, 1.0f);

    // front door knob
    oct_prisms.push_back(OctPrism(-0.45f, 2.0f, 2.075f, 0.2f, 0.2, 0.15f, {BLACK, NIGHTGRAY}, false, {"rear"}));

    // front steps (lower and upper)
    rect_prisms.push_back(RectPrism(0.0f, 0.125f, 3.0f, 2.5f, 0.25f, 2.0f, {NIGHTGRAY, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, {}}, false, {"rear", "bottom"}));
    rect_prisms.back().set_texture_properties("stone", 5.0f, 5.0f, "top");

    rect_prisms.push_back(RectPrism(0.0f, 0.375f, 2.75f, 1.75f, 0.25f, 1.5f, {NIGHTGRAY, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, {}}, false, {"rear", "bottom"}));
    rect_prisms.back().set_texture_properties("stone", 4.0f, 4.0f, "top");

    // chimney (lower and upper section)
    rect_prisms.push_back(RectPrism(2.0f, 6.0f, 0.0f, 1.2f, 1.8f, 1.2f, {RED, RED, RED, RED, {}, {}}, false, {"top", "bottom"}));
    rect_prisms.back().set_texture_properties("brick", 2.0f, 3.0f, "front");
    rect_prisms.back().set_texture_properties("brick", 2.0f, 3.0f, "rear");
    rect_prisms.back().set_texture_properties("brick", 2.0f, 3.0f, "left");
    rect_prisms.back().set_texture_properties("brick", 2.0f, 3.0f, "right");

    rect_prisms.push_back(RectPrism(2.0f, 7.0f, 0.0f, 1.5f, 0.6f, 1.5f, {GRAY, GRAY, GRAY, GRAY, BLACK, DKGRAY}));
    rect_prisms.back().set_texture_properties("metal", 1.0f, 1.0f, "front");
    rect_prisms.back().set_texture_properties("metal", 1.0f, 1.0f, "rear");
    rect_prisms.back().set_texture_properties("metal", 1.0f, 1.0f, "left");
    rect_prisms.back().set_texture_properties("metal", 1.0f, 1.0f, "right");

    // Populate the surfaces vector with all surfaces
    vector<Surface> shape_surfaces;
    for (auto &shape : rect_prisms)
    {
        shape_surfaces.clear();
        shape_surfaces = shape.get_surfaces();
        surfaces.insert(surfaces.end(), shape_surfaces.begin(), shape_surfaces.end());
    }
    for (auto &shape : oct_prisms)
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