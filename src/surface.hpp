#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <vector>
#include <cstdlib>
#include "constants.h"
#include "point.h"

using std::abs;
using std::max;
using std::min;
using std::vector;

// class defining a triangular surface
class Surface
{
private:
    Point p0;
    Point p1;
    Point p2;

public:
    Surface(); // default constructor (initializes object to default state with no arguments)
    Surface(const Point &_p0, const Point &_p1, const Point &_p2);
    Surface(const Surface &);            // copy constructor
    ~Surface();                          // destructor
    Surface &operator=(const Surface &); // copy/assignment operator
    void draw_vertices(SDL_Renderer &renderer, const Color &color);
    vector<Point> get_edge(const Point &pa, const Point &pb);
    void line_low(const int &x0, const int &y0, const int &x1, const int &y1, vector<Point> &edge_a_b);
    void line_high(const int &x0, const int &y0, const int &x1, const int &y1, vector<Point> &edge_a_b);
    void draw_edges(SDL_Renderer &renderer, const Color &color);
};

// implementation
Surface::Surface() : p0({-1, -1, -1}), p1({-1, -1, -1}), p2({-1, -1, -1}) {}
Surface::Surface(const Point &_p0, const Point &_p1, const Point &_p2) : p0(_p0), p1(_p1), p2(_p2) {}
Surface::Surface(const Surface &s)
{
    p0 = s.p0;
    p1 = s.p1;
    p2 = s.p2;
}

Surface::~Surface() {}

Surface &Surface::operator=(const Surface &s)
{
    if (this != &s)
    {
        p0 = s.p0;
        p1 = s.p1;
        p2 = s.p2;
    }
    return *this;
}

void Surface::draw_vertices(SDL_Renderer &renderer, const Color &color)
{
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(&renderer, static_cast<float>(p0.x), static_cast<float>(p0.y));
    SDL_RenderPoint(&renderer, static_cast<float>(p1.x), static_cast<float>(p1.y));
    SDL_RenderPoint(&renderer, static_cast<float>(p2.x), static_cast<float>(p2.y));
}

vector<Point> Surface::get_edge(const Point &pa, const Point &pb)
{
    vector<Point> edge_a_b;
    // case where points have same x coordinate (infinite slope)
    if (pa.x == pb.x)
    {
        // find start and end (not inclusive of edges)
        int start{min(pa.y, pb.y)};
        int end{max(pa.y, pb.y)};
        size_t count = end - start - 1;
        edge_a_b.reserve(edge_a_b.size() + count);

        for (int i{start + 1}; i < end; ++i)
        {
            Point p{pa.x, i, 0};
            edge_a_b.push_back(p);
        }
    }
    // case where points have same y coordinate (0 slope)
    else if (pa.y == pb.y)
    {
        // find start and end (not inclusive of edges)
        int start{min(pa.x, pb.x)};
        int end{max(pa.x, pb.x)};
        size_t count = end - start - 1;
        edge_a_b.reserve(edge_a_b.size() + count);

        for (int j{start + 1}; j < end; ++j)
        {
            Point p{j, pa.y, 0};
            edge_a_b.push_back(p);
        }
    }
    // otherwise draw diagonal using Bresenham's algorithm
    else if (abs(pb.y - pa.y) < abs(pb.x - pa.x))
        if (pa.x > pb.x)
            line_low(pb.x, pb.y, pa.x, pa.y, edge_a_b);
        else
            line_low(pa.x, pa.y, pb.x, pb.y, edge_a_b);
    else
    {
        if (pa.y > pb.y)
            line_high(pb.x, pb.y, pa.x, pa.y, edge_a_b);
        else
            line_high(pa.x, pa.y, pb.x, pb.y, edge_a_b);
    }

    return edge_a_b;
}

// Bresenham's algorithm for slopes with magnitude less than 1
void Surface::line_low(const int &x0, const int &y0, const int &x1, const int &y1, vector<Point> &edge_a_b)
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
            Point p{x, y, 0};
            edge_a_b.push_back(p);
        }
    }
}

// Bresenham's algorithm for slopes with magnitude greater than or equal to 1
void Surface::line_high(const int &x0, const int &y0, const int &x1, const int &y1, vector<Point> &edge_a_b)
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
            Point p{x, y, 0};
            edge_a_b.push_back(p);
        }
    }
}

void Surface::draw_edges(SDL_Renderer &renderer, const Color &color)
{
    SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);

    vector<Point> edge_0_1 = get_edge(p0, p1);
    vector<Point> edge_1_2 = get_edge(p1, p2);
    vector<Point> edge_2_0 = get_edge(p2, p0);
    for (Point &p : edge_0_1)
    {
        SDL_RenderPoint(&renderer, static_cast<float>(p.x), static_cast<float>(p.y));
    }
    for (Point &p : edge_1_2)
    {
        SDL_RenderPoint(&renderer, static_cast<float>(p.x), static_cast<float>(p.y));
    }
    for (Point &p : edge_2_0)
    {
        SDL_RenderPoint(&renderer, static_cast<float>(p.x), static_cast<float>(p.y));
    }
}

#endif