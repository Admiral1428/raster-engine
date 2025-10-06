#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include "surface.hpp"
#include "rectprism.hpp"
#include "rect.hpp"
#include "pyramid.hpp"

using std::string;
using std::vector;

// class defining Renderer perspective
class Map
{
private:
    vector<RectPrism> shapes_rect_prism;
    vector<Pyramid> shapes_pyramid;
    vector<Rect> shapes_rect;
    vector<Surface> shapes_triangle;
    vector<Surface> all_surfaces;

public:
    Map();                                // default constructor (initializes object to default state with no arguments)
    Map(const Map &) = delete;            // prevent copy
    ~Map();                               // destructor
    Map &operator=(const Map &) = delete; // prevent copy/assignment
    vector<Surface> &get_map_surfaces();
    void push_surfaces(const vector<Surface> &temp_surfaces);
    RectPrism &get_rect_prism(const int &index);
    Pyramid &get_pyramid(const int &index);
    Rect &get_rect(const int &index);
    Surface &get_triangle(const int &index);
};

Map::Map()
{
    // right tree
    shapes_rect_prism.push_back(RectPrism(2.5f, -1.0f, -7.0f, 0.5f, 2.0f, 0.5f, {BROWN, BROWN, TAN, TAN, BROWN, BROWN}));
    shapes_pyramid.push_back(Pyramid(2.5f, 0.0f, -7.0f, 2.0f, 2.0f, 2.0f, {DKGREEN, DKGREEN, MEDGREEN, MEDGREEN, BLACK}));

    // left tree
    shapes_rect_prism.push_back(RectPrism(-2.8f, 0.0f, -10.0f, 0.75f, 4.0f, 0.75f, {BROWN, BROWN, TAN, TAN, BROWN, BROWN}));
    shapes_pyramid.push_back(Pyramid(-2.8f, 2.0f, -10.0f, 3.0f, 3.0f, 3.0f, {DKGREEN, DKGREEN, MEDGREEN, MEDGREEN, BLACK}));

    // grass surface
    shapes_rect.push_back(Rect(0.0f, -2.0f, -10.0f, 10.0f, 0.0f, 10.0f, GREEN, true));

    // cloud
    shapes_triangle.push_back(Surface(Point{0.5f, 10.5f, -15.0f, 1.0f}, Point{4.0f, 11.0f, -15.0f, 1.0f}, Point{2.5f, 9.0f, -15.0f, 1.0f}, WHITE));
    shapes_triangle.push_back(Surface(Point{0.0f, 10.0f, -15.0f, 1.0f}, Point{2.0f, 12.5f, -15.0f, 1.0f}, Point{3.0f, 10.5f, -15.0f, 1.0f}, WHITE));
    shapes_triangle.push_back(Surface(Point{1.2f, 10.5f, -15.0f, 1.0f}, Point{3.5f, 12.0f, -15.0f, 1.0f}, Point{4.5f, 10.0f, -15.0f, 1.0f}, WHITE));
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

#endif