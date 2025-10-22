#include "map_textures.hpp"

unordered_map<string, Texture> TEXTURES;

void load_textures()
{
    TEXTURES.emplace("test", Texture({"../assets/textures/test.png"}, 0.0f));
    TEXTURES.emplace("waterfall", Texture({"../assets/textures/RE_Waterfall1.png",
                                           "../assets/textures/RE_Waterfall2.png",
                                           "../assets/textures/RE_Waterfall3.png",
                                           "../assets/textures/RE_Waterfall4.png"},
                                          0.25f));
    TEXTURES.emplace("water", Texture({"../assets/textures/RE_Water1.png",
                                       "../assets/textures/RE_Water2.png",
                                       "../assets/textures/RE_Water3.png",
                                       "../assets/textures/RE_Water4.png"},
                                      0.25f));
}