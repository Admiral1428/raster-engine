#include "map.hpp"

Map::Map()
{
    // reserve space for each vector
    // shapes_rect_prism.reserve(0);
    shapes_pyramid.reserve(9);
    shapes_tree.reserve(15);
    shapes_house.reserve(1);
    shapes_bridge.reserve(1);
    shapes_airplane.reserve(1);
    shapes_runway.reserve(1);
    shapes_hangar.reserve(1);
    shapes_triangle.reserve(31);
    shapes_quad.reserve(36);

    // small trees along river
    shapes_tree.push_back(Tree(6.5f, -2.0f, -4.0f, "small"));
    shapes_tree.push_back(Tree(-6.5f, -2.0f, -4.0f, "small"));
    shapes_tree.push_back(Tree(6.5f, -2.0f, -15.0f, "small"));
    shapes_tree.push_back(Tree(-6.5f, -2.0f, -15.0f, "small"));

    // small trees on island
    shapes_tree.push_back(Tree(-50.0f, -3.0f, 34.0f, "small", 0.0f, -15.0f, 0.0f, "roll-pitch-yaw"));
    shapes_tree.push_back(Tree(-41.0f, -3.0f, 14.0f, "small", 0.0f, -12.0f, 0.0f, "roll-pitch-yaw"));
    shapes_tree.push_back(Tree(-46.0f, -3.0f, -2.0f, "small", 0.0f, 45.0f, 0.0f, "roll-pitch-yaw"));
    shapes_tree.push_back(Tree(-42.0f, -3.0f, -17.0f, "small", 0.0f, 25.0f, 0.0f, "roll-pitch-yaw"));
    shapes_tree.push_back(Tree(-55.0f, -3.0f, -38.0f, "small", 0.0f, 35.0f, 0.0f, "roll-pitch-yaw"));

    // medium trees near house
    shapes_tree.push_back(Tree(-8.0f, -2.0f, -43.0f, "medium", 0.0f, -35.0f, 0.0f, "roll-pitch-yaw"));
    shapes_tree.push_back(Tree(8.0f, -2.0f, -32.0f, "medium", 0.0f, -35.0f, 0.0f, "roll-pitch-yaw"));

    // medium trees near runway
    shapes_tree.push_back(Tree(10.0f, -2.0f, 15.0f, "medium", 0.0f, -25.0f, 0.0f, "roll-pitch-yaw"));
    shapes_tree.push_back(Tree(18.0f, -2.0f, 10.0f, "medium", 0.0f, 0.0f, 0.0f, "roll-pitch-yaw"));

    // big trees near waterfall
    shapes_tree.push_back(Tree(22.0f, -2.0f, -7.0f, "large", 0.0f, 12.5f, 0.0f, "roll-pitch-yaw"));
    shapes_tree.push_back(Tree(22.0f, -2.0f, -20.0f, "large", 0.0f, 12.5f, 0.0f, "roll-pitch-yaw"));

    // house
    shapes_house.push_back(House(-1.0f, -2.0f, -36.0f, 0.0f, -35.0f, 0.0f, "roll-pitch-yaw"));

    // bridge across straight river
    shapes_bridge.push_back(Bridge(0.0f, -2.0f, -9.5f, 0.0f, 0.0f, 0.0f, "roll-pitch-yaw"));

    // walkway from bridge to house
    shapes_quad.push_back(Quad({-2.7f, -1.99f, -29.0f}, {1.5f, -1.99f, -13.0f}, {-1.4f, -1.99f, -13.0f}, {-5.2f, -1.99f, -30.0f}, {GRAY}, true));
    shapes_quad.back().set_texture_properties("bright_stone", Eigen::Vector2f(2.5f, 20.8f), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(6.0f, 0.0f), Eigen::Vector2f(8.0f, 22.0f));

    shapes_quad.push_back(Quad({-2.4f, -1.99f, -32.3f}, {-2.7f, -1.99f, -29.0f}, {-5.2f, -1.99f, -30.0f}, {-4.2f, -1.99f, -33.5f}, {GRAY}, true));
    shapes_quad.back().set_texture_properties("bright_stone", Eigen::Vector2f(0.8f, 4.4f), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(4.0f, 0.0f), Eigen::Vector2f(4.0f, 5.0f));

    // static airplane
    shapes_airplane.push_back(Airplane(-5.0f, -1.25f, 18.5f, "small", 0.0f, -240.0f, 16.0f, "yaw-pitch-roll", 0.0f));

    // runway
    shapes_runway.push_back(Runway(0.0f, -1.98f, 10.0f, "normal", 0.0f, 30.0f, 0.0f, "roll-pitch-yaw"));

    // hangar
    shapes_hangar.push_back(Hangar(-2.0f, -1.99f, 25.0f, 0.0f, -150.0f, 0.0f, "roll-pitch-yaw"));

    // main grass surfaces (house side)
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-24.0f, -2.0f, -60.0f, 1.0f), Eigen::Vector4f(25.0f, -2.0f, -26.0, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, -26.0f, 1.0f), GREEN, true));
    shapes_triangle.back().set_texture_properties("grass", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(49.0f, 34.0f), Eigen::Vector2f(0.0f, 34.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-24.0f, -2.0f, -26.0f, 1.0f), Eigen::Vector4f(-14.0f, -2.0f, -26.0f, 1.0f), Eigen::Vector4f(-15.0f, -2.0f, -11.5f, 1.0f), GREEN, true));
    shapes_triangle.back().set_texture_properties("grass", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(10.0f, 0.0f), Eigen::Vector2f(10.0f, 14.0f));

    shapes_quad.push_back(Quad({-14.0f, -2.0f, -26.0f}, {10.0f, -2.0f, -26.0f}, {10.0f, -2.0f, -12.0f}, {-15.0f, -2.0f, -11.5f}, {GREEN}, true));
    shapes_quad.back().set_texture_properties("grass", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(24.0f, 0.0f),
                                              Eigen::Vector2f(24.0f, 14.0f), Eigen::Vector2f(0.0f, 14.0f));

    shapes_quad.push_back(Quad({10.0f, -2.0f, -26.0f}, {25.0f, -2.0f, -26.0f}, {25.0f, -2.0f, -17.0f}, {10.0f, -2.0f, -17.0f}, {GREEN}, true));
    shapes_quad.back().set_texture_properties("grass", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(15.0f, 0.0f),
                                              Eigen::Vector2f(15.0f, 9.0f), Eigen::Vector2f(0.0f, 9.0f));

    // main grass surfaces (runway side)
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-24.0f, -2.0f, 10.0f, 1.0f), Eigen::Vector4f(25.0f, -2.0f, 10.0f, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, 60.0f, 1.0f), GREEN, true));
    shapes_triangle.back().set_texture_properties("grass", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(49.0f, 0.0f), Eigen::Vector2f(0.0f, 50.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-15.0f, -2.0f, -7.5f, 1.0f), Eigen::Vector4f(-14.0f, -2.0f, 10.0f, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, 10.0f, 1.0f), GREEN, true));
    shapes_triangle.back().set_texture_properties("grass", Eigen::Vector2f(10.0f, 0.0f), Eigen::Vector2f(10.0f, 17.0f), Eigen::Vector2f(0.0f, 17.0f));

    shapes_quad.push_back(Quad({-15.0f, -2.0f, -7.5f}, {25.0f, -2.0f, -7.0f}, {25.0f, -2.0f, 10.0f}, {-14.0f, -2.0f, 10.0f}, {GREEN}, true));
    shapes_quad.back().set_texture_properties("grass", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(39.0f, 0.0f),
                                              Eigen::Vector2f(39.0f, 17.0f), Eigen::Vector2f(0.0f, 17.0f));

    float ofac = 0.25f; // ocean scale factor for textures

    // ocean water surfaces
    shapes_quad.push_back(Quad({-800.0f, -3.0f, -800.0f}, {-25.0f, -3.0f, -800.0f}, {-25.0f, -3.0f, -50.0f}, {-800.0f, -3.0f, -50.0f}, {BLUE}, true));
    shapes_quad.back().set_texture_properties("water", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(775.0f * ofac, 0.0f),
                                              Eigen::Vector2f(775.0f * ofac, 750.0f * ofac), Eigen::Vector2f(0.0f, 750.0f * ofac));

    shapes_quad.push_back(Quad({-800.0f, -3.0f, 40.0f}, {-25.0f, -3.0f, 40.0f}, {-25.0f, -3.0f, 800.0f}, {-800.0f, -3.0f, 800.0f}, {BLUE}, true));
    shapes_quad.back().set_texture_properties("water", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(775.0f * ofac, 0.0f),
                                              Eigen::Vector2f(775.0f * ofac, 760.0f * ofac), Eigen::Vector2f(0.0f, 760.0f * ofac));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-100.0f, -3.0f, -50.0f, 1.0f), Eigen::Vector4f(-60.0f, -3.0f, -50.0f, 1.0f), Eigen::Vector4f(-100.0f, -3.0f, -10.0f, 1.0f), BLUE, true));
    shapes_triangle.back().set_texture_properties("water", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(40.0f * ofac, 0.0f), Eigen::Vector2f(0.0f, 40.0f * ofac));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-100.0f, -3.0f, 40.0f, 1.0f), Eigen::Vector4f(-100.0f, -3.0f, 10.0f, 1.0f), Eigen::Vector4f(-50.0f, -3.0f, 40.0f, 1.0f), BLUE, true));
    shapes_triangle.back().set_texture_properties("water", Eigen::Vector2f(0.0f, 30.0f * ofac), Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(50.0f * ofac, 30.0f * ofac));

    shapes_quad.push_back(Quad({-100.0f, -3.0f, 40.0f}, {-800.0f, -3.0f, 40.0f}, {-800.0f, -3.0f, -50.0f}, {-100.0f, -3.0f, -50.0f}, {BLUE}, true));
    shapes_quad.back().set_texture_properties("water", Eigen::Vector2f(700.0f * ofac, 90.0f * ofac), Eigen::Vector2f(0.0f, 90.0f * ofac),
                                              Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(700.0f * ofac, 0.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-37.0f, -3.0f, 40.0f, 1.0f), Eigen::Vector4f(-50.0f, -3.0f, 40.0f, 1.0f), Eigen::Vector4f(-37.0f, -3.0f, 15.0f, 1.0f), BLUE, true));
    shapes_triangle.back().set_texture_properties("water", Eigen::Vector2f(13.0f * ofac, 25.0f * ofac), Eigen::Vector2f(0.0f, 25.0f * ofac), Eigen::Vector2f(13.0f * ofac, 0.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-37.0f, -3.0f, 15.0f, 1.0f), Eigen::Vector4f(-45.0f, -3.0f, 0.0f, 1.0f), Eigen::Vector4f(-37.0f, -3.0f, -15.0f, 1.0f), BLUE, true));
    shapes_triangle.back().set_texture_properties("water", Eigen::Vector2f(8.0f * ofac, 30.0f * ofac), Eigen::Vector2f(0.0f, 15.0f * ofac), Eigen::Vector2f(8.0f * ofac, 0.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-37.0f, -3.0f, -15.0f, 1.0f), Eigen::Vector4f(-60.0f, -3.0f, -50.0f, 1.0f), Eigen::Vector4f(-37.0f, -3.0f, -50.0f, 1.0f), BLUE, true));
    shapes_triangle.back().set_texture_properties("water", Eigen::Vector2f(23.0f * ofac, 35.0f * ofac), Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(23.0f * ofac, 0.0f));

    shapes_quad.push_back(Quad({-37.0f, -3.0f, 40.0f}, {-37.0f, -3.0f, -50.0f}, {-25.0f, -3.0f, -50.0f}, {-25.0f, -3.0f, 40.0f}, {BLUE}, true));
    shapes_quad.back().set_texture_properties("water", Eigen::Vector2f(0.0f, 90.0f * ofac), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(12.0f * ofac, 0.0f), Eigen::Vector2f(12.0f * ofac, 90.0f * ofac));

    shapes_quad.push_back(Quad({-25.0f, -3.0f, -11.0f}, {-16.0f, -3.0f, -11.0f}, {-16.0f, -3.0f, -8.0f}, {-25.0f, -3.0f, -8.0f}, {BLUE}, true));
    shapes_quad.back().set_texture_properties("water", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(9.0f * ofac, 0.0f),
                                              Eigen::Vector2f(9.0f * ofac, 3.0f * ofac), Eigen::Vector2f(0.0f, 3.0f * ofac));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-25.0f, -3.0f, -25.5f, 1.0f), Eigen::Vector4f(-16.0f, -3.0f, -11.0f, 1.0f), Eigen::Vector4f(-25.0f, -3.0f, -11.0f, 1.0f), BLUE, true));
    shapes_triangle.back().set_texture_properties("water", Eigen::Vector2f(9.0f * ofac, 14.5f * ofac), Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(9.0f * ofac, 0.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-25.0f, -3.0f, -8.0f, 1.0f), Eigen::Vector4f(-16.0f, -3.0f, -8.0f, 1.0f), Eigen::Vector4f(-25.0f, -3.0f, 9.5f, 1.0f), BLUE, true));
    shapes_triangle.back().set_texture_properties("water", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(9.0f * ofac, 0.0f), Eigen::Vector2f(0.0f, 17.5f * ofac));

    // distant water surfaces on main land side (far and near and mid)
    shapes_quad.push_back(Quad({-25.0f, -3.0f, -60.0f}, {-25.0f, -3.0f, -800.0f}, {800.0f, -3.0f, -800.0f}, {800.0f, -3.0f, -60.0f}, {BLUE}, true));
    shapes_quad.back().set_texture_properties("water", Eigen::Vector2f(0.0f, 740.0f * ofac), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(825.0f * ofac, 0.0f), Eigen::Vector2f(825.0f * ofac, 740.0f * ofac));

    shapes_quad.push_back(Quad({800.0f, -3.0f, 60.0f}, {800.0f, -3.0f, 800.0f}, {-25.0f, -3.0f, 800.0f}, {-25.0f, -3.0f, 60.0f}, {BLUE}, true));
    shapes_quad.back().set_texture_properties("water", Eigen::Vector2f(825.0f * ofac, 0.0f), Eigen::Vector2f(825.0f * ofac, 740.0f * ofac),
                                              Eigen::Vector2f(0.0f, 740.0f * ofac), Eigen::Vector2f(0.0f, 0.0f));

    shapes_quad.push_back(Quad({25.0f, -3.0f, -60.0f}, {800.0f, -3.0f, -60.0f}, {800.0f, -3.0f, 60.0f}, {25.0f, -3.0f, 60.0f}, {BLUE}, true));
    shapes_quad.back().set_texture_properties("water", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(775.0f * ofac, 0.0f),
                                              Eigen::Vector2f(775.0f * ofac, 120.0f * ofac), Eigen::Vector2f(0.0f, 120.0f * ofac));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-25.0f, -3.0f, -60.0f, 1.0f), Eigen::Vector4f(25.0f, -3.0f, -60.0f, 1.0f), Eigen::Vector4f(25.0f, -3.0f, -26.0f, 1.0f), BLUE, true));
    shapes_triangle.back().set_texture_properties("water", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(50.0f * ofac, 0.0f), Eigen::Vector2f(50.0f * ofac, 34.0f * ofac));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-25.0f, -3.0f, 60.0f, 1.0f), Eigen::Vector4f(25.0f, -3.0f, 10.0f, 1.0f), Eigen::Vector4f(25.0f, -3.0f, 60.0f, 1.0f), BLUE, true));
    shapes_triangle.back().set_texture_properties("water", Eigen::Vector2f(0.0f, 50.0f * ofac), Eigen::Vector2f(50.0f * ofac, 0.0f), Eigen::Vector2f(50.0f * ofac, 50.0f * ofac));

    float bfac = 2.0f; // beach scale factor for textures

    // top beach surfaces
    shapes_quad.push_back(Quad({-25.0f, -3.0f, -60.0f}, {-24.0f, -2.0f, -60.0f}, {-24.0f, -2.0f, -26.0f}, {-25.0f, -3.0f, -26.0f}, {YELLOW}, false));
    shapes_quad.back().set_texture_properties("sand", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(1.0f * bfac, 0.0f),
                                              Eigen::Vector2f(1.0f * bfac, 34.0f * bfac), Eigen::Vector2f(0.0f, 34.0f * bfac));

    // bottom beach surfaces
    shapes_quad.push_back(Quad({-25.0f, -3.0f, 10.0f}, {-24.0f, -2.0f, 10.0f}, {-24.0f, -2.0f, 60.0f}, {-25.0f, -3.0f, 60.0f}, {YELLOW}, false));
    shapes_quad.back().set_texture_properties("sand", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(1.0f * bfac, 0.0f),
                                              Eigen::Vector2f(1.0f * bfac, 50.0f * bfac), Eigen::Vector2f(0.0f, 50.0f * bfac));

    // mid top beach surfaces
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-25.0f, -3.0f, -26.0f, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, -26.0f, 1.0f), Eigen::Vector4f(-25.0f, -3.0f, -25.5f, 1.0f), YELLOW, false));
    shapes_triangle.back().set_texture_properties("sand", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(2.0f, 0.0f), Eigen::Vector2f(0.0f, 1.0f));

    shapes_quad.push_back(Quad({-25.0f, -3.0f, -25.5f}, {-24.0f, -2.0f, -26.0f}, {-15.0f, -2.0f, -11.5f}, {-16.0f, -3.0f, -11.0f}, {YELLOW}, false));
    shapes_quad.back().set_texture_properties("sand", Eigen::Vector2f(0.0f, 1.0f * bfac), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(5.0f * bfac, 0.0f), Eigen::Vector2f(4.8f * bfac, 1.0f * bfac));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-16.0f, -3.0f, -11.0f, 1.0f), Eigen::Vector4f(-15.0f, -2.0f, -11.5f, 1.0f), Eigen::Vector4f(-12.5f, -2.5f, -11.0f, 1.0f), BROWN, false));
    shapes_triangle.back().set_texture_properties("dirt", Eigen::Vector2f(0.0f, 1.0f), Eigen::Vector2f(1.0f, 0.0f), Eigen::Vector2f(2.0f, 1.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-15.0f, -2.0f, -11.5f, 1.0f), Eigen::Vector4f(-12.5f, -2.0f, -12.0f, 1.0f), Eigen::Vector4f(-12.5f, -2.5f, -11.0f, 1.0f), BROWN, false));
    shapes_triangle.back().set_texture_properties("dirt", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(2.0f, 0.0f), Eigen::Vector2f(2.0f, 1.0f));

    // mid bottom beach surfaces
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-25.0f, -3.0f, 9.5f, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, 10.0f, 1.0f), Eigen::Vector4f(-25.0f, -3.0f, 10.0f, 1.0f), YELLOW, false));
    shapes_triangle.back().set_texture_properties("sand", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(2.0f, 1.0f), Eigen::Vector2f(0.0f, 1.0f));

    shapes_quad.push_back(Quad({-16.0f, -3.0f, -8.0f}, {-15.0f, -2.0f, -7.5f}, {-24.0f, -2.0f, 10.0f}, {-25.0f, -3.0f, 9.5f}, {YELLOW}, false));
    shapes_quad.back().set_texture_properties("sand", Eigen::Vector2f(4.8f * bfac, 0.0f), Eigen::Vector2f(5.0f * bfac, 1.0f * bfac),
                                              Eigen::Vector2f(0.0f, 1.0f * bfac), Eigen::Vector2f(0.0f, 0.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-16.0f, -3.0f, -8.0f, 1.0f), Eigen::Vector4f(-12.5f, -2.5f, -8.0f, 1.0f), Eigen::Vector4f(-15.0f, -2.0f, -7.5f, 1.0f), BROWN, false));
    shapes_triangle.back().set_texture_properties("dirt", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(2.0f, 0.0f), Eigen::Vector2f(1.0f, 1.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-12.5f, -2.5f, -8.0f, 1.0f), Eigen::Vector4f(-12.5f, -2.0f, -7.0f, 1.0f), Eigen::Vector4f(-15.0f, -2.0f, -7.5f, 1.0f), BROWN, false));
    shapes_triangle.back().set_texture_properties("dirt", Eigen::Vector2f(2.0f, 0.0f), Eigen::Vector2f(2.0f, 1.0f), Eigen::Vector2f(0.0f, 1.0f));

    // beach waterfall
    shapes_quad.push_back(Quad({-16.0f, -3.0f, -11.0f}, {-12.5f, -2.5f, -11.0f}, {-12.5f, -2.5f, -8.0f}, {-16.0f, -3.0f, -8.0f}, {BLUE}, false));
    shapes_quad.back().set_texture_properties("waterfall", Eigen::Vector2f(0.0f, 2.0f), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(1.0f, 0.0f), Eigen::Vector2f(1.0f, 2.0f));

    // main river
    shapes_quad.push_back(Quad({-12.5f, -2.0f, -12.0f}, {10.0f, -2.0f, -12.0f}, {10.0f, -2.5f, -11.0f}, {-12.5f, -2.5f, -11.0f}, {BROWN}, false));
    shapes_quad.back().set_texture_properties("dirt", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(22.0f, 0.0f),
                                              Eigen::Vector2f(22.0f, 1.0f), Eigen::Vector2f(0.0f, 1.0f));

    shapes_quad.push_back(Quad({-12.5f, -2.5f, -11.0f}, {10.0f, -2.5f, -11.0f}, {10.0f, -2.5f, -8.0f}, {-12.5f, -2.5f, -8.0f}, {BLUE}, false));
    shapes_quad.back().set_texture_properties("waterfall", Eigen::Vector2f(0.0f, 11.0f), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(1.0f, 0.0f), Eigen::Vector2f(1.0f, 11.0f));

    shapes_quad.push_back(Quad({-12.5f, -2.5f, -8.0f}, {10.0f, -2.5f, -8.0f}, {10.0f, -2.0f, -7.0f}, {-12.5f, -2.0f, -7.0f}, {BROWN}, false));
    shapes_quad.back().set_texture_properties("dirt", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(22.0f, 0.0f),
                                              Eigen::Vector2f(22.0f, 1.0f), Eigen::Vector2f(0.0f, 1.0f));

    // diagonal river (includes grass, dirt, and water)
    shapes_triangle.push_back(Surface(Eigen::Vector4f(10.0f, -2.0f, -17.0f, 1.0f), Eigen::Vector4f(25.0f, -2.0f, -17.0f, 1.0f), Eigen::Vector4f(10.0f, -2.0f, -12.0f, 1.0f), GREEN, true));
    shapes_triangle.back().set_texture_properties("grass", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(15.0f, 0.0f), Eigen::Vector2f(0.0f, 5.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(10.0f, -2.5f, -11.0f, 1.0f), Eigen::Vector4f(10.0f, -2.0f, -12.0f, 1.0f), Eigen::Vector4f(11.0f, -2.5f, -11.25f, 1.0f), BROWN, false));
    shapes_triangle.back().set_texture_properties("dirt", Eigen::Vector2f(0.0f, 1.0f), Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(2.0f, 0.5f));

    shapes_quad.push_back(Quad({10.0f, -2.0f, -12.0f}, {25.0f, -2.0f, -17.0f}, {25.0f, -2.0f, -16.0f}, {11.0f, -2.5f, -11.25f}, {BROWN}, false));
    shapes_quad.back().set_texture_properties("dirt", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(4.0f, 0.0f),
                                              Eigen::Vector2f(4.0f, 1.0f), Eigen::Vector2f(0.0f, 1.0f));

    shapes_quad.push_back(Quad({10.0f, -2.5f, -11.0f}, {25.0f, -2.0f, -16.0f}, {25.0f, -2.0f, -13.0f}, {10.0f, -2.5f, -8.0f}, {BLUE}, false));
    shapes_quad.back().set_texture_properties("waterfall", Eigen::Vector2f(0.0f, 6.5f), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(1.0f, 0.2f), Eigen::Vector2f(1.0f, 6.8f));

    shapes_quad.push_back(Quad({10.0f, -2.5f, -8.0f}, {25.0f, -2.0f, -13.0f}, {25.0f, -2.0f, -12.0f}, {11.0f, -2.0f, -7.0f}, {BROWN}, false));
    shapes_quad.back().set_texture_properties("dirt", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(4.0f, 0.0f),
                                              Eigen::Vector2f(4.0f, 1.0f), Eigen::Vector2f(0.0f, 1.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(10.0f, -2.5f, -8.0f, 1.0f), Eigen::Vector4f(11.0f, -2.0f, -7.0f, 1.0f), Eigen::Vector4f(10.0f, -2.0f, -7.0f, 1.0f), BROWN, false));
    shapes_triangle.back().set_texture_properties("dirt", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(2.0f, 1.0f), Eigen::Vector2f(0.0f, 1.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(11.0f, -2.0f, -7.0f, 1.0f), Eigen::Vector4f(25.0f, -2.0f, -12.0f, 1.0f), Eigen::Vector4f(25.0f, -2.0f, -7.0f, 1.0f), GREEN, true));
    shapes_triangle.back().set_texture_properties("grass", Eigen::Vector2f(0.0f, 5.0f), Eigen::Vector2f(14.0f, 0.0f), Eigen::Vector2f(14.0f, 5.0f));

    // waterfall

    shapes_quad.push_back(Quad({25.0f, -2.0f, -22.0f}, {25.0f, -2.0f, -26.0f}, {26.0f, 20.0, -26.0f}, {26.0f, 20.0f, -22.0f}, {TAN}, false));
    shapes_quad.back().set_texture_properties("rock", Eigen::Vector2f(2.0f, 11.0f), Eigen::Vector2f(0.0f, 11.0f),
                                              Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(2.0f, 0.0f));

    shapes_quad.push_back(Quad({25.0f, -2.0f, -22.0f}, {26.0f, 20.0f, -22.0f}, {26.0f, 18.5f, -16.0f}, {25.0f, -2.0f, -16.0f}, {TAN}, false));
    shapes_quad.back().set_texture_properties("rock", Eigen::Vector2f(0.0f, 10.0f), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(3.0f, 0.25f), Eigen::Vector2f(3.0f, 10.0f));

    shapes_quad.push_back(Quad({25.0f, -2.0f, -16.0f}, {26.0f, 18.0f, -16.0f}, {26.0f, 18.0f, -13.0f}, {25.0f, -2.0f, -13.0f}, {BLUE}, false));
    shapes_quad.back().set_texture_properties("waterfall", Eigen::Vector2f(0.0f, 6.0f), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(1.0f, 0.0f), Eigen::Vector2f(1.0f, 6.0f));

    shapes_quad.push_back(Quad({25.0f, -2.0f, -13.0f}, {26.0f, 18.5f, -13.0f}, {26.0f, 20.0f, -7.0f}, {25.0f, -2.0f, -7.0f}, {TAN}, false));
    shapes_quad.back().set_texture_properties("rock", Eigen::Vector2f(0.0f, 10.0f), Eigen::Vector2f(0.0f, 0.25f),
                                              Eigen::Vector2f(3.0f, 0.0f), Eigen::Vector2f(3.0f, 10.0f));

    shapes_quad.push_back(Quad({25.0f, -2.0f, -7.0f}, {26.0f, 20.0f, -7.0f}, {26.0f, 20.0, 10.0f}, {25.0f, -2.0f, 10.0f}, {TAN}, false));
    shapes_quad.back().set_texture_properties("rock", Eigen::Vector2f(0.0f, 11.0f), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(8.0f, 0.0f), Eigen::Vector2f(8.0f, 11.0f));

    // far cliff (left of waterfall)
    shapes_quad.push_back(Quad({25.0f, -2.0f, -26.0f}, {0.5f, -2.0f, -43.0f}, {0.5f, 11.0f, -43.0f}, {26.0f, 20.0, -26.0f}, {TAN}, false));
    shapes_quad.back().set_texture_properties("rock", Eigen::Vector2f(14.0f, 8.0f), Eigen::Vector2f(0.0f, 8.0f),
                                              Eigen::Vector2f(0.0f, 3.0f), Eigen::Vector2f(14.0f, 0.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(0.5f, 11.0f, -43.0f, 1.0f), Eigen::Vector4f(0.5f, -2.0f, -43.0f, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, -60.0f, 1.0f), {TAN}, false));
    shapes_triangle.back().set_texture_properties("rock", Eigen::Vector2f(11.0f, 0.0f), Eigen::Vector2f(11.0f, 5.0f), Eigen::Vector2f(0.0f, 5.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(0.0f, 15.0f, -55.0f, 1.0f), Eigen::Vector4f(0.5f, 11.0f, -43.0f, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, -60.0f, 1.0f), {GREEN}, false));
    shapes_triangle.back().set_texture_properties("grass_dark", Eigen::Vector2f(13.0f, 0.0f), Eigen::Vector2f(13.0f, 6.0f), Eigen::Vector2f(0.0f, 6.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(0.0f, 15.0f, -55.0f, 1.0f), Eigen::Vector4f(26.0f, 20.0, -26.0f, 1.0f), Eigen::Vector4f(0.5f, 11.0f, -43.0f, 1.0f), {GREEN}, false));
    shapes_triangle.back().set_texture_properties("grass_dark", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(15.0f, 6.0f), Eigen::Vector2f(0.0f, 6.0f));

    // near cliff (right of waterfall)
    shapes_quad.push_back(Quad({25.0f, -2.0f, 10.0f}, {26.0f, 20.0f, 10.0f}, {10.3f, 14.0f, 25.0f}, {10.3f, -2.0f, 25.0f}, {TAN}, false));
    shapes_quad.back().set_texture_properties("rock", Eigen::Vector2f(0.0f, 8.0f), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(10.0f, 2.0f), Eigen::Vector2f(10.0f, 8.0f));

    shapes_quad.push_back(Quad({10.3, -2.0f, 25.0f}, {10.3f, 14.0f, 25.0f}, {0.5f, 19.0f, 37.0f}, {0.5f, -2.0f, 35.0f}, {TAN}, false));
    shapes_quad.back().set_texture_properties("rock", Eigen::Vector2f(0.0f, 7.0f), Eigen::Vector2f(0.0f, 2.0f),
                                              Eigen::Vector2f(5.0f, 0.0f), Eigen::Vector2f(5.0f, 7.0f));

    shapes_quad.push_back(Quad({0.5f, -2.0f, 35.0f}, {0.5f, 19.0f, 37.0f}, {-12.0f, 8.0f, 49.0f}, {-11.75f, -2.0f, 47.5f}, {TAN}, false));
    shapes_quad.back().set_texture_properties("rock", Eigen::Vector2f(0.0f, 7.5f), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(5.0f, 3.0f), Eigen::Vector2f(5.0f, 7.5f));

    shapes_quad.push_back(Quad({-11.75f, -2.0f, 47.5f}, {-12.0f, 8.0f, 49.0f}, {-17.0f, 8.0f, 54.0f}, {-24.0f, -2.0f, 60.0f}, {TAN}, false));
    shapes_quad.back().set_texture_properties("rock", Eigen::Vector2f(0.0f, 4.0f), Eigen::Vector2f(0.0f, 0.0f),
                                              Eigen::Vector2f(2.0f, 0.0f), Eigen::Vector2f(4.0f, 4.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(26.0f, 20.0f, 10.0f, 1.0f), Eigen::Vector4f(15.0f, 19.0f, 30.0f, 1.0f), Eigen::Vector4f(10.3f, 14.0f, 25.0f, 1.0f), {GREEN}, false));
    shapes_triangle.back().set_texture_properties("grass_dark", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(12.0f, 0.0f), Eigen::Vector2f(12.0f, 4.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(15.0f, 19.0f, 30.0f, 1.0f), Eigen::Vector4f(0.5f, 19.0f, 37.0f, 1.0f), Eigen::Vector4f(10.3f, 14.0f, 25.0f, 1.0f), {GREEN}, false));
    shapes_triangle.back().set_texture_properties("grass_dark", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(9.0f, 0.0f), Eigen::Vector2f(0.0f, 4.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(0.5f, 19.0f, 37.0f, 1.0f), Eigen::Vector4f(-10.0f, 15.0f, 52.0f, 1.0f), Eigen::Vector4f(-12.0f, 8.0f, 49.0f, 1.0f), {GREEN}, false));
    shapes_triangle.back().set_texture_properties("grass_dark", Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(8.0f, 0.0f), Eigen::Vector2f(8.0f, 4.0f));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-12.0f, 8.0f, 49.0f, 1.0f), Eigen::Vector4f(-10.0f, 15.0f, 52.0f, 1.0f), Eigen::Vector4f(-17.0f, 8.0f, 54.0f, 1.0f), {GREEN}, false));
    shapes_triangle.back().set_texture_properties("grass_dark", Eigen::Vector2f(0.0f, 4.0f), Eigen::Vector2f(0.0f, 0.0f), Eigen::Vector2f(4.0f, 4.0f));

    float ifac = 10.0f; // factor for scaling island surface textures

    // island
    shapes_quad.push_back(Quad({-100.0f, -3.0f, 10.0f}, {-45.0f, -3.0f, 0.0f}, {-37.0f, -3.0f, 15.0f}, {-50.0f, -3.0f, 40.0f}, {YELLOW}, false));
    shapes_quad.back().set_texture_properties("sand", Eigen::Vector2f(0.25f * ifac, 0.0f), Eigen::Vector2f(0.9f * ifac, 0.0f),
                                              Eigen::Vector2f(1.0f * ifac, 0.3f * ifac), Eigen::Vector2f(0.8f * ifac, 1.0f * ifac));

    shapes_quad.push_back(Quad({-100.0f, -3.0f, -10.0f}, {-60.0f, -3.0f, -50.0f}, {-37.0f, -3.0f, -15.0f}, {-45.0f, -3.0f, 0.0f}, {YELLOW}, false));
    shapes_quad.back().set_texture_properties("sand", Eigen::Vector2f(0.0f, 0.8f * ifac), Eigen::Vector2f(0.6f * ifac, 0.0f),
                                              Eigen::Vector2f(1.0f * ifac, 0.7f * ifac), Eigen::Vector2f(0.85f * ifac, 1.0f * ifac));

    shapes_triangle.push_back(Surface(Eigen::Vector4f(-45.0f, -3.0f, 0.0f, 1.0f), Eigen::Vector4f(-100.0f, -3.0f, 10.0f, 1.0f), Eigen::Vector4f(-100.0f, -3.0f, -10.0f, 1.0f), YELLOW, false));
    shapes_triangle.back().set_texture_properties("sand", Eigen::Vector2f(6.0f, 1.0f), Eigen::Vector2f(0.0f, 2.0f), Eigen::Vector2f(0.0f, 0.0f));

    // island mountains
    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 15.0f, 10.0f, 15.0f, {DKGREEN, DKGREEN, DKGREEN, DKGREEN, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-52.0f, -2.99, 20.0f);
    shapes_pyramid.back().set_texture_properties("grass", 4.0f, 2.0f, "front");
    shapes_pyramid.back().set_texture_properties("grass", 4.0f, 2.0f, "rear");
    shapes_pyramid.back().set_texture_properties("grass", 4.0f, 2.0f, "left");
    shapes_pyramid.back().set_texture_properties("grass", 4.0f, 2.0f, "right");

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 15.0f, 16.0f, 15.0f, {DKGREEN, DKGREEN, DKGREEN, DKGREEN, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-58.0f, -2.99, 5.0f);
    shapes_pyramid.back().set_texture_properties("grass", 4.0f, 5.0f, "front");
    shapes_pyramid.back().set_texture_properties("grass", 4.0f, 5.0f, "rear");
    shapes_pyramid.back().set_texture_properties("grass", 4.0f, 5.0f, "left");
    shapes_pyramid.back().set_texture_properties("grass", 4.0f, 5.0f, "right");

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 15.0f, 13.0f, 15.0f, {DKGREEN, DKGREEN, DKGREEN, DKGREEN, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-53.0f, -2.99, -10.0f);
    shapes_pyramid.back().set_texture_properties("grass", 4.0f, 3.0f, "front");
    shapes_pyramid.back().set_texture_properties("grass", 4.0f, 3.0f, "rear");
    shapes_pyramid.back().set_texture_properties("grass", 4.0f, 3.0f, "left");
    shapes_pyramid.back().set_texture_properties("grass", 4.0f, 3.0f, "right");

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 20.0f, 15.0f, 20.0f, {DKGREEN, DKGREEN, DKGREEN, DKGREEN, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-65.0f, -2.99, -24.0f);
    shapes_pyramid.back().set_texture_properties("grass", 5.0f, 3.0f, "front");
    shapes_pyramid.back().set_texture_properties("grass", 5.0f, 3.0f, "rear");
    shapes_pyramid.back().set_texture_properties("grass", 5.0f, 3.0f, "left");
    shapes_pyramid.back().set_texture_properties("grass", 5.0f, 3.0f, "right");

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 15.0f, {DKBROWN, DKBROWN, DKBROWN, DKBROWN, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-67.0f, -2.99, 13.0f);
    shapes_pyramid.back().set_texture_properties("mountain", 1.0f, 1.0f, "front");
    shapes_pyramid.back().set_texture_properties("mountain", 1.0f, 1.0f, "rear");
    shapes_pyramid.back().set_texture_properties("mountain", 1.0f, 1.0f, "left");
    shapes_pyramid.back().set_texture_properties("mountain", 1.0f, 1.0f, "right");

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 20.0f, 30.0f, 20.0f, {DKBROWN, DKBROWN, DKBROWN, DKBROWN, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-70.0f, -2.99, 0.0f);
    shapes_pyramid.back().set_texture_properties("mountain", 1.0f, 1.0f, "front");
    shapes_pyramid.back().set_texture_properties("mountain", 1.0f, 1.0f, "rear");
    shapes_pyramid.back().set_texture_properties("mountain", 1.0f, 1.0f, "left");
    shapes_pyramid.back().set_texture_properties("mountain", 1.0f, 1.0f, "right");

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 22.0f, 28.0f, 22.0f, {DKBROWN, DKBROWN, DKBROWN, DKBROWN, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-75.0f, -2.99, -15.0f);
    shapes_pyramid.back().set_texture_properties("mountain", 1.0f, 1.0f, "front");
    shapes_pyramid.back().set_texture_properties("mountain", 1.0f, 1.0f, "rear");
    shapes_pyramid.back().set_texture_properties("mountain", 1.0f, 1.0f, "left");
    shapes_pyramid.back().set_texture_properties("mountain", 1.0f, 1.0f, "right");

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 15.0f, 38.0f, 15.0f, {WHITE, WHITE, WHITE, WHITE, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-76.0f, -2.99, 7.5f);
    shapes_pyramid.back().set_texture_properties("snow", 3.0f, 9.0f, "front");
    shapes_pyramid.back().set_texture_properties("snow", 3.0f, 9.0f, "rear");
    shapes_pyramid.back().set_texture_properties("snow", 3.0f, 9.0f, "left");
    shapes_pyramid.back().set_texture_properties("snow", 3.0f, 9.0f, "right");

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 15.0f, 44.0f, 15.0f, {WHITE, WHITE, WHITE, WHITE, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-78.0f, -2.99, -4.0f);
    shapes_pyramid.back().set_texture_properties("snow", 3.0f, 11.0f, "front");
    shapes_pyramid.back().set_texture_properties("snow", 3.0f, 11.0f, "rear");
    shapes_pyramid.back().set_texture_properties("snow", 3.0f, 11.0f, "left");
    shapes_pyramid.back().set_texture_properties("snow", 3.0f, 11.0f, "right");
}

