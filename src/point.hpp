#ifndef POINT_HPP
#define POINT_HPP

#include <array>
#include <vector>
#include <algorithm>
#include <cmath>
#include <Eigen/Dense>
#include "constants.h"

using std::array;
using std::max;
using std::min;
using std::round;
using std::vector;

void normalize_point(Eigen::Vector4f &c);
void rasterize_point(Eigen::Vector4f &c, const int &width, const int &height);
Eigen::Vector4i get_bounding_box(const Eigen::Vector4f &r0, const Eigen::Vector4f &r1, const Eigen::Vector4f &r2,
                                 const int &width, const int &height);
vector<Eigen::VectorXf> get_barycentric_coords(const Eigen::Vector4f &r0, const Eigen::Vector4f &r1, const Eigen::Vector4f &r2,
                                               const Eigen::VectorXf &px, const Eigen::VectorXf &py);
vector<Eigen::VectorXf> get_points_in_triangle(const vector<Eigen::VectorXf> barycentric_coords,
                                               const Eigen::VectorXf &px, const Eigen::VectorXf &py);
vector<Eigen::VectorXf> get_points_on_triangle_boundary(const vector<Eigen::VectorXf> &barycentric_coords,
                                                        const Eigen::VectorXf &px, const Eigen::VectorXf &py);
Eigen::VectorXf get_ndc_depth(const vector<Eigen::VectorXf> &barycentric_and_pixels,
                              const Eigen::Vector4f &c0, const Eigen::Vector4f &c1, const Eigen::Vector4f &c2);
Eigen::MatrixXf get_uv_texture(const vector<Eigen::VectorXf> &barycentric_and_pixels,
                               const Eigen::Vector4f &c0, const Eigen::Vector4f &c1, const Eigen::Vector4f &c2,
                               const Eigen::Vector2f uv0, const Eigen::Vector2f uv1, const Eigen::Vector2f uv2);
bool is_surface_visible(const Eigen::Vector4f &v0, const Eigen::Vector4f &v1, const Eigen::Vector4f &v2);
Eigen::Vector3f get_normal_vector(const Eigen::Vector4f &c0, const Eigen::Vector4f &c1, const Eigen::Vector4f &c2);

#endif