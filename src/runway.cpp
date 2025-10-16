#include "runway.hpp"

Runway::Runway(const float &_x, const float &_y, const float &_z, const string _size,
               const float &_rol, const float &_pit, const float &_yaw, const string _rot)
    : Shape(_x, _y, _z, 0.0f, 0.0f, 0.0f, {}, false, {}),
      size(_size), roll(_rol), pitch(_pit), yaw(_yaw), rot_order(_rot)
{
    make_shape();
}

Runway::Runway(const Runway &t) : Shape(t)
{
    size = t.size;
    yaw = t.yaw;
    pitch = t.pitch;
    roll = t.roll;
    rot_order = t.rot_order;
    make_shape();
}

Runway &Runway::operator=(const Runway &t)
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

void Runway::make_shape()
{
    // Runway position x, y, z is location of center of bottom of trunk
    // roll = rotation about x-axis
    // pitch = rotation about y-axis
    // yaw = rotation about z-axis

    if (size == "normal")
    {
        // Initialize vectors to store shapes of each type
        vector<Rect> rects;

        // Reserve space for vectors
        rects.reserve(20);

        // main surface
        rects.push_back(Rect(0.0f, 0.0f, 0.0f, 40.0f, 0.0f, 5.0f, {NIGHTGRAY}, true));

        // threshold markings (left side)
        rects.push_back(Rect(-18.0f, 0.01f, -0.5f, 2.0f, 0.0f, 0.5f, {WHITE}));
        rects.push_back(Rect(-18.0f, 0.01f, -1.5f, 2.0f, 0.0f, 0.5f, {WHITE}));
        rects.push_back(Rect(-18.0f, 0.01f, 0.5f, 2.0f, 0.0f, 0.5f, {WHITE}));
        rects.push_back(Rect(-18.0f, 0.01f, 1.5f, 2.0f, 0.0f, 0.5f, {WHITE}));

        // threshold markings (right side)
        rects.push_back(Rect(18.0f, 0.01f, -0.5f, 2.0f, 0.0f, 0.5f, {WHITE}));
        rects.push_back(Rect(18.0f, 0.01f, -1.5f, 2.0f, 0.0f, 0.5f, {WHITE}));
        rects.push_back(Rect(18.0f, 0.01f, 0.5f, 2.0f, 0.0f, 0.5f, {WHITE}));
        rects.push_back(Rect(18.0f, 0.01f, 1.5f, 2.0f, 0.0f, 0.5f, {WHITE}));

        // center markings
        rects.push_back(Rect(0.0f, 0.01f, 0.0f, 2.0f, 0.0f, 0.25f, {WHITE}));
        rects.push_back(Rect(-3.0f, 0.01f, 0.0f, 2.0f, 0.0f, 0.25f, {WHITE}));
        rects.push_back(Rect(-6.0f, 0.01f, 0.0f, 2.0f, 0.0f, 0.25f, {WHITE}));
        rects.push_back(Rect(-9.0f, 0.01f, 0.0f, 2.0f, 0.0f, 0.25f, {WHITE}));
        rects.push_back(Rect(-12.0f, 0.01f, 0.0f, 2.0f, 0.0f, 0.25f, {WHITE}));
        rects.push_back(Rect(-15.0f, 0.01f, 0.0f, 2.0f, 0.0f, 0.25f, {WHITE}));
        rects.push_back(Rect(3.0f, 0.01f, 0.0f, 2.0f, 0.0f, 0.25f, {WHITE}));
        rects.push_back(Rect(6.0f, 0.01f, 0.0f, 2.0f, 0.0f, 0.25f, {WHITE}));
        rects.push_back(Rect(9.0f, 0.01f, 0.0f, 2.0f, 0.0f, 0.25f, {WHITE}));
        rects.push_back(Rect(12.0f, 0.01f, 0.0f, 2.0f, 0.0f, 0.25f, {WHITE}));
        rects.push_back(Rect(15.0f, 0.01f, 0.0f, 2.0f, 0.0f, 0.25f, {WHITE}));

        // Populate the surfaces vector with all surfaces
        vector<Surface> shape_surfaces;
        for (auto &shape : rects)
        {
            shape_surfaces.clear();
            shape_surfaces = shape.get_surfaces();
            surfaces.insert(surfaces.end(), shape_surfaces.begin(), shape_surfaces.end());
        }
    }

    // apply rotations
    rotate(roll, pitch, yaw, rot_order);

    // apply translations
    translate(x, y, z);
}