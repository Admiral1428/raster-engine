#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <numbers>
#include <cmath>
#include <cstdlib>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <initializer_list>
#include <SDL3/SDL.h>
#include "constants.h"
#include "point.h"
#include "surface.hpp"

using std::abs;
using std::array;
using std::fabs;
using std::fill;
using std::max;
using std::min;
using std::size_t;
using std::string;
using std::tan;
using std::vector;
using std::numbers::pi;

using Float2DVector = std::vector<std::vector<float>>;

// class defining Renderer perspective
class Renderer
{
private:
    float n;    // near clipping plane
    float f;    // far clipping plane
    float fov;  // field of view in degrees
    int width;  // screen width
    int height; // screen height
    Float2DVector z_buffer;
    array<array<float, 4>, 4> projection_matrix;

public:
    Renderer(); // default constructor (initializes object to default state with no arguments)
    Renderer(const float &_n, const float &_f, const float &_fov, const float &_width, const float &_height);
    Renderer(const Renderer &);            // copy constructor
    ~Renderer();                           // destructor
    Renderer &operator=(const Renderer &); // copy/assignment operator
    void resize_z_buffer();
    void calc_projection_matrix();
    void draw_surfaces(SDL_Renderer &renderer, vector<Surface> &surfaces);
    Point matrix_mult(const array<array<float, 4>, 4> &m, const Point &p);
    vector<Point> clip(const Point &c0, const Point &c1, const Point &c2);
    bool in_clip_space(const Point &c);
    void normalize_point(Point &c);
    void rasterize_point(Point &c);
    vector<int> get_bounding_box(const Point &r0, const Point &r1, const Point &r2);
    Point get_barycentric_coords(const Point &r0, const Point &r1, const Point &r2, const Point &p);
    bool point_in_triangle(const Point &barycentric_coords);
    float get_ndc_depth(const Point &barycentric_coords, const Point &c0, const Point &c1, const Point &c2);
    void set_width_height(const float &w, const float &h);
};

// implementation
Renderer::Renderer() : n(PLANE_N), f(PLANE_F), fov(FOV), width(WIDTH), height(HEIGHT)
{
    resize_z_buffer();
}
Renderer::Renderer(const float &_n, const float &_f, const float &_fov, const float &_width, const float &_height)
    : n(_n), f(_f), fov(_fov), width(_width), height(_height)
{
    resize_z_buffer();
}
Renderer::Renderer(const Renderer &c)
{
    n = c.n;
    f = c.f;
    fov = c.fov;
    width = c.width;
    height = c.height;
    z_buffer = c.z_buffer;
    projection_matrix = c.projection_matrix;
}

Renderer::~Renderer() {}

Renderer &Renderer::operator=(const Renderer &c)
{
    if (this != &c)
    {
        n = c.n;
        f = c.f;
        fov = c.fov;
        width = c.width;
        height = c.height;
        z_buffer = c.z_buffer;
        projection_matrix = c.projection_matrix;
    }
    return *this;
}

void Renderer::resize_z_buffer()
{
    z_buffer.assign(static_cast<size_t>(width), vector<float>(static_cast<size_t>(height)));
}

void Renderer::calc_projection_matrix()
{
    float S = 1.0f / tan(fov * 0.5f * pi / 180.0f); // scaling factor
    projection_matrix = {
        {{S, 0.0f, 0.0f, 0.0f},
         {0.0f, S, 0.0f, 0.0f},
         {0.0f, 0.0f, -f / (f - n), -(f * n) / (f - n)},
         {0.0f, 0.0f, -1.0f, 0.0f}}};
}

void Renderer::draw_surfaces(SDL_Renderer &renderer, vector<Surface> &surfaces)
{
    // initialize z buffer with 1.0 depth values
    for (auto &row : z_buffer)
    {
        fill(row.begin(), row.end(), 1.0f);
    }

    // calculate projection matrix
    calc_projection_matrix();

    // initialize variables
    vector<Point> points;
    Point c0;
    Point c1;
    Point c2;
    vector<Point> homog_points;
    Point ndc_0;
    Point ndc_1;
    Point ndc_2;
    Point r0;
    Point r1;
    Point r2;
    vector<int> bounding_box;
    Color surf_color;
    Point p;
    Point barycentric_coords;
    float z_ndc;

    // perform drawing for each surface
    for (auto &surface : surfaces)
    {
        // transform points with projection matrix
        points = surface.get_points();
        c0 = matrix_mult(projection_matrix, points[0]);
        c1 = matrix_mult(projection_matrix, points[1]);
        c2 = matrix_mult(projection_matrix, points[2]);

        // perform clipping and return homogeneous coordinates
        homog_points = clip(c0, c1, c2);

        // loop through every third element to get each resulting triangle
        for (int i{0}; i < homog_points.size(); i += 3)
        {
            // get normalized device coordinates
            ndc_0 = homog_points[i];
            ndc_1 = homog_points[i + 1];
            ndc_2 = homog_points[i + 2];
            normalize_point(ndc_0);
            normalize_point(ndc_1);
            normalize_point(ndc_2);

            // rasterize triangle vertices to screen space after normalizing
            r0 = ndc_0;
            r1 = ndc_1;
            r2 = ndc_2;
            rasterize_point(r0);
            rasterize_point(r1);
            rasterize_point(r2);

            // get bounding box of these screen vertices
            bounding_box = get_bounding_box(r0, r1, r2);

            // set color
            surf_color = surface.get_color();
            SDL_SetRenderDrawColor(&renderer, surf_color.r, surf_color.g, surf_color.b, surf_color.a);

            // loop through bounding box to determine triangle points
            for (int x{bounding_box[0]}; x <= bounding_box[1]; ++x)
            {
                p.x = static_cast<float>(x);
                for (int y{bounding_box[2]}; y <= bounding_box[3]; ++y)
                {
                    p.y = static_cast<float>(y);
                    // get and process barycentric coordinates
                    barycentric_coords = get_barycentric_coords(r0, r1, r2, p);

                    if (point_in_triangle(barycentric_coords))
                    {
                        z_ndc = get_ndc_depth(barycentric_coords, homog_points[i], homog_points[i + 1], homog_points[i + 2]);
                        if (z_ndc < z_buffer[x][y])
                        {
                            z_buffer[x][y] = z_ndc;
                            SDL_RenderPoint(&renderer, x, y);
                        }
                    }
                }
            }
        }
    }
}