Map::~Map() {}

vector<Surface> &Map::get_map_surfaces()
{
    all_surfaces.clear();

    for (auto &shape : shapes_rect_prism)
    {
        push_surfaces(shape.get_surfaces());
    }

    for (auto &shape : shapes_pyramid)
    {
        push_surfaces(shape.get_surfaces());
    }

    for (auto &shape : shapes_rect)
    {
        push_surfaces(shape.get_surfaces());
    }

    for (auto &shape : shapes_triangle)
    {
        all_surfaces.push_back(shape);
    }

    for (auto &shape : shapes_quad)
    {
        push_surfaces(shape.get_surfaces());
    }

    for (auto &shape : shapes_tree)
    {
        push_surfaces(shape.get_surfaces());
    }

    for (auto &shape : shapes_house)
    {
        push_surfaces(shape.get_surfaces());
    }

    for (auto &shape : shapes_bridge)
    {
        push_surfaces(shape.get_surfaces());
    }

    for (auto &shape : shapes_airplane)
    {
        push_surfaces(shape.get_surfaces());
    }

    for (auto &shape : shapes_runway)
    {
        push_surfaces(shape.get_surfaces());
    }

    for (auto &shape : shapes_hangar)
    {
        push_surfaces(shape.get_surfaces());
    }

    return all_surfaces;
}

void Map::push_surfaces(const vector<Surface> &temp_surfaces)
{
    for (const auto &surface : temp_surfaces)
    {
        all_surfaces.push_back(surface);
    }
}