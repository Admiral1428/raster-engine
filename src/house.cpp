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
    vector<Rect> rects;
    vector<Surface> triangles;

    // Reserve space for vectors
    rect_prisms.reserve(8);
    triangles.reserve(8);

    // exterior walls
    rect_prisms.push_back(RectPrism(0.0f, 2.0f, 0.0f, 7.0f, 4.0f, 4.0f, {WHITE, WHITE, GRAY, GRAY, {}, {}}, false, {"top", "bottom"}));

    // attic (left and right)
    triangles.push_back(Surface(Eigen::Vector4f(-3.5f, 4.0f, -2.0f, 1.0f), Eigen::Vector4f(-3.5f, 5.8f, 0.0f, 1.0f), Eigen::Vector4f(-3.5f, 4.0f, 2.0f, 1.0f), {GRAY}, false));
    triangles.push_back(Surface(Eigen::Vector4f(3.5f, 4.0f, 2.0f, 1.0f), Eigen::Vector4f(3.5f, 5.8f, 0.0f, 1.0f), Eigen::Vector4f(3.5f, 4.0f, -2.0f, 1.0f), {GRAY}, false));

    // near side of roof
    rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 8.0f, 0.20f, 4.0f, {NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}));
    rect_prisms.back().rotate(38.6f, 0.0f, 0.0f, "roll-pitch-yaw");
    rect_prisms.back().translate(0.0f, 4.5f, 1.5f);

    // far side of roof
    rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 8.0f, 0.20f, 4.0f, {NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}));
    rect_prisms.back().rotate(-38.6f, 0.0f, 0.0f, "roll-pitch-yaw");
    rect_prisms.back().translate(0.0f, 4.5f, -1.5f);

    // front windows (left and right)
    rects.push_back(Rect(-2.0f, 2.2f, 2.01f, 1.5f, 1.4f, 0.0f, {SKY_BLUE}));
    rects.push_back(Rect(2.0f, 2.2f, 2.01f, 1.5f, 1.4f, 0.0f, {SKY_BLUE}));

    // front door
    rects.push_back(Rect(0.0f, 2.0f, 2.01f, 1.5f, 3.0f, 0.0f, {GRAY}));

    // front door knob
    rect_prisms.push_back(RectPrism(-0.5f, 2.0f, 2.075f, 0.25f, 0.25, 0.15f, {DKGRAY, {}, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY}, false, {"rear"}));

    // front steps (lower and upper)
    rect_prisms.push_back(RectPrism(0.0f, 0.125f, 3.0f, 2.5f, 0.25f, 2.0f, {NIGHTGRAY, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, {}}, false, {"rear", "bottom"}));
    rect_prisms.push_back(RectPrism(0.0f, 0.375f, 2.75f, 1.75f, 0.25f, 1.5f, {NIGHTGRAY, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, {}}, false, {"rear", "bottom"}));

    // chimney (lower and upper section)
    rect_prisms.push_back(RectPrism(2.0f, 6.0f, 0.0f, 1.2f, 1.8f, 1.2f, {RED, RED, RED, RED, {}, {}}, false, {"top", "bottom"}));
    rect_prisms.push_back(RectPrism(2.0f, 7.0f, 0.0f, 1.5f, 0.6f, 1.5f, {GRAY, GRAY, GRAY, GRAY, BLACK, DKGRAY}));

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