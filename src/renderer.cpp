#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip> // Required for std::setprecision and std::fixed

#include "renderer.hpp"

Renderer::Renderer() : n(PLANE_N), f(PLANE_F), fov(FOV), width(WIDTH), height(HEIGHT), pitch(0), yaw(0)
{
    eye << 0.0f, 0.0f, 0.0f;
    resize_z_buffer();
}
Renderer::Renderer(const float &_n, const float &_f, const float &_fov, const float &_width, const float &_height)
    : n(_n), f(_f), fov(_fov), width(_width), height(_height), pitch(0.0f), yaw(0.0f)
{
    eye << 0.0f, 0.0f, 0.0f;
    resize_z_buffer();
}
Renderer::Renderer(const Renderer &c)
{
    n = c.n;
    f = c.f;
    fov = c.fov;
    width = c.width;
    height = c.height;
    z_buffer = c.z_buffer;
    projection_matrix = c.projection_matrix;
    view_matrix = c.view_matrix;
    pitch = c.pitch;
    yaw = c.yaw;
    eye = c.eye;
}

Renderer::~Renderer() {}

Renderer &Renderer::operator=(const Renderer &c)
{
    if (this != &c)
    {
        n = c.n;
        f = c.f;
        fov = c.fov;
        width = c.width;
        height = c.height;
        z_buffer = c.z_buffer;
        projection_matrix = c.projection_matrix;
        view_matrix = c.view_matrix;
        pitch = c.pitch;
        yaw = c.yaw;
        eye = c.eye;
    }
    return *this;
}

void Renderer::resize_z_buffer()
{
    z_buffer.resize(height, width);
}

void Renderer::calc_projection_matrix()
{
    float S = 1.0f / tan(fov * 0.5f * pi / 180.0f); // scaling factor
    projection_matrix << S, 0.0f, 0.0f, 0.0f,
        0.0f, S, 0.0f, 0.0f,
        0.0f, 0.0f, -f / (f - n), -(f * n) / (f - n),
        0.0f, 0.0f, -1.0f, 0.0f;
}

vector<Eigen::Matrix4f> Renderer::calc_rot_matrices()
{
    float pitch_rad = pitch * pi / 180.0f;
    float yaw_rad = yaw * pi / 180.0f;
    float cos_pitch = cos(pitch_rad);
    float sin_pitch = sin(pitch_rad);
    float cos_yaw = cos(yaw_rad);
    float sin_yaw = sin(yaw_rad);

    // rotation about x-axis (pitch)
    Eigen::Matrix4f mat_rx = Eigen::Matrix4f::Identity();
    mat_rx(1, 1) = cos_pitch;
    mat_rx(1, 2) = -sin_pitch;
    mat_rx(2, 1) = sin_pitch;
    mat_rx(2, 2) = cos_pitch;

    // rotation about y-axis (yaw)
    Eigen::Matrix4f mat_ry = Eigen::Matrix4f::Identity();
    mat_ry(0, 0) = cos_yaw;
    mat_ry(0, 2) = sin_yaw;
    mat_ry(2, 0) = -sin_yaw;
    mat_ry(2, 2) = cos_yaw;

    return {mat_rx, mat_ry};
}

void Renderer::calc_view_matrix()
{
    // calculate rotation matrices
    vector<Eigen::Matrix4f> mats_rot = calc_rot_matrices();

    // translation matrix
    Eigen::Matrix4f mat_t = Eigen::Matrix4f::Identity();
    mat_t(0, 3) = eye(0);
    mat_t(1, 3) = eye(1);
    mat_t(2, 3) = eye(2);

    // inv(T*Ry*Rx) = trans(mat_rx) * trans(mat_ry) * inv(mat_t)
    view_matrix = mats_rot[0].transpose() * mats_rot[1].transpose() * mat_t.inverse();
}

// determine new forward and left view directions (used for processing movement)
vector<Eigen::Vector3f> Renderer::get_view_directions()
{
    // calculate rotation matrices
    vector<Eigen::Matrix4f> mats_rot = calc_rot_matrices();

    Eigen::MatrixXf mat_sub_rx = mats_rot[0].block<3, 3>(0, 0);
    Eigen::MatrixXf mat_sub_ry = mats_rot[1].block<3, 3>(0, 0);

    // original forward and up view directions (as percieved by player)
    Eigen::Vector3f forward_dir(0.0f, 0.0f, -1.0f);
    Eigen::Vector3f up_dir(0.0f, 1.0f, 0.0f);

    // new directions
    Eigen::Vector3f new_forward_dir = mat_sub_ry * mat_sub_rx * forward_dir;
    Eigen::Vector3f new_left_dir = up_dir.cross(new_forward_dir);
    return {new_forward_dir, new_left_dir};
}

