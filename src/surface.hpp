#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <vector>
#include <cstdlib>
#include <string>
#include <array>
#include "constants.h"
#include "point.h"
#include "gridpoint.h"

using std::abs;
using std::array;
using std::max;
using std::min;
using std::string;
using std::vector;

// class defining a triangular surface
class Surface
{
private:
    Point p0; // original coordinates
    Point p1;
    Point p2;
    GridPoint c0; // transformed into camera perspective
    GridPoint c1;
    GridPoint c2;
    Color vertex_color;
    Color edge_color;

public:
    Surface(); // default constructor (initializes object to default state with no arguments)
    Surface(const Point &_p0, const Point &_p1, const Point &_p2,
            const Color &_edge_color = RED, const Color &_vertex_color = WHITE);
    Surface(const Surface &);            // copy constructor
    ~Surface();                          // destructor
    Surface &operator=(const Surface &); // copy/assignment operator
    void matrix_mult(const array<array<float, 4>, 4> &m, Point &c);
    void transform_to_camera(const array<array<float, 4>, 4> &m, const int &width, const int &height);
    GridPoint createGridPointFromPoint(const Point &p, const int &width, const int &height);
    void draw_vertices(SDL_Renderer &renderer, const int &width, const int &height);
    vector<GridPoint> get_edge(const GridPoint &ca, const GridPoint &cb);
    void line_low(const int &x0, const int &y0, const float &z0,
                  const int &x1, const int &y1, const float &z1, vector<GridPoint> &edge_a_b);
    void line_high(const int &x0, const int &y0, const float &z0,
                   const int &x1, const int &y1, const float &z1, vector<GridPoint> &edge_a_b);
    void draw_edges(SDL_Renderer &renderer, const int &width, const int &height);
    void set_vertex_color(const Color &color);
    void set_edge_color(const Color &color);
    void translate(float dx, float dy, float dz);
};

// implementation
Surface::Surface() : p0({0.0f, 0.0f, 0.0f}), p1({0.0f, 0.0f, 0.0f}), p2({0.0f, 0.0f, 0.0f}) {}
Surface::Surface(const Point &_p0, const Point &_p1, const Point &_p2, const Color &_edge_color, const Color &_vertex_color)
    : p0(_p0), p1(_p1), p2(_p2), edge_color(_edge_color), vertex_color(_vertex_color) {}
Surface::Surface(const Surface &s)
{
    p0 = s.p0;
    p1 = s.p1;
    p2 = s.p2;
    edge_color = s.edge_color;
    vertex_color = s.vertex_color;
}

Surface::~Surface() {}

Surface &Surface::operator=(const Surface &s)
{
    if (this != &s)
    {
        p0 = s.p0;
        p1 = s.p1;
        p2 = s.p2;
        edge_color = s.edge_color;
        vertex_color = s.vertex_color;
    }
    return *this;
}

void Surface::matrix_mult(const array<array<float, 4>, 4> &m, Point &p)
{
    Point orig = p;
    p.x = orig.x * m[0][0] + orig.y * m[0][1] + orig.z * m[0][2] + m[0][3];
    p.y = orig.x * m[1][0] + orig.y * m[1][1] + orig.z * m[1][2] + m[1][3];
    p.z = orig.x * m[2][0] + orig.y * m[2][1] + orig.z * m[2][2] + m[2][3];
    float w = orig.x * m[3][0] + orig.y * m[3][1] + orig.z * m[3][2] + m[3][3];

    // convert from homogeneous to Cartesian coordinates
    if (w != 1 && w != 0)
    {
        p.x /= w;
        p.y /= w;
        p.z /= w;
    }
}

void Surface::transform_to_camera(const array<array<float, 4>, 4> &m, const int &width, const int &height)
{
    Point c0_temp = p0;
    Point c1_temp = p1;
    Point c2_temp = p2;
    matrix_mult(m, c0_temp);
    matrix_mult(m, c1_temp);
    matrix_mult(m, c2_temp);
    c0 = createGridPointFromPoint(c0_temp, width, height);
    c1 = createGridPointFromPoint(c1_temp, width, height);
    c2 = createGridPointFromPoint(c2_temp, width, height);
}

GridPoint Surface::createGridPointFromPoint(const Point &p, const int &width, const int &height)
{
    // convert position to screen coordinates
    int x = static_cast<int>((p.x + 1) * 0.5 * width);
    int y = static_cast<int>((1 - (p.y + 1) * 0.5) * height);

    GridPoint c{x, y, p.z};
    return c;
}

void Surface::draw_vertices(SDL_Renderer &renderer, const int &width, const int &height)
{
    SDL_SetRenderDrawColor(&renderer, vertex_color.r, vertex_color.g, vertex_color.b, vertex_color.a);
    if (c0.x <= width && c0.x >= 0 && c0.y <= height && c0.y >= 0 && c0.z > 0 && c0.z < 1)
        SDL_RenderPoint(&renderer, static_cast<float>(c0.x), static_cast<float>(c0.y));
    if (c1.x <= width && c1.x >= 0 && c1.y <= height && c1.y >= 0 && c1.z > 0 && c1.z < 1)
        SDL_RenderPoint(&renderer, static_cast<float>(c1.x), static_cast<float>(c1.y));
    if (c2.x <= width && c2.x >= 0 && c2.y <= height && c2.y >= 0 && c2.z > 0 && c2.z < 1)
        SDL_RenderPoint(&renderer, static_cast<float>(c2.x), static_cast<float>(c2.y));
}

