#ifndef MAP_SOUNDS_HPP
#define MAP_SOUNDS_HPP

#include <SDL3/SDL_mixer.h>
#include <unordered_map>
#include <string>
#include "sound.hpp"

using std::string;
using std::unordered_map;

extern unordered_map<string, Sound> SOUNDS;

void load_sounds(MIX_Mixer &mixer);
void start_sounds();
void set_sound_gains(const Eigen::Vector3f &eye);
void move_sound(const string sound_name, const float &dx, const float &dy, const float &dz,
                const float &roll, const float &pitch, const float &yaw, const string &order);
void destroy_sounds();

#endif