void Renderer::draw_surfaces(SDL_Renderer &renderer, vector<Surface> &surfaces)
{
    // initialize z buffer with 1.0 depth values
    z_buffer.setConstant(1.0f);

    // calculate view and projection matrices
    calc_view_matrix();
    calc_projection_matrix();

    // initialize variables
    vector<Eigen::Vector4f> points;
    Eigen::Vector4f v0;
    Eigen::Vector4f v1;
    Eigen::Vector4f v2;
    Eigen::Vector4f c0;
    Eigen::Vector4f c1;
    Eigen::Vector4f c2;
    vector<Eigen::Vector4f> homog_points;
    Eigen::Vector4f ndc_0;
    Eigen::Vector4f ndc_1;
    Eigen::Vector4f ndc_2;
    Eigen::Vector4f r0;
    Eigen::Vector4f r1;
    Eigen::Vector4f r2;
    float r0_r1_delta;
    float r1_r2_delta;
    float r2_r0_delta;
    Eigen::Vector4i bounding_box;
    float triangle_area;
    Color surf_color;
    bool surf_diminish_light;
    Color pixel_color;
    Eigen::Vector2f p;
    Eigen::Vector3f barycentric_coords;
    double z_ndc;

    // perform drawing for each surface
    for (auto &surface : surfaces)
    {
        // transform points with view and projection matrices
        points = surface.get_points();
        v0 = view_matrix * points[0];
        v1 = view_matrix * points[1];
        v2 = view_matrix * points[2];
        c0 = projection_matrix * v0;
        c1 = projection_matrix * v1;
        c2 = projection_matrix * v2;

        // perform clipping and return homogeneous coordinates
        homog_points = clip(c0, c1, c2);

        // loop through every third element to get each resulting triangle
        for (int i{0}; i < homog_points.size(); i += 3)
        {
            // get normalized device coordinates
            ndc_0 = homog_points[i];
            ndc_1 = homog_points[i + 1];
            ndc_2 = homog_points[i + 2];
            normalize_point(ndc_0);
            normalize_point(ndc_1);
            normalize_point(ndc_2);

            // rasterize triangle vertices to screen space after normalizing
            r0 = ndc_0;
            r1 = ndc_1;
            r2 = ndc_2;
            rasterize_point(r0, width, height);
            rasterize_point(r1, width, height);
            rasterize_point(r2, width, height);

            // only render triangle if vertices at least two pixels apart
            r0_r1_delta = abs(r0(0) - r1(0)) + abs(r0(1) - r1(1));
            r1_r2_delta = abs(r1(0) - r2(0)) + abs(r1(1) - r2(1));
            r2_r0_delta = abs(r2(0) - r0(0)) + abs(r2(1) - r0(1));

            if ((r0_r1_delta >= 2.0f) && (r1_r2_delta >= 2.0f) && (r2_r0_delta >= 2.0f))
            {
                // get bounding box of these screen vertices
                bounding_box = get_bounding_box(r0, r1, r2, width, height);

                // set color
                surf_color = surface.get_color();

                // get surface light property
                surf_diminish_light = surface.get_diminish_light();

                // loop through bounding box to determine triangle points
                for (int x{bounding_box(0)}; x <= bounding_box(1); ++x)
                {
                    p(0) = static_cast<float>(x);
                    for (int y{bounding_box(2)}; y <= bounding_box(3); ++y)
                    {
                        p(1) = static_cast<float>(y);

                        // get and process barycentric coordinates
                        barycentric_coords = get_barycentric_coords(r0, r1, r2, p);

                        if (point_in_triangle(barycentric_coords, TOL_IN_TRIANGLE))
                        {
                            z_ndc = get_ndc_depth(barycentric_coords, homog_points[i], homog_points[i + 1], homog_points[i + 2]);

                            if (z_ndc < z_buffer(y, x))
                            {
                                z_buffer(y, x) = z_ndc;
                                if (surf_diminish_light)
                                    pixel_color = diminish_light(z_buffer(y, x), surf_color);
                                else
                                    pixel_color = surf_color;

                                SDL_SetRenderDrawColor(&renderer, pixel_color.r,
                                                       pixel_color.g, pixel_color.b, pixel_color.a);
                                SDL_RenderPoint(&renderer, x, y);
                            }
                        }
                    }
                }
            }
        }
    }
}

// Change width and height vars based on screen resize, and resize z_buffer
void Renderer::set_width_height(const float &w, const float &h)
{
    width = static_cast<int>(w);
    height = static_cast<int>(h);
    resize_z_buffer();
}

// Move the view position and angle
void Renderer::move_view(const Eigen::Vector3f &dloc, const float &dpitch, const float &dyaw)
{
    if ((dpitch != 0.0f) || (dyaw != 0.0f))
    {
        pitch += dpitch;
        yaw += dyaw;

        // enforce limits on pitch
        if (pitch > 90.0f)
            pitch = 90.0f;
        else if (pitch < -90.0f)
            pitch = -90.0f;

        // re-baseline yaw angle
        if ((yaw < 0.0f) || (yaw > 360.0f))
        {
            float normalized = fmod(yaw, 360.0f);
            if (normalized < 0.0f)
            {
                normalized += 360.0f;
            }
            yaw = normalized;
        }
    }

    eye(0) += dloc(0);
    eye(1) += dloc(1);
    eye(2) += dloc(2);
}