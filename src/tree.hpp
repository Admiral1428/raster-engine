#ifndef TREE_HPP
#define TREE_HPP

#include <Eigen/Dense>
#include "shape.hpp"
#include "rectprism.hpp"
#include "pyramid.hpp"

// class defining a tree shape
class Tree : public Shape
{
private:
    string size;
    float yaw;
    float pitch;
    float roll;
    string rot_order;

public:
    Tree(const float &_x, const float &_y, const float &_z, const string _size = "small",
         const float &_rol = 0.0f, const float &_pit = 0.0f, const float &_yaw = 0.0f,
         const string _rot = "roll-pitch-yaw");
    Tree(const Tree &p);
    Tree &operator=(const Tree &);
    void make_shape() override;
};

#endif