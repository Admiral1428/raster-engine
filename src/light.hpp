#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <vector>
#include <numbers>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <Eigen/Dense>
#include "constants.h"
#include "point.hpp"

using std::clamp;
using std::invalid_argument;
using std::string;
using std::vector;
using std::numbers::pi;

// class defining a Light
class Light
{
private:
    Eigen::Vector3f p; // original coordinates
    Eigen::Vector2f brightness_factors;
    Eigen::Vector2f height_thresholds;

public:
    Light(); // default constructor (initializes object to default state with no arguments)
    Light(const Eigen::Vector3f &_p, const Eigen::Vector2f &_brightness_factors = Eigen::Vector2f(1.0f, 1.0f),
          const Eigen::Vector2f &_height_thresholds = Eigen::Vector2f(0.0f, 1.0f));
    Light(const Light &);            // copy constructor
    ~Light();                        // destructor
    Light &operator=(const Light &); // copy/assignment operator
    void translate(const float &dx, const float &dy, const float &dz);
    void rotate(const float &roll, const float &pitch, const float &yaw, const string &order);
    Eigen::Vector3f &get_points();
    Eigen::Vector2f &get_brightness_factors();
    Eigen::Vector2f &get_height_thresholds();
};

#endif