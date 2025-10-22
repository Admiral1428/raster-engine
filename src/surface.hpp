#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <vector>
#include <numbers>
#include <string>
#include <stdexcept>
#include <Eigen/Dense>
#include "constants.h"
#include "point.hpp"

using std::invalid_argument;
using std::string;
using std::vector;
using std::numbers::pi;

// class defining a triangular surface
class Surface
{
private:
    Eigen::Vector4f p0; // original coordinates
    Eigen::Vector4f p1;
    Eigen::Vector4f p2;
    Color color;
    bool diminish_light;
    string texture_name = "";
    Eigen::Vector2f uv0 = Eigen::Vector2f::Zero(); // texture coordinates
    Eigen::Vector2f uv1 = Eigen::Vector2f::Zero();
    Eigen::Vector2f uv2 = Eigen::Vector2f::Zero();

public:
    Surface(); // default constructor (initializes object to default state with no arguments)
    Surface(const Eigen::Vector4f &_p0, const Eigen::Vector4f &_p1, const Eigen::Vector4f &_p2,
            const Color &_color = RED, const bool &_dim_light = false);
    Surface(const Surface &);            // copy constructor
    ~Surface();                          // destructor
    Surface &operator=(const Surface &); // copy/assignment operator
    void set_color(const Color &c);
    void set_texture_properties(const string &_texture_name, const Eigen::Vector2f &_uv0,
                                const Eigen::Vector2f &_uv1, const Eigen::Vector2f &_uv2);
    const Color get_color() const;
    void translate(const float &dx, const float &dy, const float &dz);
    void rotate(const float &roll, const float &pitch, const float &yaw, const string &order);
    vector<Eigen::Vector4f> get_points();
    vector<Eigen::Vector2f> get_uv_coords();
    string &get_texture_name();
    bool &get_diminish_light();
};

#endif