vector<GridPoint> Surface::get_edge(const GridPoint &ca, const GridPoint &cb)
{
    vector<GridPoint> edge_a_b;
    // case where points have same x coordinate (infinite slope)
    if (ca.x == cb.x)
    {
        // find start and end (not inclusive of edges)
        int start{min(ca.y, cb.y)};
        int end{max(ca.y, cb.y)};
        size_t count = end - start - 1;
        edge_a_b.reserve(edge_a_b.size() + count);
        float z;

        for (int j{start + 1}; j < end; ++j)
        {
            z = (cb.z - ca.z) * (j - ca.y) / (cb.y - ca.y) + ca.z;
            GridPoint p{ca.x, j, z};
            edge_a_b.push_back(p);
        }
    }
    // case where points have same y coordinate (0 slope)
    else if (ca.y == cb.y)
    {
        // find start and end (not inclusive of edges)
        int start{min(ca.x, cb.x)};
        int end{max(ca.x, cb.x)};
        size_t count = end - start - 1;
        edge_a_b.reserve(edge_a_b.size() + count);
        float z;

        for (int i{start + 1}; i < end; ++i)
        {
            z = (cb.z - ca.z) * (i - ca.x) / (cb.x - ca.x) + ca.z;
            GridPoint p{i, ca.y, z};
            edge_a_b.push_back(p);
        }
    }
    // otherwise draw diagonal using Bresenham's algorithm
    else if (abs(cb.y - ca.y) < abs(cb.x - ca.x))
        if (ca.x > cb.x)
            line_low(cb.x, cb.y, cb.z, ca.x, ca.y, ca.z, edge_a_b);
        else
            line_low(ca.x, ca.y, ca.z, cb.x, cb.y, cb.z, edge_a_b);
    else
    {
        if (ca.y > cb.y)
            line_high(cb.x, cb.y, cb.z, ca.x, ca.y, ca.z, edge_a_b);
        else
            line_high(ca.x, ca.y, ca.z, cb.x, cb.y, cb.z, edge_a_b);
    }

    return edge_a_b;
}

// Bresenham's algorithm for slopes with magnitude less than 1
void Surface::line_low(const int &x0, const int &y0, const float &z0,
                       const int &x1, const int &y1, const float &z1, vector<GridPoint> &edge_a_b)
{
    size_t count = x1 - x0 + 1;
    edge_a_b.reserve(edge_a_b.size() + count);

    int dx{x1 - x0};
    int dy{y1 - y0};

    int yi = 1;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }

    int D{(2 * dy) - dx};
    int y{y0};
    float z;

    for (int x{x0}; x <= x1; ++x)
    {
        if (D > 0)
        {
            y = y + yi;
            D = D + (2 * (dy - dx));
        }
        else
        {
            D = D + 2 * dy;
        }
        if (((x == x0) && (y == y0)) || ((x == x1) && (y >= y1)))
        {
            continue; // don't overwrite vertices
        }
        else
        {
            z = (z1 - z0) * (x - x0) / (x1 - x0) + z0;
            GridPoint p{x, y, z};
            edge_a_b.push_back(p);
        }
    }
}

// Bresenham's algorithm for slopes with magnitude greater than or equal to 1
void Surface::line_high(const int &x0, const int &y0, const float &z0,
                        const int &x1, const int &y1, const float &z1, vector<GridPoint> &edge_a_b)
{
    size_t count = y1 - y0 + 1;
    edge_a_b.reserve(edge_a_b.size() + count);

    int dx{x1 - x0};
    int dy{y1 - y0};

    int xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }

    int D{(2 * dx) - dy};
    int x{x0};
    float z;

    for (int y{y0}; y <= y1; ++y)
    {
        if (D > 0)
        {
            x = x + xi;
            D = D + (2 * (dx - dy));
        }
        else
        {
            D = D + 2 * dx;
        }
        if (((x == x0) && (y == y0)) || ((x >= x1) && (y == y1)))
        {
            continue; // don't overwrite vertices
        }
        else
        {
            z = (z1 - z0) * (y - y0) / (y1 - y0) + z0;
            GridPoint p{x, y, z};
            edge_a_b.push_back(p);
        }
    }
}

void Surface::draw_edges(SDL_Renderer &renderer, const int &width, const int &height)
{
    SDL_SetRenderDrawColor(&renderer, edge_color.r, edge_color.g, edge_color.b, edge_color.a);

    vector<GridPoint> edge_0_1 = get_edge(c0, c1);
    vector<GridPoint> edge_1_2 = get_edge(c1, c2);
    vector<GridPoint> edge_2_0 = get_edge(c2, c0);
    for (GridPoint &c : edge_0_1)
    {
        if (c.x <= width && c.x >= 0 && c.y <= height && c.y >= 0 && c.z > 0 && c.z < 1)
            SDL_RenderPoint(&renderer, static_cast<float>(c.x), static_cast<float>(c.y));
    }
    for (GridPoint &c : edge_1_2)
    {
        if (c.x <= width && c.x >= 0 && c.y <= height && c.y >= 0 && c.z > 0 && c.z < 1)
            SDL_RenderPoint(&renderer, static_cast<float>(c.x), static_cast<float>(c.y));
    }
    for (GridPoint &c : edge_2_0)
    {
        if (c.x <= width && c.x >= 0 && c.y <= height && c.y >= 0 && c.z > 0 && c.z < 1)
            SDL_RenderPoint(&renderer, static_cast<float>(c.x), static_cast<float>(c.y));
    }
}

void Surface::set_vertex_color(const Color &color)
{
    vertex_color = color;
}

void Surface::set_edge_color(const Color &color)
{
    edge_color = color;
}

void Surface::translate(float dx, float dy, float dz)
{
    p0.x += dx;
    p0.y += dy;
    p0.z += dz;

    p1.x += dx;
    p1.y += dy;
    p1.z += dz;

    p2.x += dx;
    p2.y += dy;
    p2.z += dz;
}

#endif