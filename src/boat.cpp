#include "Boat.hpp"

Boat::Boat(const float &_x, const float &_y, const float &_z, const string &_size,
           const float &_rol, const float &_pit, const float &_yaw, const string &_rot,
           const float &_speed)
    : Shape(_x, _y, _z, 0.0f, 0.0f, 0.0f, {}, false, {}),
      size(_size), roll(_rol), pitch(_pit), yaw(_yaw), rot_order(_rot), speed(_speed)
{
    make_shape();
}

Boat::Boat(const Boat &t) : Shape(t)
{
    size = t.size;
    yaw = t.yaw;
    pitch = t.pitch;
    roll = t.roll;
    rot_order = t.rot_order;
    make_shape();
}

Boat &Boat::operator=(const Boat &t)
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

void Boat::make_shape()
{
    // Boat position x, y, z is location of center of bottom of trunk
    // roll = rotation about x-axis
    // pitch = rotation about y-axis
    // yaw = rotation about z-axis

    if (size == "small")
    {
        // Boat base
        RectPrism base(0.0f, 0.75f, 0.0f, 4.5f, 1.5f, 2.25f, {BROWN, BROWN, {}, {}, NIGHTBROWN, {}},
                       false, {"left", "right", "bottom"});

        // Bow wedge (front of boat)
        Surface bow_left(Eigen::Vector4f(2.25f, 1.5f, -1.125f, 1.0f),
                         Eigen::Vector4f(2.25f, 0.0f, -1.125f, 1.0f),
                         Eigen::Vector4f(3.375f, 1.5f, -1.125f, 1.0f), {BROWN});
        Surface bow_right(Eigen::Vector4f(3.375f, 1.5f, 1.125f, 1.0f),
                          Eigen::Vector4f(2.25f, 0.0f, 1.125f, 1.0f),
                          Eigen::Vector4f(2.25f, 1.5f, 1.125f, 1.0f), {BROWN});
        Quad bow_slope({2.25f, 0.0f, -1.125f}, {2.25f, 0.0f, 1.125f}, {3.375f, 1.5f, 1.125f}, {3.375f, 1.5f, -1.125f}, {DKBROWN});
        Quad bow_top({2.25f, 1.5f, 1.125f}, {2.25f, 1.5f, -1.125f}, {3.375f, 1.5f, -1.125f}, {3.375f, 1.5f, 1.125f}, {NIGHTBROWN});

        // Stern wedge (rear of boat)
        Surface stern_left(Eigen::Vector4f(-3.375f, 1.5f, -1.125f, 1.0f),
                           Eigen::Vector4f(-2.25f, 0.0f, -1.125f, 1.0f),
                           Eigen::Vector4f(-2.25f, 1.5f, -1.125f, 1.0f), {BROWN});
        Surface stern_right(Eigen::Vector4f(-2.25f, 1.5f, 1.125f, 1.0f),
                            Eigen::Vector4f(-2.25f, 0.0f, 1.125f, 1.0f),
                            Eigen::Vector4f(-3.375f, 1.5f, 1.125f, 1.0f), {BROWN});
        Quad stern_slope({-3.375f, 1.5f, -1.125f}, {-3.375f, 1.5f, 1.125f}, {-2.25f, 0.0f, 1.125f}, {-2.25f, 0.0f, -1.125f}, {DKBROWN});
        Quad stern_top({-3.375f, 1.5f, 1.125f}, {-3.375f, 1.5f, -1.125f}, {-2.25f, 1.5f, -1.125f}, {-2.25f, 1.5f, 1.125f}, {NIGHTBROWN});

        // mast
        RectPrism mast(1.0f, 4.0f, 0.0f, 0.2f, 5.0f, 0.2f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"});

        // headsail (front bow, smaller triangle)
        Surface head_left(Eigen::Vector4f(1.1f, 6.3f, 0.0f, 1.0f),
                          Eigen::Vector4f(2.8f, 1.9f, 0.0f, 1.0f),
                          Eigen::Vector4f(1.1f, 1.9f, -0.1f, 1.0f), {WHITE});
        Surface head_right(Eigen::Vector4f(1.1f, 1.9f, 0.1f, 1.0f),
                           Eigen::Vector4f(2.8f, 1.9f, 0.0f, 1.0f),
                           Eigen::Vector4f(1.1f, 6.3f, 0.0f, 1.0f), {WHITE});

        // mainsail (rear stern, larger triangle)
        Surface main_left(Eigen::Vector4f(0.9f, 1.9f, -0.1f, 1.0f),
                          Eigen::Vector4f(-2.8f, 1.9f, 0.0f, 1.0f),
                          Eigen::Vector4f(0.9f, 6.3f, 0.0f, 1.0f), {WHITE});
        Surface main_right(Eigen::Vector4f(0.9f, 6.3f, 0.0f, 1.0f),
                           Eigen::Vector4f(-2.8f, 1.9f, 0.0f, 1.0f),
                           Eigen::Vector4f(0.9f, 1.9f, 0.1f, 1.0f), {WHITE});

        vector<Surface> base_surfaces = base.get_surfaces();
        surfaces.insert(surfaces.end(), base_surfaces.begin(), base_surfaces.end());
        surfaces.insert(surfaces.end(), bow_left);
        surfaces.insert(surfaces.end(), bow_right);
        vector<Surface> bow_slope_surfaces = bow_slope.get_surfaces();
        surfaces.insert(surfaces.end(), bow_slope_surfaces.begin(), bow_slope_surfaces.end());
        vector<Surface> bow_top_surfaces = bow_top.get_surfaces();
        surfaces.insert(surfaces.end(), bow_top_surfaces.begin(), bow_top_surfaces.end());
        surfaces.insert(surfaces.end(), stern_left);
        surfaces.insert(surfaces.end(), stern_right);
        vector<Surface> stern_slope_surfaces = stern_slope.get_surfaces();
        surfaces.insert(surfaces.end(), stern_slope_surfaces.begin(), stern_slope_surfaces.end());
        vector<Surface> stern_top_surfaces = stern_top.get_surfaces();
        surfaces.insert(surfaces.end(), stern_top_surfaces.begin(), stern_top_surfaces.end());
        vector<Surface> mast_surfaces = mast.get_surfaces();
        surfaces.insert(surfaces.end(), mast_surfaces.begin(), mast_surfaces.end());
        surfaces.insert(surfaces.end(), head_left);
        surfaces.insert(surfaces.end(), head_right);
        surfaces.insert(surfaces.end(), main_left);
        surfaces.insert(surfaces.end(), main_right);
    }

    // apply rotations
    rotate(roll, pitch, yaw, rot_order);

    // apply translations
    translate(x, y, z);
}

void Boat::move(const float &frame_dt)
{
    // translate surfaces
    translate(0.0f, 0.0f, speed * frame_dt);

    // modify coordinates to track position
    z += speed * frame_dt;

    // turn boat around if edge of map
    if ((z < -185.0f && speed < 0.0f) || (z > 185.0f && speed > 0.0f))
    {
        // reverse direction
        speed = -speed;

        // move back to origin and flip 180 degrees
        translate(-x, -y, -z);
        rotate(0.0f, 180.0f, 0.0f, "roll-pitch-yaw");

        // move back
        translate(x, y, z);
    }
}