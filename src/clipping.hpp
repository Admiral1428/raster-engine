#ifndef CLIPPING_HPP
#define CLIPPING_HPP

#include <vector>
#include <algorithm>
#include <vector>
#include <Eigen/Dense>
#include "point.hpp"

using std::all_of;
using std::vector;

// Store position and texture coordinates
struct Vertex
{
    Eigen::Vector4f position;
    Eigen::Vector2f uv;
};

vector<Vertex> clip(const Eigen::Vector4f &c0, const Eigen::Vector4f &c1, const Eigen::Vector4f &c2,
                    const Eigen::Vector2f &uv0, const Eigen::Vector2f &uv1, const Eigen::Vector2f &uv2);
vector<bool> in_clip_space(const Eigen::Vector4f &c);
vector<Vertex> clip_algorithm(vector<Vertex> &points);
vector<Vertex> clip_against_plane(vector<Vertex> &points, const int &plane);
Vertex get_intersect_point(const Vertex &p1, const Vertex &p2, const int &plane);
vector<Vertex> split_polygon(vector<Vertex> &points);

#endif