#include "prop.hpp"

Prop::Prop(const float &_x, const float &_y, const float &_z, const string &_size,
           const float &_rol, const float &_pit, const float &_yaw, const string &_rot,
           const float &_rot_speed)
    : Shape(_x, _y, _z, 0.0f, 0.0f, 0.0f, {}, false, {}),
      size(_size), roll(_rol), pitch(_pit), yaw(_yaw), rot_order(_rot), rot_speed(_rot_speed)
{
    make_shape();
}

Prop::Prop(const Prop &a) : Shape(a)
{
    size = a.size;
    yaw = a.yaw;
    pitch = a.pitch;
    roll = a.roll;
    rot_order = a.rot_order;
    rot_speed = a.rot_speed;
    make_shape();
}

Prop &Prop::operator=(const Prop &a)
{
    if (this != &a)
    {
        Shape::operator=(a);
        size = a.size;
        yaw = a.yaw;
        pitch = a.pitch;
        roll = a.roll;
        rot_order = a.rot_order;
        rot_speed = a.rot_speed;
        make_shape();
    }
    return *this;
}

void Prop::make_shape()
{
    // Prop position x, y, z is location of center of bottom of trunk
    // roll = rotation about x-axis
    // pitch = rotation about y-axis
    // yaw = rotation about z-axis

    if (size == "small")
    {
        // Initialize vectors to store shapes of each type
        vector<OctPrism> octs;

        // Reserve space for vectors
        octs.reserve(2);

        // Propeller
        octs.push_back(OctPrism(0.0f, 0.0f, 0.0f, 0.8f, 0.1f, 0.05f, {BLACK, GRAY}));
        octs.back().rotate(0.0f, 90.0f, 0.0f, "roll-pitch-yaw");
        octs.back().translate(0.95f, 0.0f, 0.0f);

        // Spinner
        octs.push_back(OctPrism(0.0f, 0.0f, 0.0f, 0.07f, 0.07f, 0.06f, {GRAY, WHITE}));
        octs.back().rotate(0.0f, 90.0f, 0.0f, "roll-pitch-yaw");
        octs.back().translate(0.98f, 0.0f, 0.0f);

        // Populate the surfaces vector with all surfaces
        vector<Surface> shape_surfaces;
        for (auto &shape : octs)
        {
            shape_surfaces.clear();
            shape_surfaces = shape.get_surfaces();
            surfaces.insert(surfaces.end(), shape_surfaces.begin(), shape_surfaces.end());
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // apply rotations
    rotate(roll, pitch, yaw, rot_order);

    // apply translations
    translate(x, y, z);

    // set flag to indicate that prop has been moved to airplane location
    shifted = true;
}

void Prop::move(const float &frame_dt)
{
    // move back to origin if shift to airplane has occured
    if (shifted)
    {
        string opp_rot_order;

        if (rot_order == "yaw-pitch-roll")
        {
            opp_rot_order = "roll-pitch-yaw";
        }
        else if (rot_order == "yaw-roll-pitch")
        {
            opp_rot_order = "pitch-roll-yaw";
        }
        else if (rot_order == "pitch-yaw-roll")
        {
            opp_rot_order = "roll-yaw-pitch";
        }
        else if (rot_order == "pitch-roll-yaw")
        {
            opp_rot_order = "yaw-roll-pitch";
        }
        else if (rot_order == "roll-yaw-pitch")
        {
            opp_rot_order = "pitch-yaw-roll";
        }
        else if (rot_order == "roll-pitch-yaw")
        {
            opp_rot_order = "yaw-pitch-roll";
        }

        translate(-x, -y, -z);
        rotate(-roll, -pitch, -yaw, opp_rot_order);
    }

    // apply rotation about x axis to achieve "spinning" motion
    rotate(rot_speed * frame_dt, 0.0f, 0.0f, "roll-pitch-yaw");

    // move back to airplane location
    rotate(roll, pitch, yaw, rot_order);
    translate(x, y, z);

    shifted = true;
}