#ifndef HOUSE_HPP
#define HOUSE_HPP

#include <Eigen/Dense>
#include "shape.hpp"
#include "rect.hpp"
#include "rectprism.hpp"

// class defining a house shape
class House : public Shape
{
private:
    string size;
    float yaw;
    float pitch;
    float roll;
    string rot_order;

public:
    House(const float &_x, const float &_y, const float &_z, const float &_rol = 0.0f,
          const float &_pit = 0.0f, const float &_yaw = 0.0f, const string _rot = "roll-pitch-yaw");
    House(const House &p);
    House &operator=(const House &);
    void make_shape() override;
};

#endif