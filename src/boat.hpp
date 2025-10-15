#ifndef BOAT_HPP
#define BOAT_HPP

#include <Eigen/Dense>
#include "shape.hpp"
#include "rectprism.hpp"
#include "quad.hpp"

// class defining a boat shape
class Boat : public Shape
{
private:
    string size;
    float yaw;
    float pitch;
    float roll;
    string rot_order;
    float speed;

public:
    Boat(const float &_x, const float &_y, const float &_z, const string &_size = "small",
         const float &_rol = 0.0f, const float &_pit = 0.0f, const float &_yaw = 0.0f,
         const string &_rot = "roll-pitch-yaw", const float &_speed = 2.0f);
    Boat(const Boat &p);
    Boat &operator=(const Boat &);
    void make_shape() override;
    void move(const float &frame_dt);
};

#endif