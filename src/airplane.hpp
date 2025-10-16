#ifndef AIRPLANE_HPP
#define AIRPLANE_HPP

#include <Eigen/Dense>
#include "shape.hpp"
#include "rectprism.hpp"
#include "octprism.hpp"
#include "quad.hpp"

// class defining a Airplane shape
class Airplane : public Shape
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
    Airplane(const float &_x, const float &_y, const float &_z, const string &_size = "small",
             const float &_rol = 0.0f, const float &_pit = 0.0f, const float &_yaw = 0.0f,
             const string &_rot = "roll-pitch-yaw", const float &_rot_speed = 0.0f);
    Airplane(const Airplane &p);
    Airplane &operator=(const Airplane &);
    void make_shape() override;
    void move(const float &frame_dt);
};

#endif