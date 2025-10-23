#include "airplane.hpp"

Airplane::Airplane(const float &_x, const float &_y, const float &_z, const string &_size,
                   const float &_rol, const float &_pit, const float &_yaw, const string &_rot,
                   const float &_rot_speed)
    : Shape(_x, _y, _z, 0.0f, 0.0f, 0.0f, {}, false, {}),
      size(_size), roll(_rol), pitch(_pit), yaw(_yaw), rot_order(_rot), rot_speed(_rot_speed)
{
    make_shape();
}

Airplane::Airplane(const Airplane &a) : Shape(a)
{
    size = a.size;
    yaw = a.yaw;
    pitch = a.pitch;
    roll = a.roll;
    rot_order = a.rot_order;
    rot_speed = a.rot_speed;
    make_shape();
}

Airplane &Airplane::operator=(const Airplane &a)
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

void Airplane::make_shape()
{
    // Airplane position x, y, z is location of center of bottom of trunk
    // roll = rotation about x-axis
    // pitch = rotation about y-axis
    // yaw = rotation about z-axis

    if (size == "small")
    {
        // Initialize vectors to store shapes of each type
        vector<RectPrism> rect_prisms;
        vector<Surface> triangles;
        vector<Quad> quads;
        vector<Pyramid> pyramids;
        vector<OctPrism> octs;

        // Reserve space for vectors
        rect_prisms.reserve(7);
        triangles.reserve(8);
        quads.reserve(1);
        pyramids.reserve(1);
        octs.reserve(8);

        // Fuselage (bottom section)
        rect_prisms.push_back(RectPrism(0.0f, 0.0f, 0.0f, 1.5f, 0.5f, 0.5f, {MEDYELLOW, MEDYELLOW, HIGHYELLOW, {}, {}, DKYELLOW},
                                        false, {"left", "top"}));
        rect_prisms.back().set_texture_properties("plane_right", 1.0f, 1.0f, "front");
        rect_prisms.back().set_texture_properties("plane_left", 1.0f, 1.0f, "rear");

        // Fuselage (top section)
        rect_prisms.push_back(RectPrism(-0.25f, 0.45f, 0.0f, 1.0f, 0.4f, 0.5f, {MEDYELLOW, MEDYELLOW, {}, {}, YELLOW, {}},
                                        false, {"left", "right", "bottom"}));
        rect_prisms.back().set_texture_properties("plane", 1.0f, 0.5f, "front");
        rect_prisms.back().set_texture_properties("plane", 1.0f, 0.5f, "rear");

        // Right window
        triangles.push_back(Surface(Eigen::Vector4f(0.25f, 0.25f, 0.25f, 1.0f), Eigen::Vector4f(0.25f, 0.65f, 0.25f, 1.0f),
                                    Eigen::Vector4f(0.75f, 0.25f, 0.25f, 1.0f), BLUE));
        triangles.back().set_texture_properties("plane_glass_side", Eigen::Vector2f(0.0f, 1.0f),
                                                Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(1.0f, 1.0f));

        // Left window
        triangles.push_back(Surface(Eigen::Vector4f(0.75f, 0.25f, -0.25f, 1.0f), Eigen::Vector4f(0.25f, 0.65f, -0.25f, 1.0f),
                                    Eigen::Vector4f(0.25f, 0.25f, -0.25f, 1.0f), BLUE));
        triangles.back().set_texture_properties("plane_glass_side", Eigen::Vector2f(0.0f, 1.0f),
                                                Eigen::Vector2f(1.0f, 0.0f), Eigen::Vector2f(1.0f, 1.0f));

        // Front window
        quads.push_back(Quad({0.75f, 0.25f, 0.25f}, {0.25f, 0.65f, 0.25f},
                             {0.25f, 0.65f, -0.25f}, {0.75f, 0.25f, -0.25f}, {BLUE}));
        quads.back().set_texture_properties("plane_glass", Eigen::Vector2f(0.0f, 1.0f), Eigen::Vector2f(0.0f, 0.0f),
                                            Eigen::Vector2f(1.0f, 0.0f), Eigen::Vector2f(1.0f, 1.0f));

        // Fuselage (nose)
        rect_prisms.push_back(RectPrism(0.8f, 0.0f, 0.0f, 0.25f, 0.35f, 0.3f, {YELLOW, YELLOW, HIGHYELLOW, {}, YELLOW, YELLOW},
                                        false, {"left"}));

        // Engine block
        rect_prisms.push_back(RectPrism(0.83f, 0.0f, 0.0f, 0.12f, 0.1f, 0.35f, {BLACK, BLACK, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY, NIGHTGRAY},
                                        false, {"left"}));
        rect_prisms.back().set_texture_properties("plane_engine", 1.0f, 1.0f, "front");
        rect_prisms.back().set_texture_properties("plane_engine", 1.0f, 1.0f, "rear");

        // Aft fuselage
        pyramids.push_back(Pyramid(0.0f, 0.0f, 0.0f, 0.9f, 1.8f, 0.48f, {MEDYELLOW, MEDYELLOW, DKYELLOW, YELLOW, {}},
                                   false, {"bottom"}));
        pyramids.back().rotate(0.0f, 0.0f, 90.0f, "roll-pitch-yaw");
        pyramids.back().translate(-0.65f, 0.2f, 0.0f);
        pyramids.back().set_texture_properties("plane_back", 1.0f, 1.0f, "front");
        pyramids.back().set_texture_properties("plane_back", 1.0f, 1.0f, "rear");

        // Wing
        rect_prisms.push_back(RectPrism(-0.25f, 0.65f, 0.0f, 0.7f, 0.1f, 4.0f, {MEDYELLOW, MEDYELLOW, MEDYELLOW, MEDYELLOW, YELLOW, DKYELLOW}));
        rect_prisms.back().set_texture_properties("plane_wing", 1.0f, 10.0f, "top");
        rect_prisms.back().set_texture_properties("plane_wing", 1.0f, 10.0f, "bottom");

        // Horizontal tail
        rect_prisms.push_back(RectPrism(-2.25f, 0.2f, 0.0f, 0.5f, 0.05f, 1.5f, {MEDYELLOW, MEDYELLOW, MEDYELLOW, MEDYELLOW, YELLOW, DKYELLOW}));
        rect_prisms.back().set_texture_properties("plane_wing", 1.0f, 5.0f, "top");
        rect_prisms.back().set_texture_properties("plane_wing", 1.0f, 5.0f, "bottom");

        // Vertical tail
        rect_prisms.push_back(RectPrism(-2.35f, 0.70f, 0.0f, 0.3f, 1.1f, 0.05f, {MEDYELLOW, MEDYELLOW, MEDYELLOW, MEDYELLOW, YELLOW, DKYELLOW}));
        rect_prisms.back().set_texture_properties("plane_wing", 1.0f, 5.0f, "front");
        rect_prisms.back().set_texture_properties("plane_wing", 1.0f, 5.0f, "rear");

        // Vertical tail fairings (right and left)
        triangles.push_back(Surface(Eigen::Vector4f(-2.2f, 0.12f, 0.01f, 1.0f), Eigen::Vector4f(-2.2f, 1.25f, 0.0f, 1.0f),
                                    Eigen::Vector4f(-1.5f, 0.12f, 0.0f, 1.0f), YELLOW));
        triangles.push_back(Surface(Eigen::Vector4f(-1.5f, 0.12f, 0.0f, 1.0f), Eigen::Vector4f(-2.2f, 1.25f, 0.0f, 1.0f),
                                    Eigen::Vector4f(-2.2f, 0.12f, -0.01f, 1.0f), YELLOW));

        // Left tire and hubcap
        octs.push_back(OctPrism(0.25f, -0.55f, -0.4f, 0.3f, 0.3f, 0.15f, {BLACK, BLACK}));
        octs.push_back(OctPrism(0.25f, -0.55f, -0.45f, 0.1f, 0.1f, 0.1f, {WHITE, WHITE}, false, {"far"}));

        // Light tire and hubcap
        octs.push_back(OctPrism(0.25f, -0.55f, 0.4f, 0.3f, 0.3f, 0.15f, {BLACK, BLACK}));
        octs.push_back(OctPrism(0.25f, -0.55f, 0.45f, 0.1f, 0.1f, 0.1f, {GRAY, WHITE}, false, {"near"}));

        // Aft tire and hubcap
        octs.push_back(OctPrism(-2.25f, 0.0f, 0.0f, 0.2f, 0.2f, 0.1f, {BLACK, BLACK}));
        octs.push_back(OctPrism(-2.25f, 0.0f, 0.0f, 0.08f, 0.08f, 0.12f, {GRAY, WHITE}));

        // Right wheel strut (near and far sides)
        triangles.push_back(Surface(Eigen::Vector4f(0.1f, -0.25f, 0.0f, 1.0f), Eigen::Vector4f(0.4f, -0.25f, 0.0f, 1.0f),
                                    Eigen::Vector4f(0.25f, -0.55f, 0.35f, 1.0f), YELLOW));
        triangles.push_back(Surface(Eigen::Vector4f(0.4f, -0.25f, 0.0f, 1.0f), Eigen::Vector4f(0.1f, -0.25f, 0.0f, 1.0f),
                                    Eigen::Vector4f(0.25f, -0.55f, 0.34f, 1.0f), DKYELLOW));

        // Left wheel strut (near and far sides)
        triangles.push_back(Surface(Eigen::Vector4f(0.1f, -0.25f, 0.0f, 1.0f), Eigen::Vector4f(0.4f, -0.25f, 0.0f, 1.0f),
                                    Eigen::Vector4f(0.25f, -0.55f, -0.34f, 1.0f), DKYELLOW));
        triangles.push_back(Surface(Eigen::Vector4f(0.4f, -0.25f, 0.0f, 1.0f), Eigen::Vector4f(0.1f, -0.25f, 0.0f, 1.0f),
                                    Eigen::Vector4f(0.25f, -0.55f, -0.35f, 1.0f), YELLOW));

        // only include "blurred" propeller if airplane has movement
        if (rot_speed != 0.0f)
        {
            // prop
            octs.push_back(OctPrism(0.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.07f, {DKGRAY, DKGRAY}));
            octs.back().rotate(0.0f, 90.0f, 0.0f, "roll-pitch-yaw");
            octs.back().translate(0.92f, 0.0f, 0.0f);

            // spinner
            octs.push_back(OctPrism(0.0f, 0.0f, 0.0f, 0.07f, 0.07f, 0.07f, {GRAY, WHITE}));
            octs.back().rotate(0.0f, 90.0f, 0.0f, "roll-pitch-yaw");
            octs.back().translate(0.95f, 0.0f, 0.0f);
        }

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
        for (auto &shape : pyramids)
        {
            shape_surfaces.clear();
            shape_surfaces = shape.get_surfaces();
            surfaces.insert(surfaces.end(), shape_surfaces.begin(), shape_surfaces.end());
        }
        for (auto &shape : octs)
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

    // set flag to indicate that orbit track has not yet been moved
    shifted = false;
}

void Airplane::move(const float &frame_dt)
{
    // shift back to origin if shift away from mountains has occured
    if (shifted)
    {
        translate(15.0f, 0.0f, 0.0f);
    }

    // rotate about y axis to obtain turning motion
    rotate(0.0f, rot_speed * frame_dt, 0.0f, "roll-pitch-yaw");

    translate(-15.0f, 0.0f, 0.0f);
    shifted = true;
}