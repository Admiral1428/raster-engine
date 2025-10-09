#include "map.hpp"

Map::Map()
{
    // right tree
    shapes_rect_prism.push_back(RectPrism(2.5f, -1.0f, -7.0f, 0.5f, 2.0f, 0.5f, {BROWN, BROWN, TAN, TAN, BROWN, BROWN}));
    shapes_pyramid.push_back(Pyramid(2.5f, 0.0f, -7.0f, 2.0f, 2.0f, 2.0f, {DKGREEN, DKGREEN, MEDGREEN, MEDGREEN, BLACK}));

    // left tree
    shapes_rect_prism.push_back(RectPrism(-2.8f, 0.0f, -10.0f, 0.75f, 4.0f, 0.75f, {BROWN, BROWN, TAN, TAN, BROWN, BROWN}));
    shapes_pyramid.push_back(Pyramid(-2.8f, 2.0f, -10.0f, 3.0f, 3.0f, 3.0f, {DKGREEN, DKGREEN, MEDGREEN, MEDGREEN, BLACK}));

    // grass surface
    shapes_rect.push_back(Rect(0.0f, -2.0f, -10.0f, 10.0f, 0.0f, 10.0f, {GREEN}, true));

    // cloud
    shapes_triangle.push_back(Surface(Eigen::Vector4f(0.5f, 10.5f, -15.0f, 1.0f), Eigen::Vector4f(4.0f, 11.0f, -15.0f, 1.0f), Eigen::Vector4f(2.5f, 9.0f, -15.0f, 1.0f), WHITE));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(0.0f, 10.0f, -15.0f, 1.0f), Eigen::Vector4f(2.0f, 12.5f, -15.0f, 1.0f), Eigen::Vector4f(3.0f, 10.5f, -15.0f, 1.0f), WHITE));
    shapes_triangle.push_back(Surface(Eigen::Vector4f(1.2f, 10.5f, -15.0f, 1.0f), Eigen::Vector4f(3.5f, 12.0f, -15.0f, 1.0f), Eigen::Vector4f(4.5f, 10.0f, -15.0f, 1.0f), WHITE));

    // // triangle aligned with x-y plane used for clipping checks (translating 1.0 at a time)
    // shapes_triangle.push_back(Surface(Eigen::Vector4f(-20.0f, -10.0f, -90.0f, 1.0f), Eigen::Vector4f(20.0f, 10.0f, -90.0f, 1.0f), Eigen::Vector4f(40.0f, -25.0f, -90.0f, 1.0f), RED, true));

    // triangle aligned with z-y plane used for clipping checks (translating 0.05 at a time)
    // shapes_triangle.push_back(Surface(Eigen::Vector4f(-1.0f, 0.0f, -1.0f, 1.0f), Eigen::Vector4f(-1.0f, 0.0f, -3.0f, 1.0f), Eigen::Vector4f(-1.0f, 2.0f, -3.0f, 1.0f), RED, true));
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

// Return reference to Surface (triangle) object
Surface &Map::get_triangle(const int &index)
{
    return shapes_triangle[index];
}