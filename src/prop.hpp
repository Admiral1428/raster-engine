#ifndef PROP_HPP
#define PROP_HPP

#include <Eigen/Dense>
#include "shape.hpp"
#include "octprism.hpp"

// class defining a propeller shape for an airplane
class Prop : public Shape
{
private:
    string size;
    float yaw;
    float pitch;
    float roll;
    string rot_order;
    float rot_speed;
    bool shifted;

public:
    Prop(const float &_x, const float &_y, const float &_z, const string &_size = "small",
         const float &_rol = 0.0f, const float &_pit = 0.0f, const float &_yaw = 0.0f,
         const string &_rot = "roll-pitch-yaw", const float &_rot_speed = 0.0f);
    Prop(const Prop &p);
    Prop &operator=(const Prop &);
    void make_shape() override;
    void move(const float &frame_dt);
};

#endif