#include "texture.hpp"

// implementation
Texture::Texture() : width(0), height(0), frame(0), last_frame_update_counter(0), perf_frequency(0.0)
{
    perf_frequency = static_cast<double>(SDL_GetPerformanceFrequency());
}

Texture::Texture(const std::vector<std::string> &_paths, const float &_animation_dt)
    : paths(_paths), animation_dt(_animation_dt), width(0), height(0), frame(0), last_frame_update_counter(0), perf_frequency(0.0)
{
    perf_frequency = static_cast<double>(SDL_GetPerformanceFrequency());
    load_texture();
}

Texture::Texture(const Texture &t)
{
    paths = t.paths;
    width = t.width;
    height = t.height;
    frame = t.frame;
    animation_dt = t.animation_dt;
    last_frame_update_counter = t.last_frame_update_counter;
    perf_frequency = t.perf_frequency;

    // Deep copy of all surfaces
    for (const auto &surface : t.surfaces)
    {
        surfaces.push_back(SDL_DuplicateSurface(surface));
    }
}

Texture::~Texture()
{
    for (auto &surface : surfaces)
    {
        if (surface)
        {
            SDL_DestroySurface(surface);
        }
    }
}

Texture &Texture::operator=(const Texture &t)
{
    if (this != &t)
    {
        // Free existing surfaces
        for (auto &surface : surfaces)
        {
            if (surface)
            {
                SDL_DestroySurface(surface);
            }
        }
        surfaces.clear();

        paths = t.paths;
        width = t.width;
        height = t.height;
        frame = t.frame;
        animation_dt = t.animation_dt;
        last_frame_update_counter = t.last_frame_update_counter;
        perf_frequency = t.perf_frequency;

        // Deep copy of all surfaces
        for (const auto &surface : t.surfaces)
        {
            surfaces.push_back(SDL_DuplicateSurface(surface));
        }
    }
    return *this;
}

void Texture::load_texture()
{
    // Clear any existing surfaces before loading new ones
    for (auto &surface : surfaces)
    {
        if (surface)
        {
            SDL_DestroySurface(surface);
        }
    }
    surfaces.clear();

    for (const auto &path : paths)
    {
        SDL_Surface *temp_surface = IMG_Load(path.c_str());
        if (!temp_surface)
        {
            SDL_Log("Failed to load image: %s", path.c_str());
        }
        else
        {
            surfaces.push_back(temp_surface);
        }
    }

    if (!surfaces.empty())
    {
        width = surfaces[0]->w;
        height = surfaces[0]->h;
        // Initialize the last update time
        last_frame_update_counter = SDL_GetPerformanceCounter();
    }
}

void Texture::update_animation()
{
    if (surfaces.size() > 1 && animation_dt > 0.0f)
    {
        Uint64 current_counter = SDL_GetPerformanceCounter();
        float elapsed_seconds = static_cast<float>(current_counter - last_frame_update_counter) / perf_frequency;

        if (elapsed_seconds >= animation_dt)
        {
            // Update the frame
            frame = (frame + 1) % surfaces.size();
            // Reset the timer, accounting for the excess time
            last_frame_update_counter = current_counter;
        }
    }
}

Color Texture::get_color(const float &u, const float &v)
{
    // perform wrap around to account for coordinates below 0 or above 1
    float u_wrap = fmod(u, 1.0f);
    float v_wrap = fmod(v, 1.0f);

    // perform wrapping for negative values
    if (u_wrap < 0.0f)
    {
        u_wrap += 1.0f;
    }
    if (v_wrap < 0.0f)
    {
        v_wrap += 1.0f;
    }

    int pixel_x = static_cast<int>(u_wrap * width);
    int pixel_y = static_cast<int>(v_wrap * height);

    Uint8 r, g, b, a;

    if (!surfaces.empty() && surfaces[frame])
    {
        SDL_ReadSurfacePixel(surfaces[frame], pixel_x, pixel_y, &r, &g, &b, &a);
    }
    else
    {
        // If surface is invalid
        r = g = b = a = 0;
    }

    return Color(r, g, b, a);
}