Point Renderer::matrix_mult(const array<array<float, 4>, 4> &m, const Point &p)
{
    Point c;
    c.x = p.x * m[0][0] + p.y * m[0][1] + p.z * m[0][2] + p.w * m[0][3];
    c.y = p.x * m[1][0] + p.y * m[1][1] + p.z * m[1][2] + p.w * m[1][3];
    c.z = p.x * m[2][0] + p.y * m[2][1] + p.z * m[2][2] + p.w * m[2][3];
    c.w = p.x * m[3][0] + p.y * m[3][1] + p.z * m[3][2] + p.w * m[3][3];
    return c;
}

vector<Point> Renderer::clip(const Point &c0, const Point &c1, const Point &c2)
{
    bool c0_inside = in_clip_space(c0);
    bool c1_inside = in_clip_space(c1);
    bool c2_inside = in_clip_space(c2);

    // all points in clip space (x and y within (-1, 1), z within (0, 1))
    if (c0_inside && c1_inside && c2_inside)
    {
        return {c0, c1, c2};
    }
    // all three points outside single clipping plane

    // some points in clip space, return 1 or 2 or 3 triangles

    return {};
}

bool Renderer::in_clip_space(const Point &c)
{
    return c.x <= c.w && c.x >= -c.w && c.y <= c.w && c.y >= -c.w && c.z <= c.w && c.z >= -c.w;
}

void Renderer::normalize_point(Point &c)
{
    if (c.w != 0.0f)
    {
        c.x /= c.w;
        c.y /= c.w;
        c.z /= c.w;
        c.w /= c.w;
    }
}

void Renderer::rasterize_point(Point &c)
{
    float x = (c.x + 1) * 0.5 * width;
    float y = (1 - (c.y + 1) * 0.5) * height;
    c.x = x;
    c.y = y;
}

vector<int> Renderer::get_bounding_box(const Point &r0, const Point &r1, const Point &r2)
{
    int min_x = static_cast<int>(min({r0.x, r1.x, r2.x}));
    int max_x = static_cast<int>(max({r0.x, r1.x, r2.x}));
    int min_y = static_cast<int>(min({r0.y, r1.y, r2.y}));
    int max_y = static_cast<int>(max({r0.y, r1.y, r2.y}));

    // Limit to screen dimensions
    min_x = max(0, min_x);
    max_x = min(width - 1, max_x);
    min_y = max(0, min_y);
    max_y = min(height - 1, max_y);

    return {min_x, max_x, min_y, max_y};
}

Point Renderer::get_barycentric_coords(const Point &r0, const Point &r1, const Point &r2, const Point &p)
{
    Point v0 = {r1.x - r0.x, r1.y - r0.y};
    Point v1 = {r2.x - r0.x, r2.y - r0.y};
    Point v2 = {p.x - r0.x, p.y - r0.y};

    // dot products of vectors
    float dot_00 = v0.x * v0.x + v0.y * v0.y;
    float dot_01 = v0.x * v1.x + v0.y * v1.y;
    float dot_11 = v1.x * v1.x + v1.y * v1.y;
    float dot_20 = v2.x * v0.x + v2.y * v0.y;
    float dot_21 = v2.x * v1.x + v2.y * v1.y;

    float denom = (dot_00 * dot_11 - dot_01 * dot_01);
    float beta = (dot_11 * dot_20 - dot_01 * dot_21) / denom;
    float gamma = (dot_00 * dot_21 - dot_01 * dot_20) / denom;
    float alpha = 1.0f - beta - gamma;

    Point result{alpha, beta, gamma};
    return result;
}

bool Renderer::point_in_triangle(const Point &barycentric_coords)
{
    float tol = 1e-6f;

    /* If all coordinates non-negative, coordinate inside or on edge of triangle...
    Not checking if all add to 1 since this should already be true */
    return (barycentric_coords.x >= -tol && barycentric_coords.y >= -tol && barycentric_coords.z >= -tol);
}

float Renderer::get_ndc_depth(const Point &barycentric_coords, const Point &c0, const Point &c1, const Point &c2)
{
    if (c0.w != 0.0f && c1.w != 0.0f && c2.w != 0.0f)
    {
        float interp_z_over_w = barycentric_coords.x * (c0.z / c0.w) + barycentric_coords.y * (c1.z / c1.w) + barycentric_coords.z * (c2.z / c2.w);
        return interp_z_over_w;
    }
    return 1.0f; // edge case for divide by zero
}

// Change width and height vars based on screen resize, and resize z_buffer
void Renderer::set_width_height(const float &w, const float &h)
{
    width = static_cast<int>(w);
    height = static_cast<int>(h);
    resize_z_buffer();
}

#endif