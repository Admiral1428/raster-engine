#include "Tree.hpp"

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

    if (size == "small")
    {
        RectPrism trunk(0.0f, 1.0f, 0.0f, 0.5f, 2.0f, 0.5f, {BROWN, BROWN, DKBROWN, DKBROWN, {}, {}},
                        false, {"top", "bottom"});
        Pyramid leaves(0.0f, 2.0f, 0.0f, 2.0f, 2.0f, 2.0f, {DKGREEN, DKGREEN, MEDGREEN, MEDGREEN, BLACK});

        vector<Surface> trunk_surfaces = trunk.get_surfaces();
        surfaces.insert(surfaces.end(), trunk_surfaces.begin(), trunk_surfaces.end());
        vector<Surface> leaves_surfaces = leaves.get_surfaces();
        surfaces.insert(surfaces.end(), leaves_surfaces.begin(), leaves_surfaces.end());
    }
    else if (size == "medium")
    {
        RectPrism trunk(0.0f, 2.0f, 0.0f, 0.75f, 4.0f, 0.75f, {BROWN, BROWN, DKBROWN, DKBROWN, {}, {}},
                        false, {"top", "bottom"});
        Pyramid leaves(0.0f, 4.0f, 0.0f, 3.0f, 3.0f, 3.0f, {DKGREEN, DKGREEN, MEDGREEN, MEDGREEN, BLACK});

        vector<Surface> trunk_surfaces = trunk.get_surfaces();
        surfaces.insert(surfaces.end(), trunk_surfaces.begin(), trunk_surfaces.end());
        vector<Surface> leaves_surfaces = leaves.get_surfaces();
        surfaces.insert(surfaces.end(), leaves_surfaces.begin(), leaves_surfaces.end());
    }
    else if (size == "large")
    {
        RectPrism trunk(0.0f, 1.0f, 0.0f, 1.0f, 2.0f, 1.0f, {BROWN, BROWN, DKBROWN, DKBROWN, {}, {}},
                        false, {"top", "bottom"});
        Pyramid leaves_low(0.0f, 2.0f, 0.0f, 4.0f, 4.0f, 4.0f, {DKGREEN, DKGREEN, MEDGREEN, MEDGREEN, BLACK});
        Pyramid leaves_mid(0.0f, 4.0f, 0.0f, 3.0f, 3.0f, 3.0f, {DKGREEN, DKGREEN, MEDGREEN, MEDGREEN, BLACK});
        Pyramid leaves_high(0.0f, 5.75f, 0.0f, 2.0f, 2.0f, 2.0f, {DKGREEN, DKGREEN, MEDGREEN, MEDGREEN, BLACK});

        vector<Surface> trunk_surfaces = trunk.get_surfaces();
        surfaces.insert(surfaces.end(), trunk_surfaces.begin(), trunk_surfaces.end());
        vector<Surface> leaves_low_surfaces = leaves_low.get_surfaces();
        surfaces.insert(surfaces.end(), leaves_low_surfaces.begin(), leaves_low_surfaces.end());
        vector<Surface> leaves_mid_surfaces = leaves_mid.get_surfaces();
        surfaces.insert(surfaces.end(), leaves_mid_surfaces.begin(), leaves_mid_surfaces.end());
        vector<Surface> leaves_high_surfaces = leaves_high.get_surfaces();
        surfaces.insert(surfaces.end(), leaves_high_surfaces.begin(), leaves_high_surfaces.end());
    }

    // apply rotations
    rotate(roll, pitch, yaw, rot_order);

    // apply translations
    translate(x, y, z);
}