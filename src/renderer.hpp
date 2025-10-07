#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <numbers>
#include <cmath>
#include <cstdlib>
#include <array>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <SDL3/SDL.h>
#include "constants.h"
#include "point.hpp"
#include "surface.hpp"
#include "clipping.hpp"
#include "lighting.hpp"

using std::abs;
using std::array;
using std::fill;
using std::max;
using std::min;
using std::size_t;
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
    void set_width_height(const float &w, const float &h);
};

#endif