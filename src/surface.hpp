#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <vector>
#include <Eigen/Dense>
#include "constants.h"
#include "point.hpp"

using std::vector;

// class defining a triangular surface
class Surface
{
private:
    Eigen::Vector4f p0; // original coordinates
    Eigen::Vector4f p1;
    Eigen::Vector4f p2;
    Color color;
    bool diminish_light;

public:
    Surface(); // default constructor (initializes object to default state with no arguments)
    Surface(const Eigen::Vector4f &_p0, const Eigen::Vector4f &_p1, const Eigen::Vector4f &_p2, const Color &_color = RED, const bool &_dim_light = false);
    Surface(const Surface &);            // copy constructor
    ~Surface();                          // destructor
    Surface &operator=(const Surface &); // copy/assignment operator
    void set_color(const Color &c);
    const Color get_color() const;
    void translate(float dx, float dy, float dz);
    vector<Eigen::Vector4f> get_points();
    bool &get_diminish_light();
};

#endif