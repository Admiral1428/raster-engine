#include "lighting.hpp"

Color diminish_light(float &z_buffer_val, Color &surf_color)
{
    Color final_color = surf_color;
    float factor{1.0f};
    if (z_buffer_val > Z_DARK)
        factor = DARK_FACTOR;
    else if (z_buffer_val >= Z_BRIGHT)
        factor = (1.0f - DARK_FACTOR) * (z_buffer_val - Z_DARK) / (Z_BRIGHT - Z_DARK) + DARK_FACTOR;

    final_color.r *= factor;
    final_color.g *= factor;
    final_color.b *= factor;

    return final_color;
}

float color_interp(const float &start, const float &end, const float &p)
{
    return start + p * (end - start);
}

Color get_sky_color(float angle)
{
    // Normalize angle to within 0, 360 range
    angle = fmod(angle, 360.0f);
    if (angle < 0)
    {
        angle += 360.0f;
    }

    Color start_color, end_color;
    float p;

    // Determine interpolation segment based on the angle.
    if (angle >= 30 && angle < 150)
    {
        // Constant SKY_BLUE from 30 to 150 degrees
        return SKY_BLUE;
    }
    else if (angle >= 210 && angle < 330)
    {
        // Constant NIGHTBLUE from 210 to 330 degrees
        return NIGHTBLUE;
    }
    else if (angle >= 0 && angle < 30)
    {
        // Interpolate SALMON (0) to SKY_BLUE (30)
        start_color = SALMON;
        end_color = SKY_BLUE;
        p = angle / 30.0f;
    }
    else if (angle >= 150 && angle < 180)
    {
        // Interpolate SKY_BLUE (150) to SALMON (180)
        start_color = SKY_BLUE;
        end_color = SALMON;
        p = (angle - 150.0f) / 30.0f;
    }
    else if (angle >= 180 && angle < 210)
    {
        // Interpolate SALMON (180) to NIGHTBLUE (210)
        start_color = SALMON;
        end_color = NIGHTBLUE;
        p = (angle - 180.0f) / 30.0f;
    }
    else // angle >= 330 && angle < 360 (or 0)
    {
        // Interpolate NIGHTBLUE (330) to SALMON (360/0)
        start_color = NIGHTBLUE;
        end_color = SALMON;
        p = (angle - 330.0f) / 30.0f;
    }

    // Clamp the percentage to ensure it is between 0.0 and 1.0.
    p = clamp(p, 0.0f, 1.0f);

    // Interpolate each color channel.
    Color result;
    result.r = color_interp(start_color.r, end_color.r, p);
    result.g = color_interp(start_color.g, end_color.g, p);
    result.b = color_interp(start_color.b, end_color.b, p);
    result.a = color_interp(start_color.a, end_color.a, p);

    return result;
}

float get_brightness(Light &light_source, const Eigen::Vector4f &p0,
                     const Eigen::Vector4f &p1, const Eigen::Vector4f &p2,
                     const float min_brightness, const float max_brightness)
{
    float result;
    Eigen::Vector4f average_vec = (p0 + p1 + p2) / 3.0f;

    Eigen::Vector3f light_pos = light_source.get_points();
    Eigen::Vector2f brightness_factors = light_source.get_brightness_factors();
    Eigen::Vector2f height_thresholds = light_source.get_height_thresholds();

    // linear interpolation using height
    float brightness_factor = brightness_factors(0) +
                              (brightness_factors(1) - brightness_factors(0)) *
                                  (light_pos(1) - height_thresholds(0)) /
                                  (height_thresholds(1) - height_thresholds(0));

    // vector from light to center of surface
    Eigen::Vector3f light_to_surface(average_vec(0) - light_pos(0),
                                     average_vec(1) - light_pos(1),
                                     average_vec(2) - light_pos(2));
    // normalize into a unit vector
    light_to_surface.normalize();

    // get surface normal vector
    Eigen::Vector3f normal_vector = get_normal_vector(p0, p1, p2);

    // Get dot product of vectors to find cosine of angle between them
    float cos_theta = normal_vector.dot(light_to_surface);

    if (cos_theta < min_brightness)
    {
        result = min_brightness * brightness_factor;
    }
    else if (cos_theta > max_brightness)
    {
        result = max_brightness * brightness_factor;
    }
    else
    {
        result = cos_theta * brightness_factor;
    }

    // Clamp to range between 0 and 1
    return clamp(result, 0.0f, 1.0f);
}

Color apply_light(float &brightness, Color &surf_color)
{
    Color final_color = surf_color;

    final_color.r *= brightness;
    final_color.g *= brightness;
    final_color.b *= brightness;

    return final_color;
}