#include "tree.hpp"

Tree::Tree(const float &_x, const float &_y, const float &_z, const string _size,
           const float &_rol, const float &_pit, const float &_yaw, const string _rot)
    : Shape(_x, _y, _z, 0.0f, 0.0f, 0.0f, {}, false, {}),
      size(_size), roll(_rol), pitch(_pit), yaw(_yaw), rot_order(_rot)
{
    make_shape();
}

Tree::Tree(const Tree &t) : Shape(t)
{
    size = t.size;
    yaw = t.yaw;
    pitch = t.pitch;
    roll = t.roll;
    rot_order = t.rot_order;
    make_shape();
}

Tree &Tree::operator=(const Tree &t)
{
    if (this != &t)
    {
        Shape::operator=(t);
        size = t.size;
        yaw = t.yaw;
        pitch = t.pitch;
        roll = t.roll;
        rot_order = t.rot_order;
        make_shape();
    }
    return *this;
}

void Tree::make_shape()
{
    // tree position x, y, z is location of center of bottom of trunk
    // roll = rotation about x-axis
    // pitch = rotation about y-axis
    // yaw = rotation about z-axis

    // Initialize vectors to store shapes of each type
    vector<RectPrism> rect_prisms;
    vector<Pyramid> pyramids;

    // Reserve space for vectors
    rect_prisms.reserve(1);
    pyramids.reserve(3);

    if (size == "small")
    {
        // trunk and leaves
        rect_prisms.push_back(RectPrism(0.0f, 1.0f, 0.0f, 0.5f, 2.0f, 0.5f, {BROWN, BROWN, BROWN, BROWN, {}, {}},
                                        false, {"top", "bottom"}));
        rect_prisms.back().set_texture_properties("wood", 1.0f, 4.0f, "front");
        rect_prisms.back().set_texture_properties("wood", 1.0f, 4.0f, "rear");
        rect_prisms.back().set_texture_properties("wood", 1.0f, 4.0f, "left");
        rect_prisms.back().set_texture_properties("wood", 1.0f, 4.0f, "right");

        pyramids.push_back(Pyramid(0.0f, 2.0f, 0.0f, 2.0f, 2.0f, 2.0f, {MEDGREEN, MEDGREEN, MEDGREEN, MEDGREEN, BLACK}));
        pyramids.back().set_texture_properties("leaves", 2.0f, 2.0f, "front");
        pyramids.back().set_texture_properties("leaves", 2.0f, 2.0f, "rear");
        pyramids.back().set_texture_properties("leaves", 2.0f, 2.0f, "left");
        pyramids.back().set_texture_properties("leaves", 2.0f, 2.0f, "right");
    }
    else if (size == "medium")
    {
        // trunk and leaves
        rect_prisms.push_back(RectPrism(0.0f, 2.0f, 0.0f, 0.75f, 4.0f, 0.75f, {BROWN, BROWN, BROWN, BROWN, {}, {}},
                                        false, {"top", "bottom"}));
        rect_prisms.back().set_texture_properties("wood", 1.0f, 4.0f / 0.75f, "front");
        rect_prisms.back().set_texture_properties("wood", 1.0f, 4.0f / 0.75f, "rear");
        rect_prisms.back().set_texture_properties("wood", 1.0f, 4.0f / 0.75f, "left");
        rect_prisms.back().set_texture_properties("wood", 1.0f, 4.0f / 0.75f, "right");

        pyramids.push_back(Pyramid(0.0f, 4.0f, 0.0f, 3.0f, 3.0f, 3.0f, {MEDGREEN, MEDGREEN, MEDGREEN, MEDGREEN, BLACK}));
        pyramids.back().set_texture_properties("leaves", 3.0f, 3.0f, "front");
        pyramids.back().set_texture_properties("leaves", 3.0f, 3.0f, "rear");
        pyramids.back().set_texture_properties("leaves", 3.0f, 3.0f, "left");
        pyramids.back().set_texture_properties("leaves", 3.0f, 3.0f, "right");
    }
    else if (size == "large")
    {
        // trunk
        rect_prisms.push_back(RectPrism(0.0f, 1.0f, 0.0f, 1.0f, 2.0f, 1.0f, {BROWN, BROWN, BROWN, BROWN, {}, {}},
                                        false, {"top", "bottom"}));

        rect_prisms.back().set_texture_properties("wood", 1.0f, 2.0f, "front");
        rect_prisms.back().set_texture_properties("wood", 1.0f, 2.0f, "rear");
        rect_prisms.back().set_texture_properties("wood", 1.0f, 2.0f, "left");
        rect_prisms.back().set_texture_properties("wood", 1.0f, 2.0f, "right");

        // leaves (low, mid, high)
        pyramids.push_back(Pyramid(0.0f, 2.0f, 0.0f, 4.0f, 4.0f, 4.0f, {MEDGREEN, MEDGREEN, MEDGREEN, MEDGREEN, BLACK}));
        pyramids.back().set_texture_properties("leaves", 4.0f, 4.0f, "front");
        pyramids.back().set_texture_properties("leaves", 4.0f, 4.0f, "rear");
        pyramids.back().set_texture_properties("leaves", 4.0f, 4.0f, "left");
        pyramids.back().set_texture_properties("leaves", 4.0f, 4.0f, "right");

        pyramids.push_back(Pyramid(0.0f, 4.0f, 0.0f, 3.0f, 3.0f, 3.0f, {MEDGREEN, MEDGREEN, MEDGREEN, MEDGREEN, BLACK}));
        pyramids.back().set_texture_properties("leaves", 3.0f, 3.0f, "front");
        pyramids.back().set_texture_properties("leaves", 3.0f, 3.0f, "rear");
        pyramids.back().set_texture_properties("leaves", 3.0f, 3.0f, "left");
        pyramids.back().set_texture_properties("leaves", 3.0f, 3.0f, "right");

        pyramids.push_back(Pyramid(0.0f, 5.75f, 0.0f, 2.0f, 2.0f, 2.0f, {MEDGREEN, MEDGREEN, MEDGREEN, MEDGREEN, BLACK}));
        pyramids.back().set_texture_properties("leaves", 2.0f, 2.0f, "front");
        pyramids.back().set_texture_properties("leaves", 2.0f, 2.0f, "rear");
        pyramids.back().set_texture_properties("leaves", 2.0f, 2.0f, "left");
        pyramids.back().set_texture_properties("leaves", 2.0f, 2.0f, "right");
    }

    // Populate the surfaces vector with all surfaces
    vector<Surface> shape_surfaces;
    for (auto &shape : rect_prisms)
    {
        shape_surfaces.clear();
        shape_surfaces = shape.get_surfaces();
        surfaces.insert(surfaces.end(), shape_surfaces.begin(), shape_surfaces.end());
    }
    for (auto &shape : pyramids)
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