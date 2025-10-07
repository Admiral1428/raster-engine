#ifndef CLIPPING_HPP
#define CLIPPING_HPP

#include <vector>
#include <algorithm>
#include <vector>
#include "point.hpp"

using std::all_of;
using std::vector;

vector<Point> clip(const Point &c0, const Point &c1, const Point &c2);
vector<bool> in_clip_space(const Point &c);
vector<Point> clip_algorithm(vector<Point> &points);
vector<Point> clip_against_plane(vector<Point> &points, const int &plane);
Point get_intersect_point(const Point &p1, const Point &p2, const int &plane);
vector<Point> split_polygon(vector<Point> &points);

#endif