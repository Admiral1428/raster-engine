#include "House.hpp"

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

    // exterior walls
    RectPrism exterior(0.0f, 2.0f, 0.0f, 7.0f, 4.0f, 4.0f, {WHITE, WHITE, GRAY, GRAY, {}, {}}, false, {"top", "bottom"});

    // attic
    Surface left_attic(Eigen::Vector4f(-3.5f, 4.0f, -2.0f, 1.0f), Eigen::Vector4f(-3.5f, 5.8f, 0.0f, 1.0f), Eigen::Vector4f(-3.5f, 4.0f, 2.0f, 1.0f), {GRAY}, false);
    Surface right_attic(Eigen::Vector4f(3.5f, 4.0f, 2.0f, 1.0f), Eigen::Vector4f(3.5f, 5.8f, 0.0f, 1.0f), Eigen::Vector4f(3.5f, 4.0f, -2.0f, 1.0f), {GRAY}, false);

    // near side of roof
    RectPrism roof_near(0.0f, 0.0f, 0.0f, 8.0f, 0.20f, 4.0f, {NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY});
    roof_near.rotate(38.6f, 0.0f, 0.0f, "roll-pitch-yaw");
    roof_near.translate(0.0f, 4.5f, 1.5f);

    // far side of roof
    RectPrism roof_far(0.0f, 0.0f, 0.0f, 8.0f, 0.20f, 4.0f, {NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY});
    roof_far.rotate(-38.6f, 0.0f, 0.0f, "roll-pitch-yaw");
    roof_far.translate(0.0f, 4.5f, -1.5f);

    // front windows
    Rect left_window(-2.0f, 2.2f, 2.01f, 1.5f, 1.4f, 0.0f, {SKY_BLUE});
    Rect right_window(2.0f, 2.2f, 2.01f, 1.5f, 1.4f, 0.0f, {SKY_BLUE});

    // front door
    Rect door(0.0f, 2.0f, 2.01f, 1.5f, 3.0f, 0.0f, {GRAY});

    // front door knob
    RectPrism knob(-0.5f, 2.0f, 2.075f, 0.25f, 0.25, 0.15f, {DKGRAY, {}, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY}, false, {"rear"});

    // front steps
    RectPrism lower_step(0.0f, 0.125f, 3.0f, 2.5f, 0.25f, 2.0f, {NIGHTGRAY, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, {}}, false, {"rear", "bottom"});
    RectPrism upper_step(0.0f, 0.375f, 2.75f, 1.75f, 0.25f, 1.5f, {NIGHTGRAY, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, {}}, false, {"rear", "bottom"});

    vector<Surface> ext_surfaces = exterior.get_surfaces();
    surfaces.insert(surfaces.end(), ext_surfaces.begin(), ext_surfaces.end());
    surfaces.push_back(left_attic);
    surfaces.push_back(right_attic);
    vector<Surface> roof_near_surfaces = roof_near.get_surfaces();
    surfaces.insert(surfaces.end(), roof_near_surfaces.begin(), roof_near_surfaces.end());
    vector<Surface> roof_far_surfaces = roof_far.get_surfaces();
    surfaces.insert(surfaces.end(), roof_far_surfaces.begin(), roof_far_surfaces.end());
    vector<Surface> left_window_surfaces = left_window.get_surfaces();
    surfaces.insert(surfaces.end(), left_window_surfaces.begin(), left_window_surfaces.end());
    vector<Surface> right_window_surfaces = right_window.get_surfaces();
    surfaces.insert(surfaces.end(), right_window_surfaces.begin(), right_window_surfaces.end());
    vector<Surface> door_surfaces = door.get_surfaces();
    surfaces.insert(surfaces.end(), door_surfaces.begin(), door_surfaces.end());
    vector<Surface> knob_surfaces = knob.get_surfaces();
    surfaces.insert(surfaces.end(), knob_surfaces.begin(), knob_surfaces.end());
    vector<Surface> lower_step_surfaces = lower_step.get_surfaces();
    surfaces.insert(surfaces.end(), lower_step_surfaces.begin(), lower_step_surfaces.end());
    vector<Surface> upper_step_surfaces = upper_step.get_surfaces();
    surfaces.insert(surfaces.end(), upper_step_surfaces.begin(), upper_step_surfaces.end());

    // apply rotations
    rotate(roll, pitch, yaw, rot_order);

    // apply translations
    translate(x, y, z);
}