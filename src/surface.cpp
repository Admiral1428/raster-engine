#include "surface.hpp"

// implementation
Surface::Surface() {}
Surface::Surface(const Eigen::Vector4f &_p0, const Eigen::Vector4f &_p1, const Eigen::Vector4f &_p2,
                 const Color &_color, const bool &_dim_light)
    : p0(_p0), p1(_p1), p2(_p2), color(_color), diminish_light(_dim_light) {}
Surface::Surface(const Surface &s)
{
    p0 = s.p0;
    p1 = s.p1;
    p2 = s.p2;
    color = s.color;
    diminish_light = s.diminish_light;
    surface_name = s.surface_name;
    texture_name = s.texture_name;
    uv0 = s.uv0;
    uv1 = s.uv1;
    uv2 = s.uv2;
}

Surface::~Surface() {}

Surface &Surface::operator=(const Surface &s)
{
    if (this != &s)
    {
        p0 = s.p0;
        p1 = s.p1;
        p2 = s.p2;
        color = s.color;
        diminish_light = s.diminish_light;
        surface_name = s.surface_name;
        texture_name = s.texture_name;
        uv0 = s.uv0;
        uv1 = s.uv1;
        uv2 = s.uv2;
    }
    return *this;
}

void Surface::set_name(const string &s)
{
    surface_name = s;
}

void Surface::set_color(const Color &c)
{
    color = c;
}

void Surface::set_texture_properties(const string &_texture_name, const Eigen::Vector2f &_uv0,
                                     const Eigen::Vector2f &_uv1, const Eigen::Vector2f &_uv2)
{
    texture_name = _texture_name;
    uv0 = _uv0;
    uv1 = _uv1;
    uv2 = _uv2;
}

const Color Surface::get_color() const
{
    return color;
}

void Surface::translate(const float &dx, const float &dy, const float &dz)
{
    p0(0) += dx;
    p0(1) += dy;
    p0(2) += dz;

    p1(0) += dx;
    p1(1) += dy;
    p1(2) += dz;

    p2(0) += dx;
    p2(1) += dy;
    p2(2) += dz;
}

void Surface::rotate(const float &roll, const float &pitch, const float &yaw, const string &order)
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
    Eigen::Matrix4f mat_rx = Eigen::Matrix4f::Identity();
    mat_rx(1, 1) = cos_roll;
    mat_rx(1, 2) = -sin_roll;
    mat_rx(2, 1) = sin_roll;
    mat_rx(2, 2) = cos_roll;

    // rotation about y-axis (pitch)
    Eigen::Matrix4f mat_ry = Eigen::Matrix4f::Identity();
    mat_ry(0, 0) = cos_pitch;
    mat_ry(0, 2) = sin_pitch;
    mat_ry(2, 0) = -sin_pitch;
    mat_ry(2, 2) = cos_pitch;

    // rotation about z-axis (yaw)
    Eigen::Matrix4f mat_rz = Eigen::Matrix4f::Identity();
    mat_rz(0, 0) = cos_yaw;
    mat_rz(0, 1) = -sin_yaw;
    mat_rz(1, 0) = sin_yaw;
    mat_rz(1, 1) = cos_yaw;

    // combined rotation matrix
    Eigen::Matrix4f rot_matrix;

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

    p0 = rot_matrix * p0;
    p1 = rot_matrix * p1;
    p2 = rot_matrix * p2;
}

vector<Eigen::Vector4f> Surface::get_points()
{
    return {p0, p1, p2};
}

vector<Eigen::Vector2f> Surface::get_uv_coords()
{
    return {uv0, uv1, uv2};
}

string &Surface::get_name()
{
    return surface_name;
}

string &Surface::get_texture_name()
{
    return texture_name;
}

bool &Surface::get_diminish_light()
{
    return diminish_light;
}