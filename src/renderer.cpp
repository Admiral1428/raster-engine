#include "renderer.hpp"

// implementation
Renderer::Renderer() : n(PLANE_N), f(PLANE_F), fov(FOV), width(WIDTH), height(HEIGHT)
{
    resize_z_buffer();
}
Renderer::Renderer(const float &_n, const float &_f, const float &_fov, const float &_width, const float &_height)
    : n(_n), f(_f), fov(_fov), width(_width), height(_height)
{
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
    }
    return *this;
}

void Renderer::resize_z_buffer()
{
    z_buffer.assign(static_cast<size_t>(width), vector<float>(static_cast<size_t>(height)));
}

void Renderer::calc_projection_matrix()
{
    float S = 1.0f / tan(fov * 0.5f * pi / 180.0f); // scaling factor
    projection_matrix = {
        {{S, 0.0f, 0.0f, 0.0f},
         {0.0f, S, 0.0f, 0.0f},
         {0.0f, 0.0f, -f / (f - n), -(f * n) / (f - n)},
         {0.0f, 0.0f, -1.0f, 0.0f}}};
}

void Renderer::draw_surfaces(SDL_Renderer &renderer, vector<Surface> &surfaces)
{
    // initialize z buffer with 1.0 depth values
    for (auto &row : z_buffer)
    {
        fill(row.begin(), row.end(), 1.0f);
    }

    // calculate projection matrix
    calc_projection_matrix();

    // initialize variables
    vector<Point> points;
    Point c0;
    Point c1;
    Point c2;
    vector<Point> homog_points;
    Point ndc_0;
    Point ndc_1;
    Point ndc_2;
    Point r0;
    Point r1;
    Point r2;
    float r0_r1_delta;
    float r1_r2_delta;
    float r2_r0_delta;
    vector<int> bounding_box;
    float triangle_area;
    Color surf_color;
    bool surf_diminish_light;
    Color pixel_color;
    Point p;
    Point barycentric_coords;
    double z_ndc;

    // perform drawing for each surface
    for (auto &surface : surfaces)
    {
        // transform points with projection matrix
        points = surface.get_points();
        c0 = matrix_mult(projection_matrix, points[0]);
        c1 = matrix_mult(projection_matrix, points[1]);
        c2 = matrix_mult(projection_matrix, points[2]);

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

            // only render triangle if vertices at least a pixel
            r0_r1_delta = abs(r0.x - r1.x) + abs(r0.y - r1.y);
            r1_r2_delta = abs(r1.x - r2.x) + abs(r1.y - r2.y);
            r2_r0_delta = abs(r2.x - r0.x) + abs(r2.y - r0.y);

            if ((r0_r1_delta > 1) && (r1_r2_delta > 1) && (r2_r0_delta > 1))
            {
                // get bounding box of these screen vertices
                bounding_box = get_bounding_box(r0, r1, r2, width, height);

                // set color
                surf_color = surface.get_color();

                // // used for debugging / visualizing polygon clipping
                // if (homog_points.size() > 3)
                // {
                //     if (i >= 12)
                //         surf_color = BLACK;
                //     else if (i >= 9)
                //         surf_color = YELLOW;
                //     else if (i >= 6)
                //         surf_color = GREEN;
                //     else if (i >= 3)
                //         surf_color = BLUE;
                //     else if (i < 3)
                //         surf_color = RED;
                // }

                // get surface light property
                surf_diminish_light = surface.get_diminish_light();

                // loop through bounding box to determine triangle points
                for (int x{bounding_box[0]}; x <= bounding_box[1]; ++x)
                {
                    p.x = static_cast<float>(x);
                    for (int y{bounding_box[2]}; y <= bounding_box[3]; ++y)
                    {
                        p.y = static_cast<float>(y);
                        // get and process barycentric coordinates
                        barycentric_coords = get_barycentric_coords(r0, r1, r2, p);

                        if (point_in_triangle(barycentric_coords, TOL_IN_TRIANGLE))
                        {
                            z_ndc = get_ndc_depth(barycentric_coords, homog_points[i], homog_points[i + 1], homog_points[i + 2]);
                            if (z_ndc < z_buffer[x][y])
                            {
                                z_buffer[x][y] = z_ndc;
                                if (surf_diminish_light)
                                    pixel_color = diminish_light(z_buffer[x][y], surf_color);
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