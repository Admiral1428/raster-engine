#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <numbers>
#include <cmath>
#include <cstdlib>
#include <array>
#include "constants.h"
#include "point.h"

using std::abs;
using std::array;
using std::tan;
using std::numbers::pi;

// class defining camera perspective
class Camera
{
private:
    float f;   // far clipping plane
    float n;   // near clipping plane
    float fov; // field of view in degrees

public:
    Camera(); // default constructor (initializes object to default state with no arguments)
    Camera(const float &_n, const float &_f, const float &_fov);
    Camera(const Camera &);            // copy constructor
    ~Camera();                         // destructor
    Camera &operator=(const Camera &); // copy/assignment operator
    array<array<float, 4>, 4> get_projection_matrix();
};

// implementation
Camera::Camera() : n(0.1f), f(100.0f), fov(90.0f) {}
Camera::Camera(const float &_n, const float &_f, const float &_fov)
    : n(_n), f(_f), fov(_fov) {}
Camera::Camera(const Camera &c)
{
    n = c.n;
    f = c.f;
    fov = c.fov;
}

Camera::~Camera() {}

Camera &Camera::operator=(const Camera &c)
{
    if (this != &c)
    {
        n = c.n;
        f = c.f;
        fov = c.fov;
    }
    return *this;
}

array<array<float, 4>, 4> Camera::get_projection_matrix()
{
    float S = 1.0f / tan(fov * 0.5f * pi / 180.0f); // scaling factor
    array<array<float, 4>, 4> projection_matrix = {
        {{S, 0.0f, 0.0f, 0.0f},
         {0.0f, S, 0.0f, 0.0f},
         {0.0f, 0.0f, -f / (f - n), -(f * n) / (f - n)},
         {0.0f, 0.0f, -1.0f, 0.0f}}};
    return projection_matrix;
}

#endif