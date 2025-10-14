#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include <Eigen/Dense>
#include "shape.hpp"
#include "rect.hpp"
#include "rectprism.hpp"

// class defining a bridge shape
class Bridge : public Shape
{
private:
    string size;
    float yaw;
    float pitch;
    float roll;
    string rot_order;

public:
    Bridge(const float &_x, const float &_y, const float &_z, const float &_rol = 0.0f,
           const float &_pit = 0.0f, const float &_yaw = 0.0f, const string _rot = "roll-pitch-yaw");
    Bridge(const Bridge &p);
    Bridge &operator=(const Bridge &);
    void make_shape() override;
};

#endif