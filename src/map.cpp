#include "map.hpp"

Map::Map()
{
    // reserve space for each vector
    shapes_rect_prism.reserve(2);
    shapes_pyramid.reserve(12);
    shapes_triangle.reserve(26);
    shapes_quad.reserve(30);

    // right tree
    shapes_rect_prism.push_back(RectPrism(2.5f, -1.0f, -4.0f, 0.5f, 2.0f, 0.5f, {BROWN, BROWN, DKBROWN, DKBROWN, BLACK, BLACK}, false, {"top", "bottom"}));
    shapes_pyramid.push_back(Pyramid(2.5f, 0.0f, -4.0f, 2.0f, 2.0f, 2.0f, {DKGREEN, DKGREEN, MEDGREEN, MEDGREEN, BLACK}));

    // left tree
    shapes_rect_prism.push_back(RectPrism(-5.0f, 0.0f, -15.0f, 0.75f, 4.0f, 0.75f, {BROWN, BROWN, DKBROWN, DKBROWN, BROWN, BROWN}, false, {"top", "bottom"}));
    shapes_pyramid.push_back(Pyramid(-5.0f, 2.0f, -15.0f, 3.0f, 3.0f, 3.0f, {DKGREEN, DKGREEN, MEDGREEN, MEDGREEN, BLACK}));

    // main grass surfaces
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-24.0f, -2.0f, -60.0f, 1.0f), Eigen::Vector4f(25.0f, -2.0f, -26.0, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, -26.0f, 1.0f), GREEN, true));
    // shapes_quad.push_back(Quad({-24.0f, -2.0f, -60.0f}, {25.0f, -2.0f, -60.0f}, {25.0f, -2.0f, -26.0f}, {-24.0f, -2.0f, -26.0f}, {GREEN}, true));
    shapes_quad.push_back(Quad({-14.0f, -2.0f, -26.0f}, {10.0f, -2.0f, -26.0f}, {10.0f, -2.0f, -12.0f}, {-14.0f, -2.0f, -12.0f}, {GREEN}, true));
    shapes_quad.push_back(Quad({10.0f, -2.0f, -26.0f}, {25.0f, -2.0f, -26.0f}, {25.0f, -2.0f, -17.0f}, {10.0f, -2.0f, -17.0f}, {GREEN}, true));
    shapes_quad.push_back(Quad({-14.0f, -2.0f, -7.0f}, {25.0f, -2.0f, -7.0f}, {25.0f, -2.0f, 10.0f}, {-14.0f, -2.0f, 10.0f}, {GREEN}, true));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-24.0f, -2.0f, 10.0f, 1.0f), Eigen::Vector4f(25.0f, -2.0f, 10.0f, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, 60.0f, 1.0f), GREEN, true));
    // shapes_quad.push_back(Quad({-24.0f, -2.0f, 10.0f}, {25.0f, -2.0f, 10.0f}, {25.0f, -2.0f, 60.0f}, {-24.0f, -2.0f, 60.0f}, {GREEN}, true));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-14.0f, -2.0f, -7.0f, 1.0f), Eigen::Vector4f(-14.0f, -2.0f, 10.0f, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, 10.0f, 1.0f), GREEN, true));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-24.0f, -2.0f, -26.0f, 1.0f), Eigen::Vector4f(-14.0f, -2.0f, -26.0f, 1.0f), Eigen::Vector4f(-14.0f, -2.0f, -12.0f, 1.0f), GREEN, true));

    // ocean water surfaces
    shapes_quad.push_back(Quad({-150.0f, -3.0f, -185.0f}, {-25.0f, -3.0f, -185.0f}, {-25.0f, -3.0f, -50.0f}, {-150.0f, -3.0f, -50.0f}, {BLUE}, true));
    shapes_quad.push_back(Quad({-150.0f, -3.0f, 40.0f}, {-25.0f, -3.0f, 40.0f}, {-25.0f, -3.0f, 185.0f}, {-150.0f, -3.0f, 185.0f}, {BLUE}, true));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-150.0f, -3.0f, -50.0f, 1.0f), Eigen::Vector4f(-60.0f, -3.0f, -50.0f, 1.0f), Eigen::Vector4f(-150.0f, -3.0f, -10.0f, 1.0f), BLUE, true));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-150.0f, -3.0f, 40.0f, 1.0f), Eigen::Vector4f(-150.0f, -3.0f, 10.0f, 1.0f), Eigen::Vector4f(-50.0f, -3.0f, 40.0f, 1.0f), BLUE, true));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-37.0f, -3.0f, 40.0f, 1.0f), Eigen::Vector4f(-50.0f, -3.0f, 40.0f, 1.0f), Eigen::Vector4f(-37.0f, -3.0f, 15.0f, 1.0f), BLUE, true));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-37.0f, -3.0f, 15.0f, 1.0f), Eigen::Vector4f(-45.0f, -3.0f, 0.0f, 1.0f), Eigen::Vector4f(-37.0f, -3.0f, -15.0f, 1.0f), BLUE, true));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-37.0f, -3.0f, -15.0f, 1.0f), Eigen::Vector4f(-60.0f, -3.0f, -50.0f, 1.0f), Eigen::Vector4f(-37.0f, -3.0f, -50.0f, 1.0f), BLUE, true));
    shapes_quad.push_back(Quad({-37.0f, -3.0f, 40.0f}, {-37.0f, -3.0f, -50.0f}, {-25.0f, -3.0f, -50.0f}, {-25.0f, -3.0f, 40.0f}, {BLUE}, true));
    shapes_quad.push_back(Quad({-25.0f, -3.0f, -11.0f}, {-16.0f, -3.0f, -11.0f}, {-16.0f, -3.0f, -8.0f}, {-25.0f, -3.0f, -8.0f}, {BLUE}, true));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-25.0f, -3.0f, -25.5f, 1.0f), Eigen::Vector4f(-16.0f, -3.0f, -11.0f, 1.0f), Eigen::Vector4f(-25.0f, -3.0f, -11.0f, 1.0f), BLUE, true));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-25.0f, -3.0f, -8.0f, 1.0f), Eigen::Vector4f(-16.0f, -3.0f, -8.0f, 1.0f), Eigen::Vector4f(-25.0f, -3.0f, 9.5f, 1.0f), BLUE, true));

    // distant water surfaces (far and near)
    shapes_quad.push_back(Quad({-25.0f, -3.0f, -60.0f}, {-25.0f, -3.0f, -185.0f}, {-25.0f, -3.0f, -185.0f}, {25.0f, -3.0f, -90.0f}, {BLUE}, true));
    shapes_quad.push_back(Quad({25.0f, -3.0f, 90.0f}, {-25.0f, -3.0f, 185.0f}, {-25.0f, -3.0f, 185.0f}, {-25.0f, -3.0f, 60.0f}, {BLUE}, true));

    // top beach surfaces
    shapes_quad.push_back(Quad({-25.0f, -3.0f, -60.0f}, {-24.0f, -2.0f, -60.0f}, {-24.0f, -2.0f, -26.0f}, {-25.0f, -3.0f, -26.0f}, {YELLOW}, false));

    // bottom beach surfaces
    shapes_quad.push_back(Quad({-25.0f, -3.0f, 10.0f}, {-24.0f, -2.0f, 10.0f}, {-24.0f, -2.0f, 60.0f}, {-25.0f, -3.0f, 60.0f}, {YELLOW}, false));

    // mid top beach surfaces
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-25.0f, -3.0f, -26.0f, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, -26.0f, 1.0f), Eigen::Vector4f(-25.0f, -3.0f, -25.5f, 1.0f), YELLOW, false));
    shapes_quad.push_back(Quad({-25.0f, -3.0f, -25.5f}, {-24.0f, -2.0f, -26.0f}, {-14.0f, -2.0f, -12.0f}, {-16.0f, -3.0f, -11.0f}, {YELLOW}, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-16.0f, -3.0f, -11.0f, 1.0f), Eigen::Vector4f(-14.0f, -2.0f, -12.0f, 1.0f), Eigen::Vector4f(-12.5f, -2.5f, -11.0f, 1.0f), YELLOW, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-14.0f, -2.0f, -12.0f, 1.0f), Eigen::Vector4f(-12.5f, -2.0f, -12.0f, 1.0f), Eigen::Vector4f(-12.5f, -2.5f, -11.0f, 1.0f), YELLOW, false));

    // mid bottom beach surfaces
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-25.0f, -3.0f, 9.5f, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, 10.0f, 1.0f), Eigen::Vector4f(-25.0f, -3.0f, 10.0f, 1.0f), YELLOW, false));
    shapes_quad.push_back(Quad({-16.0f, -3.0f, -8.0f}, {-14.0f, -2.0f, -7.0f}, {-24.0f, -2.0f, 10.0f}, {-25.0f, -3.0f, 9.5f}, {YELLOW}, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-16.0f, -3.0f, -8.0f, 1.0f), Eigen::Vector4f(-12.5f, -2.5f, -8.0f, 1.0f), Eigen::Vector4f(-14.0f, -2.0f, -7.0f, 1.0f), YELLOW, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-12.5f, -2.5f, -8.0f, 1.0f), Eigen::Vector4f(-12.5f, -2.0f, -7.0f, 1.0f), Eigen::Vector4f(-14.0f, -2.0f, -7.0f, 1.0f), YELLOW, false));

    // beach waterfall
    shapes_quad.push_back(Quad({-16.0f, -3.0f, -11.0f}, {-12.5f, -2.5f, -11.0f}, {-12.5f, -2.5f, -8.0f}, {-16.0f, -3.0f, -8.0f}, {BLUE}, false));

    // main river
    shapes_quad.push_back(Quad({-12.5f, -2.0f, -12.0f}, {10.0f, -2.0f, -12.0f}, {10.0f, -2.5f, -11.0f}, {-12.5f, -2.5f, -11.0f}, {YELLOW}, false));
    shapes_quad.push_back(Quad({-12.5f, -2.5f, -11.0f}, {10.0f, -2.5f, -11.0f}, {10.0f, -2.5f, -8.0f}, {-12.5f, -2.5f, -8.0f}, {BLUE}, false));
    shapes_quad.push_back(Quad({-12.5f, -2.5f, -8.0f}, {10.0f, -2.5f, -8.0f}, {10.0f, -2.0f, -7.0f}, {-12.5f, -2.0f, -7.0f}, {YELLOW}, false));

    // diagonal river
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-10.0f, -2.0f, -17.0f, 1.0f), Eigen::Vector4f(25.0f, -2.0f, -17.0f, 1.0f), Eigen::Vector4f(10.0f, -2.0f, -12.0f, 1.0f), GREEN, true));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(10.0f, -2.5f, -11.0f, 1.0f), Eigen::Vector4f(10.0f, -2.0f, -12.0f, 1.0f), Eigen::Vector4f(11.0f, -2.5f, -11.25f, 1.0f), YELLOW, false));
    shapes_quad.push_back(Quad({10.0f, -2.0f, -12.0f}, {25.0f, -2.0f, -17.0f}, {25.0f, -2.0f, -16.0f}, {11.0f, -2.5f, -11.25f}, {YELLOW}, false));
    shapes_quad.push_back(Quad({10.0f, -2.5f, -11.0f}, {25.0f, -2.0f, -16.0f}, {25.0f, -2.0f, -13.0f}, {10.0f, -2.5f, -8.0f}, {BLUE}, false));
    shapes_quad.push_back(Quad({10.0f, -2.5f, -8.0f}, {25.0f, -2.0f, -13.0f}, {25.0f, -2.0f, -12.0f}, {11.0f, -2.0f, -7.0f}, {YELLOW}, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(10.0f, -2.5f, -8.0f, 1.0f), Eigen::Vector4f(11.0f, -2.0f, -7.0f, 1.0f), Eigen::Vector4f(10.0f, -2.0f, -7.0f, 1.0f), YELLOW, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(11.0f, -2.0f, -7.0f, 1.0f), Eigen::Vector4f(25.0f, -2.0f, -12.0f, 1.0f), Eigen::Vector4f(25.0f, -2.0f, -7.0f, 1.0f), GREEN, true));

    // waterfall
    shapes_quad.push_back(Quad({25.0f, -2.0f, -22.0f}, {25.0f, -2.0f, -26.0f}, {26.0f, 20.0, -26.0f}, {26.0f, 20.0f, -22.0f}, {TAN}, false));
    shapes_quad.push_back(Quad({25.0f, -2.0f, -26.0f}, {26.0f, 20.0f, -22.0f}, {26.0f, 18.5f, -16.0f}, {25.0f, -2.0f, -16.0f}, {TAN}, false));
    shapes_quad.push_back(Quad({25.0f, -2.0f, -16.0f}, {26.0f, 18.0f, -16.0f}, {26.0f, 18.0f, -13.0f}, {25.0f, -2.0f, -13.0f}, {BLUE}, false));
    shapes_quad.push_back(Quad({25.0f, -2.0f, -13.0f}, {26.0f, 18.5f, -13.0f}, {26.0f, 20.0f, -7.0f}, {25.0f, -2.0f, -7.0f}, {TAN}, false));
    shapes_quad.push_back(Quad({25.0f, -2.0f, -7.0f}, {26.0f, 20.0f, -7.0f}, {26.0f, 20.0, 10.0f}, {25.0f, -2.0f, 10.0f}, {TAN}, false));

    // far cliff (left of waterfall)
    shapes_quad.push_back(Quad({25.0f, -2.0f, -26.0f}, {0.5f, -2.0f, -43.0f}, {0.5f, 11.0f, -43.0f}, {26.0f, 20.0, -26.0f}, {TAN}, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(0.5f, 11.0f, -43.0f, 1.0f), Eigen::Vector4f(0.5f, -2.0f, -43.0f, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, -60.0f, 1.0f), {TAN}, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(0.0f, 15.0f, -55.0f, 1.0f), Eigen::Vector4f(0.5f, 11.0f, -43.0f, 1.0f), Eigen::Vector4f(-24.0f, -2.0f, -60.0f, 1.0f), {GREEN}, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(0.0f, 15.0f, -55.0f, 1.0f), Eigen::Vector4f(26.0f, 20.0, -26.0f, 1.0f), Eigen::Vector4f(0.5f, 11.0f, -43.0f, 1.0f), {GREEN}, false));

    // near cliff (right of waterfall)
    shapes_quad.push_back(Quad({25.0f, -2.0f, 10.0f}, {26.0f, 20.0f, 10.0f}, {10.3f, 14.0f, 25.0f}, {10.3f, -2.0f, 25.0f}, {TAN}, false));
    shapes_quad.push_back(Quad({10.3, -2.0f, 25.0f}, {10.3f, 14.0f, 25.0f}, {0.5f, 19.0f, 37.0f}, {0.5f, -2.0f, 35.0f}, {TAN}, false));
    shapes_quad.push_back(Quad({0.5f, -2.0f, 35.0f}, {0.5f, 19.0f, 37.0f}, {-12.0f, 8.0f, 49.0f}, {-11.75f, -2.0f, 47.5f}, {TAN}, false));
    shapes_quad.push_back(Quad({-11.75f, -2.0f, 47.5f}, {-12.0f, 8.0f, 49.0f}, {-17.0f, 8.0f, 54.0f}, {-24.0f, -2.0f, 60.0f}, {TAN}, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(26.0f, 20.0f, 10.0f, 1.0f), Eigen::Vector4f(15.0f, 19.0f, 30.0f, 1.0f), Eigen::Vector4f(10.3f, 14.0f, 25.0f, 1.0f), {GREEN}, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(15.0f, 19.0f, 30.0f, 1.0f), Eigen::Vector4f(0.5f, 19.0f, 37.0f, 1.0f), Eigen::Vector4f(10.3f, 14.0f, 25.0f, 1.0f), {GREEN}, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(0.5f, 19.0f, 37.0f, 1.0f), Eigen::Vector4f(-10.0f, 15.0f, 52.0f, 1.0f), Eigen::Vector4f(-12.0f, 8.0f, 49.0f, 1.0f), {GREEN}, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-12.0f, 8.0f, 49.0f, 1.0f), Eigen::Vector4f(-10.0f, 15.0f, 52.0f, 1.0f), Eigen::Vector4f(-17.0f, 8.0f, 54.0f, 1.0f), {GREEN}, false));

    // island
    shapes_quad.push_back(Quad({-150.0f, -3.0f, 10.0f}, {-45.0f, -3.0f, 0.0f}, {-37.0f, -3.0f, 15.0f}, {-50.0f, -3.0f, 40.0f}, {MEDGREEN}, false));
    shapes_quad.push_back(Quad({-150.0f, -3.0f, -10.0f}, {-60.0f, -3.0f, -50.0f}, {-37.0f, -3.0f, -15.0f}, {-45.0f, -3.0f, 0.0f}, {MEDGREEN}, false));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(-45.0f, -3.0f, 0.0f, 1.0f), Eigen::Vector4f(-150.0f, -3.0f, 10.0f, 1.0f), Eigen::Vector4f(-150.0f, -3.0f, -10.0f, 1.0f), MEDGREEN, false));

    // island mountains
    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 15.0f, 10.0f, 15.0f, {DKGREEN, DKGREEN, NIGHTGREEN, NIGHTGREEN, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-52.0f, -2.0, 20.0f);

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 15.0f, 16.0f, 15.0f, {DKGREEN, DKGREEN, NIGHTGREEN, NIGHTGREEN, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-58.0f, -2.0, 5.0f);

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 15.0f, 13.0f, 15.0f, {DKGREEN, DKGREEN, NIGHTGREEN, NIGHTGREEN, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-53.0f, -2.0, -10.0f);

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 20.0f, 15.0f, 20.0f, {DKGREEN, DKGREEN, NIGHTGREEN, NIGHTGREEN, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-65.0f, -2.0, -24.0f);

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 15.0f, {DKBLUE, DKBLUE, NIGHTBLUE, NIGHTBLUE, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-67.0f, -2.0, 13.0f);

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 20.0f, 30.0f, 20.0f, {DKBLUE, DKBLUE, NIGHTBLUE, NIGHTBLUE, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-70.0f, -2.0, 0.0f);

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 22.0f, 28.0f, 22.0f, {DKBLUE, DKBLUE, NIGHTBLUE, NIGHTBLUE, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-75.0f, -2.0, -15.0f);

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 15.0f, 38.0f, 15.0f, {WHITE, WHITE, GRAY, GRAY, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-76.0f, -2.0, 7.5f);

    shapes_pyramid.push_back(Pyramid(0.0f, 0.0f, 0.0f, 15.0f, 44.0f, 15.0f, {WHITE, WHITE, GRAY, GRAY, BLACK}, false, {"bottom"}));
    shapes_pyramid.back().rotate(0.0f, 45.0f, 0.0f, "roll-pitch-yaw");
    shapes_pyramid.back().translate(-78.0f, -2.0, -4.0f);

    // // cloud
    // shapes_triangle.push_back(Surface(Eigen::Vector4f(0.5f, 10.5f, -15.0f, 1.0f), Eigen::Vector4f(4.0f, 11.0f, -15.0f, 1.0f), Eigen::Vector4f(2.5f, 9.0f, -15.0f, 1.0f), WHITE));
    // shapes_triangle.push_back(Surface(Eigen::Vector4f(0.0f, 10.0f, -15.0f, 1.0f), Eigen::Vector4f(2.0f, 12.5f, -15.0f, 1.0f), Eigen::Vector4f(3.0f, 10.5f, -15.0f, 1.0f), WHITE));
    // shapes_triangle.push_back(Surface(Eigen::Vector4f(1.2f, 10.5f, -15.0f, 1.0f), Eigen::Vector4f(3.5f, 12.0f, -15.0f, 1.0f), Eigen::Vector4f(4.5f, 10.0f, -15.0f, 1.0f), WHITE));
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

    return all_surfaces;
}

void Map::push_surfaces(const vector<Surface> &temp_surfaces)
{
    for (const auto &surface : temp_surfaces)
    {
        all_surfaces.push_back(surface);
    }
}

// Return reference to RectPrism object
RectPrism &Map::get_rect_prism(const int &index)
{
    return shapes_rect_prism[index];
}

// Return reference to Pyramid object
Pyramid &Map::get_pyramid(const int &index)
{
    return shapes_pyramid[index];
}

// Return reference to Rect object
Rect &Map::get_rect(const int &index)
{
    return shapes_rect[index];
}

// Return reference to Quad object
Quad &Map::get_quad(const int &index)
{
    return shapes_quad[index];
}

// Return reference to Surface (triangle) object
Surface &Map::get_triangle(const int &index)
{
    return shapes_triangle[index];
}