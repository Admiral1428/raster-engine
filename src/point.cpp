#include "point.hpp"

// normalize by w component
void normalize_point(Eigen::Vector4f &c)
{
    if (c(3) != 0.0f)
    {
        c(0) /= c(3);
        c(1) /= c(3);
        c(2) /= c(3);
        c(3) /= c(3);
    }
}

// normalize to get unit vector
void normalize_to_unit_vector(Eigen::Vector3f &c)
{
    Eigen::Vector3f result;
    // Calculate the magnitude
    float magnitude = sqrt(c(0) * c(0) + c(1) * c(1) + c(2) * c(2));

    if (magnitude > 0.0f)
    {
        result(0) = c(0) / magnitude;
        result(1) = c(1) / magnitude;
        result(2) = c(2) / magnitude;
    }
    else // divide by zero case
    {
        result(0) = 0.0f;
        result(1) = 0.0f;
        result(2) = 0.0f;
    }
    c = result;
}

void rasterize_point(Eigen::Vector4f &c, const int &width, const int &height)
{
    float x = (c(0) + 1) * 0.5 * width;
    float y = (1 - (c(1) + 1) * 0.5) * height;
    c(0) = x;
    c(1) = y;
}

Eigen::Vector4i get_bounding_box(const Eigen::Vector4f &r0, const Eigen::Vector4f &r1, const Eigen::Vector4f &r2, const int &width, const int &height)
{
    int min_x = static_cast<int>(round(min({r0(0), r1(0), r2(0)})));
    int max_x = static_cast<int>(round(max({r0(0), r1(0), r2(0)})));
    int min_y = static_cast<int>(round(min({r0(1), r1(1), r2(1)})));
    int max_y = static_cast<int>(round(max({r0(1), r1(1), r2(1)})));

    // Limit to screen dimensions
    min_x = max(0, min_x);
    max_x = min(width - 1, max_x);
    min_y = max(0, min_y);
    max_y = min(height - 1, max_y);

    return Eigen::Vector4i(min_x, max_x, min_y, max_y);
}

vector<Eigen::VectorXf> get_barycentric_coords(const Eigen::Vector4f &r0, const Eigen::Vector4f &r1, const Eigen::Vector4f &r2,
                                               const Eigen::VectorXf &px, const Eigen::VectorXf &py)
{
    Eigen::Vector2f v0(r1(0) - r0(0), r1(1) - r0(1));
    Eigen::Vector2f v1(r2(0) - r0(0), r2(1) - r0(1));
    // v2 without vectorization is (p(0) - r0(0), p(1) - r0(1))

    // dot products of vectors
    float dot_00 = v0.dot(v0);
    float dot_01 = v0.dot(v1);
    float dot_11 = v1.dot(v1);

    int vec_size = px.size();

    // constant vectors
    auto r0_0 = Eigen::VectorXf::Constant(vec_size, r0(0));
    auto r0_1 = Eigen::VectorXf::Constant(vec_size, r0(1));
    auto ones = Eigen::VectorXf::Ones(vec_size);

    // dot products requiring vectorized v2
    auto p_minus_r0_x = px - r0_0;
    auto p_minus_r0_y = py - r0_1;
    auto dot_20 = p_minus_r0_x * v0(0) + p_minus_r0_y * v0(1);
    auto dot_21 = p_minus_r0_x * v1(0) + p_minus_r0_y * v1(1);

    float inv_denom = 1.0f / (dot_00 * dot_11 - dot_01 * dot_01);

    // get vectors of results
    auto beta = (dot_11 * dot_20 - dot_01 * dot_21) * inv_denom;
    auto gamma = (dot_00 * dot_21 - dot_01 * dot_20) * inv_denom;
    auto alpha = (ones - beta - gamma);

    vector<Eigen::VectorXf> result{alpha, beta, gamma};
    return result;
}

vector<Eigen::VectorXf> get_points_in_triangle(const vector<Eigen::VectorXf> barycentric_coords,
                                               const Eigen::VectorXf &px, const Eigen::VectorXf &py)
{
    Eigen::ArrayX<bool> in_triangle = (barycentric_coords[0].array() >= -TOL_IN_TRIANGLE) &&
                                      (barycentric_coords[1].array() >= -TOL_IN_TRIANGLE) &&
                                      (barycentric_coords[2].array() >= -TOL_IN_TRIANGLE);

    // Count the number of positive elements to determine the size of the new vectors
    int num_valid = in_triangle.count();

    // Initialize new vectors to store the subset
    Eigen::VectorXf alpha_subset(num_valid);
    Eigen::VectorXf beta_subset(num_valid);
    Eigen::VectorXf gamma_subset(num_valid);
    Eigen::VectorXf px_subset(num_valid);
    Eigen::VectorXf py_subset(num_valid);

    int counter{0};
    for (int i{0}; i < px.size(); ++i)
    {
        if (in_triangle(i))
        {
            alpha_subset(counter) = barycentric_coords[0](i);
            beta_subset(counter) = barycentric_coords[1](i);
            gamma_subset(counter) = barycentric_coords[2](i);
            px_subset(counter) = px(i);
            py_subset(counter) = py(i);
            ++counter;
        }
    }

    return {alpha_subset, beta_subset, gamma_subset, px_subset, py_subset};
}

Eigen::VectorXf get_ndc_depth(const vector<Eigen::VectorXf> &barycentric_and_pixels,
                              const Eigen::Vector4f &c0, const Eigen::Vector4f &c1, const Eigen::Vector4f &c2)
{
    // Initialize vector as ones, to handle edge case for divide by zero
    int vec_size = barycentric_and_pixels[0].size();
    Eigen::VectorXf interp_z_over_w = Eigen::VectorXf::Ones(vec_size);

    if (c0(3) != 0.0f && c1(3) != 0.0f && c2(3) != 0.0f)
    {
        interp_z_over_w = barycentric_and_pixels[0] * (c0(2) / c0(3)) +
                          barycentric_and_pixels[1] * (c1(2) / c1(3)) +
                          barycentric_and_pixels[2] * (c2(2) / c2(3));
    }
    return interp_z_over_w;
}

bool is_surface_visible(const Eigen::Vector4f &v0, const Eigen::Vector4f &v1, const Eigen::Vector4f &v2)
{
    Eigen::Vector3f normal = get_normal_vector(v0, v1, v2);

    // form a vector from the camera towards any point on triangle
    Eigen::Vector3f towards_triangle(v0(0), v0(1), v0(2));

    float sign = normal.dot(towards_triangle);

    // surface facing camera
    if (sign > 0.0f)
    {
        return true;
    }
    // collinear or facing away
    return false;
}

Eigen::Vector3f get_normal_vector(const Eigen::Vector4f &c0, const Eigen::Vector4f &c1, const Eigen::Vector4f &c2)
{
    // x, y, z vectors representing two edges from a given vertex (0)
    Eigen::Vector3f vec_01(c1(0) - c0(0), c1(1) - c0(1), c1(2) - c0(2));
    Eigen::Vector3f vec_02(c2(0) - c0(0), c2(1) - c0(1), c2(2) - c0(2));

    Eigen::Vector3f normal = vec_01.cross(vec_02);
    normalize_to_unit_vector(normal);
    return (normal);
}