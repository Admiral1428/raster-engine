#ifndef POINT_HPP
#define POINT_HPP

#include <array>
#include <vector>
#include <algorithm>

using std::array;
using std::max;
using std::min;
using std::vector;

struct Point
{
    float x; // + right
    float y; // + up
    float z; // + towards the screen
    float w; // scaling factor
};

Point matrix_mult(const array<array<float, 4>, 4> &m, const Point &p);
void normalize_point(Point &c);
void rasterize_point(Point &c, const int &width, const int &height);
vector<int> get_bounding_box(const Point &r0, const Point &r1, const Point &r2, const int &width, const int &height);
Point get_barycentric_coords(const Point &r0, const Point &r1, const Point &r2, const Point &p);
bool point_in_triangle(const Point &barycentric_coords, const float &tol);
double get_ndc_depth(const Point &barycentric_coords, const Point &c0, const Point &c1, const Point &c2);

#endif