#include "renderer.hpp"

Renderer::Renderer() : n(PLANE_N), f(PLANE_F), fov(FOV), width(RENDER_RES_OPTS[0].width), height(RENDER_RES_OPTS[0].height), pitch(0), yaw(0), render_mode("Textures_Lighting")
{
    eye << 0.0f, 0.0f, 0.0f;
    resize_z_buffer();
}
Renderer::Renderer(const float &_n, const float &_f, const float &_fov, const float &_width, const float &_height, const string &_render_mode)
    : n(_n), f(_f), fov(_fov), width(_width), height(_height), pitch(0.0f), yaw(0.0f), render_mode(_render_mode)
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
    pixel_grid = c.pixel_grid;
    projection_matrix = c.projection_matrix;
    view_matrix = c.view_matrix;
    pitch = c.pitch;
    yaw = c.yaw;
    eye = c.eye;
    render_mode = c.render_mode;
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
        pixel_grid = c.pixel_grid;
        projection_matrix = c.projection_matrix;
        view_matrix = c.view_matrix;
        pitch = c.pitch;
        yaw = c.yaw;
        eye = c.eye;
        render_mode = c.render_mode;
    }
    return *this;
}

void Renderer::resize_z_buffer()
{
    z_buffer.resize(height, width);
    pixel_grid = PixelMatrix(height, width);
}

void Renderer::calc_projection_matrix()
{
    float Sx = 1.0f / tan(fov * 0.5f * pi / 180.0f); // horizontal scaling factor using horz fov
    float Sy = Sx * (width / height);                // vertical scaling factor using aspect ratio
    projection_matrix << Sx, 0.0f, 0.0f, 0.0f,
        0.0f, Sy, 0.0f, 0.0f,
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

    // original forward and left view directions (as percieved by player)
    Eigen::Vector3f forward_dir(0.0f, 0.0f, -1.0f);
    Eigen::Vector3f left_dir(-1.0f, 0.0f, 0.0f);

    // new directions
    Eigen::Vector3f new_forward_dir = mat_sub_ry * mat_sub_rx * forward_dir;
    Eigen::Vector3f new_left_dir = mat_sub_ry * mat_sub_rx * left_dir;
    return {new_forward_dir, new_left_dir};
}

