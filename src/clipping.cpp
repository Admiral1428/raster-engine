#include "clipping.hpp"

vector<Eigen::Vector4f> clip(const Eigen::Vector4f &c0, const Eigen::Vector4f &c1, const Eigen::Vector4f &c2)
{
    vector<bool> c0_inside = in_clip_space(c0);
    vector<bool> c1_inside = in_clip_space(c1);
    vector<bool> c2_inside = in_clip_space(c2);

    bool c0_all_inside = all_of(c0_inside.begin(), c0_inside.end(), [](bool v)
                                { return v; });
    bool c1_all_inside = all_of(c1_inside.begin(), c1_inside.end(), [](bool v)
                                { return v; });
    bool c2_all_inside = all_of(c2_inside.begin(), c2_inside.end(), [](bool v)
                                { return v; });

    // all points in clip space (x and y within (-1, 1), z within (0, 1))
    if (c0_all_inside && c1_all_inside && c2_all_inside)
    {
        return {c0, c1, c2};
    }
    // all three points outside clip space
    else if (!c0_all_inside && !c1_all_inside && !c2_all_inside)
    {
        // all three points outside single clipping plane
        if (c0_inside == c1_inside && c0_inside == c2_inside)
        {
            return {};
        }
        // points outside different clipping planes, so proceed to subsequent logic
    }
    // some points in clip space, so proceed to subsequent logic

    vector<Eigen::Vector4f> input_points = {c0, c1, c2};
    vector<Eigen::Vector4f> result_points = clip_algorithm(input_points);

    if (result_points.size() == 3)
    {
        return result_points;
    }
    // more than 3 points (polygon)
    else if (result_points.size() > 3)
    {
        vector<Eigen::Vector4f> multi_triangle_points = split_polygon(result_points);
        return multi_triangle_points;
    }

    return {}; // any other case
}

vector<bool> in_clip_space(const Eigen::Vector4f &c)
{
    vector<bool> in_clipping_plane;

    in_clipping_plane.push_back(c(0) >= -c(3)); // within left boundary
    in_clipping_plane.push_back(c(0) <= c(3));  // within right boundary
    in_clipping_plane.push_back(c(1) >= -c(3)); // within bottom boundary
    in_clipping_plane.push_back(c(1) <= c(3));  // within top boundary
    in_clipping_plane.push_back(c(2) >= -c(3)); // within near boundary
    in_clipping_plane.push_back(c(2) <= c(3));  // within far boundary

    return in_clipping_plane;
}

vector<Eigen::Vector4f> clip_algorithm(vector<Eigen::Vector4f> &points)
{
    vector<Eigen::Vector4f> result_points_left;
    vector<Eigen::Vector4f> result_points_right;
    vector<Eigen::Vector4f> result_points_bottom;
    vector<Eigen::Vector4f> result_points_top;
    vector<Eigen::Vector4f> result_points_near;
    vector<Eigen::Vector4f> result_points_far;

    // clipping against each plane, using results from previous step
    result_points_left = clip_against_plane(points, 0);
    result_points_right = clip_against_plane(result_points_left, 1);
    result_points_bottom = clip_against_plane(result_points_right, 2);
    result_points_top = clip_against_plane(result_points_bottom, 3);
    result_points_near = clip_against_plane(result_points_top, 4);
    result_points_far = clip_against_plane(result_points_near, 5);

    return result_points_far;
}

// perform clipping against given plane using Sutherland-Hodgman algorithm
vector<Eigen::Vector4f> clip_against_plane(vector<Eigen::Vector4f> &points, const int &plane)
{
    vector<vector<bool>> points_inside;
    vector<Eigen::Vector4f> result_points;
    int first;
    int second;
    Eigen::Vector4f pint;

    for (auto &p : points)
    {
        points_inside.push_back(in_clip_space(p));
    }
    for (int i{0}; i < points_inside.size(); ++i)
    {
        // set indices for vertices
        first = i;
        if (i == points_inside.size() - 1)
        {
            second = 0;
        }
        else
        {
            second = i + 1;
        }

        // if both vertices inside clipping plane
        if (points_inside[first][plane] && points_inside[second][plane])
        {
            // add second vertex to output
            result_points.push_back(points[second]);
        }
        // if first vertex outside and second vertex inside
        else if (!points_inside[first][plane] && points_inside[second][plane])
        {
            // get intersection with clipping plane
            pint = get_intersect_point(points[first], points[second], plane);

            // add intersection with edge and second point
            result_points.push_back(pint);
            result_points.push_back(points[second]);
        }
        // if first vertex inside and second vertex outside
        else if (points_inside[first][plane] && !points_inside[second][plane])
        {
            // get intersection with clipping plane
            pint = get_intersect_point(points[first], points[second], plane);

            // add intersection with edge
            result_points.push_back(pint);
        }
    }

    return result_points;
}

Eigen::Vector4f get_intersect_point(const Eigen::Vector4f &p1, const Eigen::Vector4f &p2, const int &plane)
{
    float d1;
    float d2;

    // get signed distances based on clipping plane criteria
    switch (plane)
    {
    case 0: // left boundary (w + x = 0)
    {
        d1 = p1(3) + p1(0);
        d2 = p2(3) + p2(0);
        break;
    }
    case 1: // right boundary (w - x = 0)
    {
        d1 = p1(3) - p1(0);
        d2 = p2(3) - p2(0);
        break;
    }
    case 2: // bottom boundary (w + y = 0)
    {
        d1 = p1(3) + p1(1);
        d2 = p2(3) + p2(1);
        break;
    }
    case 3: // top boundary (w - y = 0)
    {
        d1 = p1(3) - p1(1);
        d2 = p2(3) - p2(1);
        break;
    }
    case 4: // near boundary (w + z = 0)
    {
        d1 = p1(3) + p1(2);
        d2 = p2(3) + p2(2);
        break;
    }
    case 5: // far boundary (w - z = 0)
    {
        d1 = p1(3) - p1(2);
        d2 = p2(3) - p2(2);
        break;
    }
    }

    // interpolation parameter
    float t = d1 / (d1 - d2);

    // interpolated final point
    return Eigen::Vector4f(p1(0) + t * (p2(0) - p1(0)),
                           p1(1) + t * (p2(1) - p1(1)),
                           p1(2) + t * (p2(2) - p1(2)),
                           p1(3) + t * (p2(3) - p1(3)));
}

// split polygon into multiple triangles
vector<Eigen::Vector4f> split_polygon(vector<Eigen::Vector4f> &points)
{
    /* Vertices of polygon already in correct order after
    Sutherland-Hodgman algorithm, so no need to re-order */

    Eigen::Vector4f p0;
    Eigen::Vector4f p1;
    Eigen::Vector4f p2;
    vector<Eigen::Vector4f> final_points;
    vector<Eigen::Vector4f> remaining_points = points;

    while (remaining_points.size() != 3)
    {
        // pick pivot vertex
        p0 = remaining_points[0];

        // pick two adjacent vertices
        p1 = remaining_points[1];
        p2 = remaining_points.back();

        // create triangle using points
        final_points.push_back(p0);
        final_points.push_back(p1);
        final_points.push_back(p2);

        // remove pivot vertex
        remaining_points.erase(remaining_points.begin());
    }

    // create last triangles using remaining points
    final_points.push_back(remaining_points[0]);
    final_points.push_back(remaining_points[1]);
    final_points.push_back(remaining_points[2]);

    return final_points;
}