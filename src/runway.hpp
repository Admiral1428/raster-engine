#ifndef RUNWAY_HPP
#define RUNWAY_HPP

#include <Eigen/Dense>
#include "shape.hpp"
#include "rect.hpp"

// class defining a runway shape
class Runway : public Shape
{
private:
    string size;
    float yaw;
    float pitch;
    float roll;
    string rot_order;

public:
    Runway(const float &_x, const float &_y, const float &_z, const string _size = "normal",
           const float &_rol = 0.0f, const float &_pit = 0.0f, const float &_yaw = 0.0f,
           const string _rot = "roll-pitch-yaw");
    Runway(const Runway &p);
    Runway &operator=(const Runway &);
    void make_shape() override;
};

#endif