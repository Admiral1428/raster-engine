#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <numbers>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <array>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <SDL3/SDL.h>
#include <Eigen/Dense>
#include "constants.h"
#include "point.hpp"
#include "surface.hpp"
#include "clipping.hpp"
#include "lighting.hpp"
#include "texture.hpp"
#include "map_textures.hpp"
#include "light.hpp"

using std::abs;
using std::array;
using std::clamp;
using std::fill;
using std::fmod;
using std::max;
using std::min;
using std::size_t;
using std::tan;
using std::vector;
using std::numbers::pi;
using PixelMatrix = Eigen::Matrix<Uint32, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

// class defining Renderer perspective
class Renderer
{
private:
    float n;    // near clipping plane
    float f;    // far clipping plane
    float fov;  // field of view in degrees
    int width;  // screen width
    int height; // screen height
    Eigen::MatrixXf z_buffer;
    PixelMatrix pixel_grid;
    Eigen::Matrix4f projection_matrix;
    Eigen::Matrix4f view_matrix;
    float pitch;         // view pitch angle (-90 to 90 degrees)
    float yaw;           // view yaw angle (0 to 360 degrees)
    Eigen::Vector3f eye; // view location in x, y, z
    string render_mode;

public:
    Renderer(); // default constructor (initializes object to default state with no arguments)
    Renderer(const float &_n, const float &_f, const float &_fov, const float &_width, const float &_height,
             const string &render_mode);
    Renderer(const Renderer &);            // copy constructor
    ~Renderer();                           // destructor
    Renderer &operator=(const Renderer &); // copy/assignment operator
    void resize_z_buffer();
    void calc_projection_matrix();
    vector<Eigen::Matrix4f> calc_rot_matrices();
    void calc_view_matrix();
    vector<Eigen::Vector3f> get_view_directions();
    void draw_surfaces(SDL_Renderer &renderer, vector<Surface> &surfaces,
                       const float &day_night_angle, Light &light_source);
    void set_width_height(const float &w, const float &h);
    Uint32 convert_color(const Color &c);
    void cycle_fov(const float &_increment);
    float get_fov();
    float get_width();
    float get_height();
    void move_view(const Eigen::Vector3f &dloc, const float &dpitch, const float &dyaw);
    void set_render_mode(const string &mode);
    string get_render_mode();
    Eigen::Vector3f get_eye();
};

#endif