void Renderer::draw_surfaces(SDL_Renderer &renderer, vector<Surface> &surfaces,
                             const float &day_night_angle, Light &light_source)
{
    // initialize z buffer with 1.0 depth values
    z_buffer.setConstant(1.0f);

    // get sky color
    Color sky_color = get_sky_color(day_night_angle);

    // initialize pixel buffer to sky blue
    if (render_mode == "Triangles_Black_White")
    {
        pixel_grid.setConstant(convert_color(WHITE));
    }
    else
    {
        pixel_grid.setConstant(convert_color(sky_color));
    }

    // Initialize pixel grid as SDL texture
    SDL_Texture *sdl_texture = SDL_CreateTexture(&renderer, SDL_PIXELFORMAT_BGRA8888,
                                                 SDL_TEXTUREACCESS_STREAMING, width, height);
    void *sdl_pixels;
    int pitch; // Number of bytes in a row
    SDL_LockTexture(sdl_texture, NULL, &sdl_pixels, &pitch);

    // Cast pixels to a usable Uint32 format
    Uint32 *texture_pixels = (Uint32 *)sdl_pixels;

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
    bool surface_visible;
    float brightness;
    vector<Eigen::Vector2f> uv_coords;
    string suface_texture_name;
    bool has_texture;
    vector<Vertex> homog_points;
    Eigen::Vector4f ndc_0;
    Eigen::Vector4f ndc_1;
    Eigen::Vector4f ndc_2;
    Eigen::Vector2f uv0;
    Eigen::Vector2f uv1;
    Eigen::Vector2f uv2;
    Eigen::Vector4f r0;
    Eigen::Vector4f r1;
    Eigen::Vector4f r2;
    float r0_r1_delta;
    float r1_r2_delta;
    float r2_r0_delta;
    Eigen::Vector4i bounding_box;
    int num_bounding_pixels;
    float triangle_area;
    vector<Color> surf_colors;
    Color surf_color;
    bool surf_diminish_light;
    int grid_ctr;
    Color pixel_color;
    vector<Eigen::VectorXf> barycentric_coords;
    vector<Eigen::VectorXf> barycentric_and_pixels;
    Eigen::VectorXf px_subset;
    Eigen::VectorXf py_subset;
    Eigen::VectorXf z_ndc;
    Texture &surface_texture = TEXTURES.at("test");
    Eigen::MatrixXf uv_texture;
    int cur_pixel_x;
    int cur_pixel_y;

    // perform drawing for each surface
    for (auto &surface : surfaces)
    {
        // transform points with view and projection matrices
        points = surface.get_points();
        v0 = view_matrix * points[0];
        v1 = view_matrix * points[1];
        v2 = view_matrix * points[2];

        // determine if surface is facing camera
        surface_visible = is_surface_visible(v0, v1, v2);

        if (surface_visible)
        {
            // calcluate brightness using light source
            if (render_mode == "Textures_Lighting" || render_mode == "Colors_Lighting")
            {
                brightness = get_brightness(light_source, points[0], points[1], points[2],
                                            surface.get_min_brightness(), surface.get_max_brightness());
            }

            // project into viewing volume
            c0 = projection_matrix * v0;
            c1 = projection_matrix * v1;
            c2 = projection_matrix * v2;

            uv_coords = surface.get_uv_coords();
            suface_texture_name = surface.get_texture_name();
            has_texture = suface_texture_name != "";

            // perform clipping and return homogeneous coordinates
            homog_points = clip(c0, c1, c2, uv_coords[0], uv_coords[1], uv_coords[2]);

            // loop through every third element to get each resulting triangle
            for (int i{0}; i < homog_points.size(); i += 3)
            {
                // get normalized device coordinates
                ndc_0 = homog_points[i].position;
                ndc_1 = homog_points[i + 1].position;
                ndc_2 = homog_points[i + 2].position;
                normalize_point(ndc_0);
                normalize_point(ndc_1);
                normalize_point(ndc_2);

                // Get texture coordinates
                uv0 = homog_points[i].uv;
                uv1 = homog_points[i + 1].uv;
                uv2 = homog_points[i + 2].uv;

                // rasterize triangle vertices to screen space after normalizing
                r0 = ndc_0;
                r1 = ndc_1;
                r2 = ndc_2;
                rasterize_point(r0, width, height);
                rasterize_point(r1, width, height);
                rasterize_point(r2, width, height);

                // only render triangle if vertices at least one pixel apart
                r0_r1_delta = abs(r0(0) - r1(0)) + abs(r0(1) - r1(1));
                r1_r2_delta = abs(r1(0) - r2(0)) + abs(r1(1) - r2(1));
                r2_r0_delta = abs(r2(0) - r0(0)) + abs(r2(1) - r0(1));

                if ((r0_r1_delta >= 1.0f) || (r1_r2_delta >= 1.0f) || (r2_r0_delta >= 1.0f))
                {
                    // get bounding box of these screen vertices
                    bounding_box = get_bounding_box(r0, r1, r2, width, height);
                    num_bounding_pixels = (bounding_box(1) - bounding_box(0) + 1) *
                                          (bounding_box(3) - bounding_box(2) + 1);

                    // get surface light property
                    surf_diminish_light = surface.get_diminish_light();

                    // initialize vectors containing pixel coordinates
                    Eigen::VectorXf px(num_bounding_pixels);
                    Eigen::VectorXf py(num_bounding_pixels);
                    grid_ctr = 0;
                    for (int x{bounding_box(0)}; x <= bounding_box(1); ++x)
                    {
                        for (int y{bounding_box(2)}; y <= bounding_box(3); ++y)
                        {
                            px(grid_ctr) = static_cast<float>(x);
                            py(grid_ctr) = static_cast<float>(y);
                            ++grid_ctr;
                        }
                    }

                    // get barycentric coordinates
                    barycentric_coords = get_barycentric_coords(r0, r1, r2, px, py);

                    // get subset of coordinates which are inside or on triangle boundary
                    if (render_mode == "Triangles" || render_mode == "Triangles_Black_White")
                    {
                        barycentric_and_pixels = get_points_on_triangle_boundary(barycentric_coords, px, py);
                    }
                    else
                    {
                        barycentric_and_pixels = get_points_in_triangle(barycentric_coords, px, py);
                    }
                    px_subset = barycentric_and_pixels[3];
                    py_subset = barycentric_and_pixels[4];

                    // get ndc depth for reduced set of coordinates
                    z_ndc = get_ndc_depth(barycentric_and_pixels, homog_points[i].position,
                                          homog_points[i + 1].position, homog_points[i + 2].position);

                    if (has_texture && (render_mode == "Textures_Lighting" || render_mode == "Textures"))
                    {
                        uv_texture = get_uv_texture(barycentric_and_pixels,
                                                    homog_points[i].position,
                                                    homog_points[i + 1].position,
                                                    homog_points[i + 2].position,
                                                    uv0, uv1, uv2);
                        surface_texture = TEXTURES.at(suface_texture_name);
                    }
                    else if (render_mode == "Triangles_Black_White")
                    {
                        surf_color = BLACK;
                    }
                    else
                    {
                        surf_color = surface.get_color();
                    }

#pragma omp parallel for
                    for (int pixel{0}; pixel < z_ndc.size(); ++pixel)
                    {
                        int cur_pixel_x = static_cast<int>(px_subset(pixel));
                        int cur_pixel_y = static_cast<int>(py_subset(pixel));

                        if (z_ndc(pixel) < z_buffer(cur_pixel_y, cur_pixel_x))
                        {
                            z_buffer(cur_pixel_y, cur_pixel_x) = z_ndc(pixel);

                            if (has_texture && (render_mode == "Textures_Lighting" || render_mode == "Textures"))
                            {
                                surf_color = surface_texture.get_color(uv_texture(pixel, 0), uv_texture(pixel, 1));
                            }
                            // Set pixel color to surface color before further manipulations
                            pixel_color = surf_color;

                            if (render_mode == "Textures_Lighting" || render_mode == "Colors_Lighting")
                            {
                                // calcluate brightness using light source
                                pixel_color = apply_light(brightness, pixel_color);
                            }
                            if (surf_diminish_light && render_mode != "Triangles" && render_mode != "Triangles_Black_White")
                            {
                                // Diminish light as a function of z depth, if surface specifies this
                                pixel_color = diminish_light(z_buffer(cur_pixel_y, cur_pixel_x), pixel_color);
                            }

                            pixel_grid(cur_pixel_y, cur_pixel_x) = convert_color(pixel_color);
                        }
                    }
                }
            }
        }
    }

    // Render the final pixel grid after looping through all surfaces
    const Uint32 *pixel_color_data = pixel_grid.data();
    memcpy(texture_pixels, pixel_color_data, width * height * sizeof(Uint32));
    SDL_UnlockTexture(sdl_texture);
    SDL_RenderTexture(&renderer, sdl_texture, NULL, NULL);
    SDL_DestroyTexture(sdl_texture);
    sdl_texture = NULL;
}

// Change width and height vars based on screen resize, and resize z_buffer
void Renderer::set_width_height(const float &w, const float &h)
{
    width = static_cast<int>(w);
    height = static_cast<int>(h);
    resize_z_buffer();
}

// Convert color struct to Uint32
Uint32 Renderer::convert_color(const Color &c)
{
    Uint32 result = 0;
    result |= static_cast<Uint32>(c.b) << 24;
    result |= static_cast<Uint32>(c.g) << 16;
    result |= static_cast<Uint32>(c.r) << 8;
    result |= static_cast<Uint32>(c.a);
    return result;
}

void Renderer::cycle_fov(const float &_increment)
{
    fov += _increment;
    if (fov > 130.0f)
    {
        fov = 70.0f;
    }
    else if (fov < 70.0f)
    {
        fov = 130.0f;
    }
}

float Renderer::get_fov()
{
    return fov;
}

float Renderer::get_width()
{
    return width;
}

float Renderer::get_height()
{
    return height;
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

void Renderer::set_render_mode(const string &mode)
{
    render_mode = mode;
}

string Renderer::get_render_mode()
{
    return render_mode;
}

Eigen::Vector3f Renderer::get_eye()
{
    return eye;
}