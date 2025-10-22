#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <Eigen/Dense>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include "constants.h"
#include <cmath>
#include <vector>

using std::fmod;
using std::invalid_argument;
using std::string;
using std::vector;
using std::numbers::pi;

// class defining a texture
class Texture
{
private:
    vector<string> paths;
    std::vector<SDL_Surface *> surfaces;
    float width;
    float height;
    int frame;
    Uint64 last_frame_update_counter;
    float perf_frequency;
    float animation_dt;

public:
    Texture(); // default constructor (initializes object to default state with no arguments)
    Texture(const vector<string> &_paths, const float &animation_dt);
    Texture(const Texture &);            // copy constructor
    ~Texture();                          // destructor
    Texture &operator=(const Texture &); // copy/assignment operator
    void load_texture();
    void update_animation();
    Color get_color(const float &u, const float &v);
};

#endif