#include "light.hpp"

// implementation
Light::Light() {}
Light::Light(const Eigen::Vector3f &_p, const Eigen::Vector2f &_brightness_factors,
             const Eigen::Vector2f &_height_thresholds)
    : p(_p), brightness_factors(_brightness_factors), height_thresholds(_height_thresholds) {}
Light::Light(const Light &s)
{
    p = s.p;
    brightness_factors = s.brightness_factors;
    height_thresholds = s.height_thresholds;
}

Light::~Light() {}

Light &Light::operator=(const Light &s)
{
    if (this != &s)
    {
        p = s.p;
        brightness_factors = s.brightness_factors;
        height_thresholds = s.height_thresholds;
    }
    return *this;
}

void Light::translate(const float &dx, const float &dy, const float &dz)
{
    p(0) += dx;
    p(1) += dy;
    p(2) += dz;
}

void Light::rotate(const float &roll, const float &pitch, const float &yaw, const string &order)
{
    float roll_rad = roll * pi / 180.0f;
    float pitch_rad = pitch * pi / 180.0f;
    float yaw_rad = yaw * pi / 180.0f;

    float cos_roll = cos(roll_rad);
    float sin_roll = sin(roll_rad);
    float cos_pitch = cos(pitch_rad);
    float sin_pitch = sin(pitch_rad);
    float cos_yaw = cos(yaw_rad);
    float sin_yaw = sin(yaw_rad);

    // rotation about x-axis (roll)
    Eigen::Matrix3f mat_rx = Eigen::Matrix3f::Identity();
    mat_rx(1, 1) = cos_roll;
    mat_rx(1, 2) = -sin_roll;
    mat_rx(2, 1) = sin_roll;
    mat_rx(2, 2) = cos_roll;

    // rotation about y-axis (pitch)
    Eigen::Matrix3f mat_ry = Eigen::Matrix3f::Identity();
    mat_ry(0, 0) = cos_pitch;
    mat_ry(0, 2) = sin_pitch;
    mat_ry(2, 0) = -sin_pitch;
    mat_ry(2, 2) = cos_pitch;

    // rotation about z-axis (yaw)
    Eigen::Matrix3f mat_rz = Eigen::Matrix3f::Identity();
    mat_rz(0, 0) = cos_yaw;
    mat_rz(0, 1) = -sin_yaw;
    mat_rz(1, 0) = sin_yaw;
    mat_rz(1, 1) = cos_yaw;

    // combined rotation matrix
    Eigen::Matrix3f rot_matrix;

    if (order == "yaw-pitch-roll") // yaw, then pitch, then roll
    {
        rot_matrix = mat_rx * mat_ry * mat_rz;
    }
    else if (order == "yaw-roll-pitch")
    {
        rot_matrix = mat_ry * mat_rx * mat_rz;
    }
    else if (order == "pitch-yaw-roll")
    {
        rot_matrix = mat_rx * mat_rz * mat_ry;
    }
    else if (order == "pitch-roll-yaw")
    {
        rot_matrix = mat_rz * mat_rx * mat_ry;
    }
    else if (order == "roll-yaw-pitch")
    {
        rot_matrix = mat_ry * mat_rz * mat_rx;
    }
    else if (order == "roll-pitch-yaw")
    {
        rot_matrix = mat_rz * mat_ry * mat_rx;
    }
    else
    {
        throw invalid_argument("Invalid rotation sequence.");
    }

    p = rot_matrix * p;
}

Eigen::Vector3f &Light::get_points()
{
    return p;
}

Eigen::Vector2f &Light::get_brightness_factors()
{
    return brightness_factors;
}

Eigen::Vector2f &Light::get_height_thresholds()
{
    return height_thresholds;
}