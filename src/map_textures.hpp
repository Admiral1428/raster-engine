#ifndef MAP_TEXTURES_HPP
#define MAP_TEXTURES_HPP

#include <unordered_map>
#include <string>
#include "constants.h"
#include "texture.hpp"

using std::string;
using std::unordered_map;

extern unordered_map<string, Texture> TEXTURES;

void load_textures();

#endif