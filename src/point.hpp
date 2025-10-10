#ifndef POINT_HPP
#define POINT_HPP

#include <array>
#include <vector>
#include <algorithm>
#include <cmath>
#include <Eigen/Dense>

using std::array;
using std::max;
using std::min;
using std::round;
using std::vector;

void normalize_point(Eigen::Vector4f &c);
void normalize_to_unit_vector(Eigen::Vector3f &c);
void rasterize_point(Eigen::Vector4f &c, const int &width, const int &height);
Eigen::Vector4i get_bounding_box(const Eigen::Vector4f &r0, const Eigen::Vector4f &r1, const Eigen::Vector4f &r2, const int &width, const int &height);
Eigen::Vector3f get_barycentric_coords(const Eigen::Vector4f &r0, const Eigen::Vector4f &r1, const Eigen::Vector4f &r2, const Eigen::Vector2f &p);
bool point_in_triangle(const Eigen::Vector3f &barycentric_coords, const float &tol);
double get_ndc_depth(const Eigen::Vector3f &barycentric_coords, const Eigen::Vector4f &c0, const Eigen::Vector4f &c1, const Eigen::Vector4f &c2);
bool is_surface_visible(const Eigen::Vector4f &v0, const Eigen::Vector4f &v1, const Eigen::Vector4f &v2);
Eigen::Vector3f get_normal_vector(const Eigen::Vector4f &c0, const Eigen::Vector4f &c1, const Eigen::Vector4f &c2);

#endif