#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include <Eigen/Dense>
#include "surface.hpp"
#include "rectprism.hpp"
#include "rect.hpp"
#include "quad.hpp"
#include "pyramid.hpp"
#include "tree.hpp"
#include "house.hpp"
#include "bridge.hpp"

using std::string;
using std::vector;

// class defining Renderer perspective
class Map
{
private:
    vector<RectPrism> shapes_rect_prism;
    vector<Pyramid> shapes_pyramid;
    vector<Tree> shapes_tree;
    vector<House> shapes_house;
    vector<Bridge> shapes_bridge;
    vector<Rect> shapes_rect;
    vector<Quad> shapes_quad;
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
    Tree &get_tree(const int &index);
    House &get_house(const int &index);
    Bridge &get_bridge(const int &index);
    Rect &get_rect(const int &index);
    Quad &get_quad(const int &index);
    Surface &get_triangle(const int &index);
};

#endif