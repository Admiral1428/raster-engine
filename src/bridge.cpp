#include "bridge.hpp"

Bridge::Bridge(const float &_x, const float &_y, const float &_z, const float &_rol,
               const float &_pit, const float &_yaw, const string _rot)
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

    // Four exterior pillars
    RectPrism left_near_pillar(-1.3f, 0.9f, 3.4f, 0.5f, 1.8f, 0.5f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"});
    RectPrism right_near_pillar(1.3f, 0.9f, 3.4f, 0.5f, 1.8f, 0.5f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"});
    RectPrism left_far_pillar(-1.3f, 0.9f, -3.4f, 0.5f, 1.8f, 0.5f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"});
    RectPrism right_far_pillar(1.3f, 0.9f, -3.4f, 0.5f, 1.8f, 0.5f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"});

    // near walking surface
    RectPrism floor_near(0.0f, 0.0f, 0.0f, 3.0f, 0.2f, 2.25f, {NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, GRAY});
    floor_near.rotate(20.0f, 0.0f, 0.0f, "roll-pitch-yaw");
    floor_near.translate(0.0f, 0.5f, 2.5f);

    // far walking surface
    RectPrism floor_far(0.0f, 0.0f, 0.0f, 3.0f, 0.2f, 2.25f, {NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, GRAY});
    floor_far.rotate(-20.0f, 0.0f, 0.0f, "roll-pitch-yaw");
    floor_far.translate(0.0f, 0.5f, -2.5f);

    // mid walking surface
    RectPrism floor_mid(0.0f, 0.89f, 0.0f, 3.0f, 0.2f, 3.00f, {GRAY, GRAY, NIGHTGRAY, NIGHTGRAY, GRAY, GRAY});

    // Four mid support pillars
    RectPrism left_near_pole(-1.35f, 1.6f, 1.5f, 0.3f, 1.5f, 0.3f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"});
    RectPrism right_near_pole(1.35f, 1.6f, 1.5f, 0.3f, 1.5f, 0.3f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"});
    RectPrism left_far_pole(-1.35f, 1.6f, -1.5f, 0.3f, 1.5f, 0.3f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"});
    RectPrism right_far_pole(1.35f, 1.6f, -1.5f, 0.3f, 1.5f, 0.3f, {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"});

    // Two mid bars
    RectPrism left_mid_bar(-1.35f, 2.15f, 0.0f, 0.3f, 0.3f, 2.7f, {{}, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}, false, {"front", "rear"});
    RectPrism right_mid_bar(1.35f, 2.15f, 0.0f, 0.3f, 0.3f, 2.7f, {{}, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}, false, {"front", "rear"});

    // Two near bars
    RectPrism left_near_bar(0.0f, 0.0f, 0.0f, 0.3f, 0.3f, 2.2f, {{}, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}, false, {"front", "rear"});
    left_near_bar.rotate(20.0f, 0.0f, 0.0f, "roll-pitch-yaw");
    left_near_bar.translate(-1.35f, 1.80f, 2.5f);

    RectPrism right_near_bar(0.0f, 0.0f, 0.0f, 0.3f, 0.3f, 2.2f, {{}, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}, false, {"front", "rear"});
    right_near_bar.rotate(20.0f, 0.0f, 0.0f, "roll-pitch-yaw");
    right_near_bar.translate(1.35f, 1.80f, 2.5f);

    // Two far bars
    RectPrism left_far_bar(0.0f, 0.0f, 0.0f, 0.3f, 0.3f, 2.2f, {{}, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}, false, {"front", "rear"});
    left_far_bar.rotate(-20.0f, 0.0f, 0.0f, "roll-pitch-yaw");
    left_far_bar.translate(-1.35f, 1.80f, -2.5f);

    RectPrism right_far_bar(0.0f, 0.0f, 0.0f, 0.3f, 0.3f, 2.2f, {{}, {}, NIGHTGRAY, NIGHTGRAY, DKGRAY, DKGRAY}, false, {"front", "rear"});
    right_far_bar.rotate(-20.0f, 0.0f, 0.0f, "roll-pitch-yaw");
    right_far_bar.translate(1.35f, 1.80f, -2.5f);

    vector<Surface> left_near_pillar_surfaces = left_near_pillar.get_surfaces();
    surfaces.insert(surfaces.end(), left_near_pillar_surfaces.begin(), left_near_pillar_surfaces.end());
    vector<Surface> right_near_pillar_surfaces = right_near_pillar.get_surfaces();
    surfaces.insert(surfaces.end(), right_near_pillar_surfaces.begin(), right_near_pillar_surfaces.end());
    vector<Surface> left_far_pillar_surfaces = left_far_pillar.get_surfaces();
    surfaces.insert(surfaces.end(), left_far_pillar_surfaces.begin(), left_far_pillar_surfaces.end());
    vector<Surface> right_far_pillar_surfaces = right_far_pillar.get_surfaces();
    surfaces.insert(surfaces.end(), right_far_pillar_surfaces.begin(), right_far_pillar_surfaces.end());
    vector<Surface> floor_near_surfaces = floor_near.get_surfaces();
    surfaces.insert(surfaces.end(), floor_near_surfaces.begin(), floor_near_surfaces.end());
    vector<Surface> floor_far_surfaces = floor_far.get_surfaces();
    surfaces.insert(surfaces.end(), floor_far_surfaces.begin(), floor_far_surfaces.end());
    vector<Surface> floor_mid_surfaces = floor_mid.get_surfaces();
    surfaces.insert(surfaces.end(), floor_mid_surfaces.begin(), floor_mid_surfaces.end());
    vector<Surface> left_near_pole_surfaces = left_near_pole.get_surfaces();
    surfaces.insert(surfaces.end(), left_near_pole_surfaces.begin(), left_near_pole_surfaces.end());
    vector<Surface> right_near_pole_surfaces = right_near_pole.get_surfaces();
    surfaces.insert(surfaces.end(), right_near_pole_surfaces.begin(), right_near_pole_surfaces.end());
    vector<Surface> left_far_pole_surfaces = left_far_pole.get_surfaces();
    surfaces.insert(surfaces.end(), left_far_pole_surfaces.begin(), left_far_pole_surfaces.end());
    vector<Surface> right_far_pole_surfaces = right_far_pole.get_surfaces();
    surfaces.insert(surfaces.end(), right_far_pole_surfaces.begin(), right_far_pole_surfaces.end());
    vector<Surface> left_mid_bar_surfaces = left_mid_bar.get_surfaces();
    surfaces.insert(surfaces.end(), left_mid_bar_surfaces.begin(), left_mid_bar_surfaces.end());
    vector<Surface> right_mid_bar_surfaces = right_mid_bar.get_surfaces();
    surfaces.insert(surfaces.end(), right_mid_bar_surfaces.begin(), right_mid_bar_surfaces.end());
    vector<Surface> left_near_bar_surfaces = left_near_bar.get_surfaces();
    surfaces.insert(surfaces.end(), left_near_bar_surfaces.begin(), left_near_bar_surfaces.end());
    vector<Surface> right_near_bar_surfaces = right_near_bar.get_surfaces();
    surfaces.insert(surfaces.end(), right_near_bar_surfaces.begin(), right_near_bar_surfaces.end());
    vector<Surface> left_far_bar_surfaces = left_far_bar.get_surfaces();
    surfaces.insert(surfaces.end(), left_far_bar_surfaces.begin(), left_far_bar_surfaces.end());
    vector<Surface> right_far_bar_surfaces = right_far_bar.get_surfaces();
    surfaces.insert(surfaces.end(), right_far_bar_surfaces.begin(), right_far_bar_surfaces.end());

    // apply rotations
    rotate(roll, pitch, yaw, rot_order);

    // apply translations
    translate(x, y, z);
}