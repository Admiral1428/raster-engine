#include "boat.hpp"

Boat::Boat(const float &_x, const float &_y, const float &_z, const string &_size,
           const float &_rol, const float &_pit, const float &_yaw, const string &_rot,
           const float &_speed)
    : Shape(_x, _y, _z, 0.0f, 0.0f, 0.0f, {}, false, {}),
      size(_size), roll(_rol), pitch(_pit), yaw(_yaw), rot_order(_rot), speed(_speed)
{
    make_shape();
}

Boat::Boat(const Boat &b) : Shape(b)
{
    size = b.size;
    yaw = b.yaw;
    pitch = b.pitch;
    roll = b.roll;
    rot_order = b.rot_order;
    speed = b.speed;
    make_shape();
}

Boat &Boat::operator=(const Boat &b)
{
    if (this != &b)
    {
        Shape::operator=(b);
        size = b.size;
        yaw = b.yaw;
        pitch = b.pitch;
        roll = b.roll;
        rot_order = b.rot_order;
        speed = b.speed;
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
        // Initialize vectors to store shapes of each type
        vector<RectPrism> rect_prisms;
        vector<Surface> triangles;
        vector<Quad> quads;

        // Reserve space for vectors
        rect_prisms.reserve(2);
        triangles.reserve(8);
        quads.reserve(4);

        // Boat base
        rect_prisms.push_back(RectPrism(0.0f, 0.75f, 0.0f, 4.5f, 1.5f, 2.25f, {BROWN, BROWN, {}, {}, NIGHTBROWN, {}},
                                        false, {"left", "right", "bottom"}));
        rect_prisms.back().set_texture_properties("boat", 1.0f, 5.0f, "front");
        rect_prisms.back().set_texture_properties("boat", 1.0f, 5.0f, "rear");

        // Bow (front) wedge (left, right, slope, top)
        triangles.push_back(Surface(Eigen::Vector4f(2.25f, 1.5f, -1.125f, 1.0f),
                                    Eigen::Vector4f(2.25f, 0.0f, -1.125f, 1.0f),
                                    Eigen::Vector4f(3.375f, 1.5f, -1.125f, 1.0f), {BROWN}));
        triangles.back().set_texture_properties("boat", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(0.0f, 5.0f), Eigen::Vector2f(1.0f, 0.0f));

        triangles.push_back(Surface(Eigen::Vector4f(3.375f, 1.5f, 1.125f, 1.0f),
                                    Eigen::Vector4f(2.25f, 0.0f, 1.125f, 1.0f),
                                    Eigen::Vector4f(2.25f, 1.5f, 1.125f, 1.0f), {BROWN}));
        triangles.back().set_texture_properties("boat", Eigen::Vector2f(1.0f, 0.0f), Eigen::Vector2f(0.0f, 5.0f), Eigen::Vector2f(0.0f, 0.0f));

        quads.push_back(Quad({2.25f, 0.0f, 1.125f}, {3.375f, 1.5f, 1.125f}, {3.375f, 1.5f, -1.125f}, {2.25f, 0.0f, -1.125f}, {DKBROWN}));
        quads.back().set_texture_properties("boat_dark", Eigen::Vector2f(0.0f, 5.0f), Eigen::Vector2f(0.0f, 0.0f),
                                            Eigen::Vector2f(1.0f, 0.0f), Eigen::Vector2f(1.0f, 5.0f));

        quads.push_back(Quad({2.25f, 1.5f, 1.125f}, {2.25f, 1.5f, -1.125f}, {3.375f, 1.5f, -1.125f}, {3.375f, 1.5f, 1.125f}, {NIGHTBROWN}));

        // Stern (rear) wedge (left, right, slope, top)
        triangles.push_back(Surface(Eigen::Vector4f(-3.375f, 1.5f, -1.125f, 1.0f),
                                    Eigen::Vector4f(-2.25f, 0.0f, -1.125f, 1.0f),
                                    Eigen::Vector4f(-2.25f, 1.5f, -1.125f, 1.0f), {BROWN}));
        triangles.back().set_texture_properties("boat", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(1.0f, 5.0f), Eigen::Vector2f(1.0f, 0.0f));

        triangles.push_back(Surface(Eigen::Vector4f(-2.25f, 1.5f, 1.125f, 1.0f),
                                    Eigen::Vector4f(-2.25f, 0.0f, 1.125f, 1.0f),
                                    Eigen::Vector4f(-3.375f, 1.5f, 1.125f, 1.0f), {BROWN}));
        triangles.back().set_texture_properties("boat", Eigen::Vector2f(1.0f, 0.0f), Eigen::Vector2f(1.0f, 5.0f), Eigen::Vector2f(0.0f, 0.0f));

        quads.push_back(Quad({-2.25f, 0.0f, -1.125f}, {-3.375f, 1.5f, -1.125f}, {-3.375f, 1.5f, 1.125f}, {-2.25f, 0.0f, 1.125f}, {DKBROWN}));
        quads.back().set_texture_properties("boat_dark", Eigen::Vector2f(0.0f, 5.0f), Eigen::Vector2f(0.0f, 0.0f),
                                            Eigen::Vector2f(1.0f, 0.0f), Eigen::Vector2f(1.0f, 5.0f));

        quads.push_back(Quad({-3.375f, 1.5f, 1.125f}, {-3.375f, 1.5f, -1.125f}, {-2.25f, 1.5f, -1.125f}, {-2.25f, 1.5f, 1.125f}, {NIGHTBROWN}));

        // mast
        rect_prisms.push_back(RectPrism(1.0f, 4.0f, 0.0f, 0.2f, 5.0f, 0.2f,
                                        {DKGRAY, DKGRAY, NIGHTGRAY, NIGHTGRAY, GRAY, {}}, false, {"bottom"}));
        rect_prisms.back().set_texture_properties("metal", 1.0f, 1.0f, "front");
        rect_prisms.back().set_texture_properties("metal", 1.0f, 1.0f, "rear");
        rect_prisms.back().set_texture_properties("metal", 1.0f, 1.0f, "left");
        rect_prisms.back().set_texture_properties("metal", 1.0f, 1.0f, "right");

        // headsail (left and right)
        triangles.push_back(Surface(Eigen::Vector4f(1.1f, 6.3f, 0.0f, 1.0f),
                                    Eigen::Vector4f(2.8f, 1.9f, 0.0f, 1.0f),
                                    Eigen::Vector4f(1.1f, 1.9f, -0.1f, 1.0f), {WHITE}));
        triangles.back().set_texture_properties("cloth", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(5.0f, 6.0f), Eigen::Vector2f(0.0f, 6.0f));

        triangles.push_back(Surface(Eigen::Vector4f(1.1f, 1.9f, 0.1f, 1.0f),
                                    Eigen::Vector4f(2.8f, 1.9f, 0.0f, 1.0f),
                                    Eigen::Vector4f(1.1f, 6.3f, 0.0f, 1.0f), {WHITE}));
        triangles.back().set_texture_properties("cloth", Eigen::Vector2f(0.0f, 6.0f), Eigen::Vector2f(5.0f, 6.0f), Eigen::Vector2f(0.0f, 0.0f));

        // mainsail (left and right)
        triangles.push_back(Surface(Eigen::Vector4f(0.9f, 1.9f, -0.1f, 1.0f),
                                    Eigen::Vector4f(-2.8f, 1.9f, 0.0f, 1.0f),
                                    Eigen::Vector4f(0.9f, 6.3f, 0.0f, 1.0f), {WHITE}));
        triangles.back().set_texture_properties("cloth", Eigen::Vector2f(5.0f, 6.0f), Eigen::Vector2f(0.0f, 6.0f), Eigen::Vector2f(5.0f, 0.0f));

        triangles.push_back(Surface(Eigen::Vector4f(0.9f, 6.3f, 0.0f, 1.0f),
                                    Eigen::Vector4f(-2.8f, 1.9f, 0.0f, 1.0f),
                                    Eigen::Vector4f(0.9f, 1.9f, 0.1f, 1.0f), {WHITE}));
        triangles.back().set_texture_properties("cloth", Eigen::Vector2f(5.0f, 0.0f), Eigen::Vector2f(0.0f, 6.0f), Eigen::Vector2f(5.0f, 6.0f));

        // Populate the surfaces vector with all surfaces
        vector<Surface> shape_surfaces;
        for (auto &shape : rect_prisms)
        {
            shape_surfaces.clear();
            shape_surfaces = shape.get_surfaces();
            surfaces.insert(surfaces.end(), shape_surfaces.begin(), shape_surfaces.end());
        }
        for (auto &shape : triangles)
        {
            surfaces.push_back(shape);
        }
        for (auto &shape : quads)
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