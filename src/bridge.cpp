#include "bridge.hpp"

Bridge::Bridge(const float &_x, const float &_y, const float &_z, const float &_rol,
               const float &_pit, const float &_yaw, const string &_rot)
    : Shape(_x, _y, _z, 0.0f, 0.0f, 0.0f, {}, false, {}),
      roll(_rol), pitch(_pit), yaw(_yaw), rot_order(_rot)
{
    make_shape();
}

Bridge::Bridge(const Bridge &h) : Shape(h)
{
    yaw = h.yaw;
    pitch = h.pitch;
    roll = h.roll;
    rot_order = h.rot_order;
    make_shape();
}

Bridge &Bridge::operator=(const Bridge &h)
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

void Bridge::make_shape()
{
    // Bridge position x, y, z is location of center of bottom of exterior pillars
    // roll = rotation about x-axis
    // pitch = rotation about y-axis
    // yaw = rotation about z-axis

    // Initialize vectors to store shapes of each type
    vector<RectPrism> rect_prisms;

    // Reserve space for vectors
    rect_prisms.reserve(17);

    // Four exterior pillars (left near, right near, left far, right far)
    rect_prisms.push_back(RectPrism(-1.3f, 0.9f, 3.4f, 0.5f, 1.8f, 0.5f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"}));
    rect_prisms.push_back(RectPrism(1.3f, 0.9f, 3.4f, 0.5f, 1.8f, 0.5f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"}));
    rect_prisms.push_back(RectPrism(-1.3f, 0.9f, -3.4f, 0.5f, 1.8f, 0.5f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"}));
    rect_prisms.push_back(RectPrism(1.3f, 0.9f, -3.4f, 0.5f, 1.8f, 0.5f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"}));
    for (auto &rp : rect_prisms)
    {
        rp.set_texture_properties("gray_rock", 0.5f, 0.5f * 1.8f / 0.5f, "front");
        rp.set_texture_properties("gray_rock", 0.5f, 0.5f * 1.8f / 0.5f, "rear");
        rp.set_texture_properties("gray_rock", 0.5f, 0.5f * 1.8f / 0.5f, "left");
        rp.set_texture_properties("gray_rock", 0.5f, 0.5f * 1.8f / 0.5f, "right");
        rp.set_texture_properties("gray_rock", 0.5f, 0.5f, "top");
    }

    // near walking surface
    rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 3.0f, 0.2f, 2.25f, {NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, NIGHTGRAY}));
    rect_prisms.back().rotate(20.0f, 0.0f, 0.0f, "roll-pitch-yaw");
    rect_prisms.back().translate(0.0f, 0.5f, 2.5f);
    rect_prisms.back().set_texture_properties("stone", 3.0f, 3.0f * 3.0f / 2.25f, "top");

    // far walking surface
    rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 3.0f, 0.2f, 2.25f, {NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, NIGHTGRAY}));
    rect_prisms.back().rotate(-20.0f, 0.0f, 0.0f, "roll-pitch-yaw");
    rect_prisms.back().translate(0.0f, 0.5f, -2.5f);
    rect_prisms.back().set_texture_properties("stone", 3.0f, 3.0f * 3.0f / 2.25f, "top");

    // mid walking surface
    rect_prisms.push_back(RectPrism(0.0f, 0.89f, 0.0f, 3.0f, 0.2f, 3.0f, {NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, NIGHTGRAY}));
    rect_prisms.back().set_texture_properties("stone", 3.0f, 3.0f * 3.0f / 2.25f, "top");

    // Four mid support pillars (left near, right near, left far, right far)
    rect_prisms.push_back(RectPrism(-1.34f, 1.6f, 1.5f, 0.3f, 1.5f, 0.3f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"}));
    rect_prisms.push_back(RectPrism(1.34f, 1.6f, 1.5f, 0.3f, 1.5f, 0.3f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"}));
    rect_prisms.push_back(RectPrism(-1.34f, 1.6f, -1.5f, 0.3f, 1.5f, 0.3f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"}));
    rect_prisms.push_back(RectPrism(1.34f, 1.6f, -1.5f, 0.3f, 1.5f, 0.3f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"}));
    for (size_t i{rect_prisms.size() - 4}; i < rect_prisms.size(); ++i)
    {
        rect_prisms[i].set_texture_properties("gray_rock", 0.5f, 0.5 * 1.5f / 0.3f, "front");
        rect_prisms[i].set_texture_properties("gray_rock", 0.5f, 0.5 * 1.5f / 0.3f, "rear");
        rect_prisms[i].set_texture_properties("gray_rock", 0.5f, 0.5 * 1.5f / 0.3f, "left");
        rect_prisms[i].set_texture_properties("gray_rock", 0.5f, 0.5 * 1.5f / 0.3f, "right");
        rect_prisms[i].set_texture_properties("gray_rock", 0.5f, 0.5, "top");
    }

    // Two mid bars (left and right)
    rect_prisms.push_back(RectPrism(-1.35f, 2.15f, 0.0f, 0.29f, 0.3f, 2.7f, {{}, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}, false, {"front", "rear"}));
    rect_prisms.push_back(RectPrism(1.35f, 2.15f, 0.0f, 0.29f, 0.3f, 2.7f, {{}, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}, false, {"front", "rear"}));
    for (size_t i{rect_prisms.size() - 2}; i < rect_prisms.size(); ++i)
    {
        rect_prisms[i].set_texture_properties("dark_gray_rock", 1.0f, 2.7f / 0.3f, "top");
        rect_prisms[i].set_texture_properties("dark_gray_rock", 1.0f, 2.7f / 0.3f, "bottom");
        rect_prisms[i].set_texture_properties("dark_gray_rock", 2.7f / 0.3f, 1.0f, "left");
        rect_prisms[i].set_texture_properties("dark_gray_rock", 2.7f / 0.3f, 1.0f, "right");
    }

    // Near bar (left)
    rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 0.29f, 0.3f, 2.2f, {{}, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}, false, {"front", "rear"}));
    rect_prisms.back().rotate(20.0f, 0.0f, 0.0f, "roll-pitch-yaw");
    rect_prisms.back().translate(-1.34f, 1.80f, 2.5f);

    // Near bar (right)
    rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 0.29f, 0.3f, 2.2f, {{}, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}, false, {"front", "rear"}));
    rect_prisms.back().rotate(20.0f, 0.0f, 0.0f, "roll-pitch-yaw");
    rect_prisms.back().translate(1.34f, 1.80f, 2.5f);

    // Far bar (left)
    rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 0.29f, 0.3f, 2.2f, {{}, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}, false, {"front", "rear"}));
    rect_prisms.back().rotate(-20.0f, 0.0f, 0.0f, "roll-pitch-yaw");
    rect_prisms.back().translate(-1.34f, 1.80f, -2.5f);

    // Far bar (right)
    rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 0.29f, 0.3f, 2.2f, {{}, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}, false, {"front", "rear"}));
    rect_prisms.back().rotate(-20.0f, 0.0f, 0.0f, "roll-pitch-yaw");
    rect_prisms.back().translate(1.34f, 1.80f, -2.5f);

    for (size_t i{rect_prisms.size() - 4}; i < rect_prisms.size(); ++i)
    {
        rect_prisms[i].set_texture_properties("dark_gray_rock", 1.0f, 2.2f / 0.3f, "top");
        rect_prisms[i].set_texture_properties("dark_gray_rock", 1.0f, 2.2f / 0.3f, "bottom");
        rect_prisms[i].set_texture_properties("dark_gray_rock", 2.2f / 0.3f, 1.0f, "left");
        rect_prisms[i].set_texture_properties("dark_gray_rock", 2.2f / 0.3f, 1.0f, "right");
    }

    // Populate the surfaces vector with all surfaces
    vector<Surface> shape_surfaces;
    for (auto &shape : rect_prisms)
    {
        shape_surfaces.clear();
        shape_surfaces = shape.get_surfaces();
        surfaces.insert(surfaces.end(), shape_surfaces.begin(), shape_surfaces.end());
    }

    // apply rotations
    rotate(roll, pitch, yaw, rot_order);

    // apply translations
    translate(x, y, z);
}