#ifndef CLIPPING_HPP
#define CLIPPING_HPP

#include <vector>
#include <algorithm>
#include <vector>
#include <Eigen/Dense>
#include "point.hpp"

using std::all_of;
using std::vector;

vector<Eigen::Vector4f> clip(const Eigen::Vector4f &c0, const Eigen::Vector4f &c1, const Eigen::Vector4f &c2);
vector<bool> in_clip_space(const Eigen::Vector4f &c);
vector<Eigen::Vector4f> clip_algorithm(vector<Eigen::Vector4f> &points);
vector<Eigen::Vector4f> clip_against_plane(vector<Eigen::Vector4f> &points, const int &plane);
Eigen::Vector4f get_intersect_point(const Eigen::Vector4f &p1, const Eigen::Vector4f &p2, const int &plane);
vector<Eigen::Vector4f> split_polygon(vector<Eigen::Vector4f> &points);

#endif