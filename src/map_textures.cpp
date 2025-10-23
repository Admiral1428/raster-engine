#include "map_textures.hpp"

unordered_map<string, Texture> TEXTURES;

void load_textures()
{
    TEXTURES.emplace("test", Texture({"../assets/textures/test.png"}, 0.0f));
    TEXTURES.emplace("waterfall", Texture({"../assets/textures/RE_Waterfall1.png",
                                           "../assets/textures/RE_Waterfall2.png",
                                           "../assets/textures/RE_Waterfall3.png",
                                           "../assets/textures/RE_Waterfall4.png",
                                           "../assets/textures/RE_Waterfall5.png"},
                                          0.1f));
    TEXTURES.emplace("water", Texture({
                                          "../assets/textures/RE_Water1.png",
                                          "../assets/textures/RE_Water2.png",
                                          "../assets/textures/RE_Water3.png",
                                      },
                                      0.25f));
    TEXTURES.emplace("wood", Texture({"../assets/textures/RE_Wood.png"}, 0.0f));
    TEXTURES.emplace("grass", Texture({"../assets/textures/RE_Grass.png"}, 0.0f));
    TEXTURES.emplace("grass_dark", Texture({"../assets/textures/RE_GrassDark.png"}, 0.0f));
    TEXTURES.emplace("dirt", Texture({"../assets/textures/RE_Dirt.png"}, 0.0f));
    TEXTURES.emplace("dirt_dark", Texture({"../assets/textures/RE_DirtDark.png"}, 0.0f));
    TEXTURES.emplace("snow", Texture({"../assets/textures/RE_Snow.png"}, 0.0f));
    TEXTURES.emplace("snow_dark", Texture({"../assets/textures/RE_SnowDark.png"}, 0.0f));
    TEXTURES.emplace("leaves", Texture({"../assets/textures/RE_Leaves.png"}, 0.0f));
    TEXTURES.emplace("leaves_bright", Texture({"../assets/textures/RE_LeavesBright.png"}, 0.0f));
    TEXTURES.emplace("sand", Texture({"../assets/textures/RE_Sand.png"}, 0.0f));
    TEXTURES.emplace("rock", Texture({"../assets/textures/RE_Rock.png"}, 0.0f));

    TEXTURES.emplace("mountain", Texture({"../assets/textures/RE_Mountain.png"}, 0.0f));
    TEXTURES.emplace("mountain_dark", Texture({"../assets/textures/RE_MountainDark.png"}, 0.0f));

    TEXTURES.emplace("metal", Texture({"../assets/textures/RE_Metal.png"}, 0.0f));
    TEXTURES.emplace("metal_horz", Texture({"../assets/textures/RE_MetalHorz.png"}, 0.0f));
    TEXTURES.emplace("stone", Texture({"../assets/textures/RE_Stone.png"}, 0.0f));
    TEXTURES.emplace("bright_stone", Texture({"../assets/textures/RE_BrightStone.png"}, 0.0f));
    TEXTURES.emplace("gray_rock", Texture({"../assets/textures/RE_GrayRock.png"}, 0.0f));
    TEXTURES.emplace("dark_gray_rock", Texture({"../assets/textures/RE_DkGrayRock.png"}, 0.0f));

    TEXTURES.emplace("brick", Texture({"../assets/textures/RE_Brick.png"}, 0.0f));
    TEXTURES.emplace("siding", Texture({"../assets/textures/RE_Siding.png"}, 0.0f));
    TEXTURES.emplace("roof", Texture({"../assets/textures/RE_Roof.png"}, 0.0f));
    TEXTURES.emplace("window", Texture({"../assets/textures/RE_House_Glass.png"}, 0.0f));
    TEXTURES.emplace("door", Texture({"../assets/textures/RE_Door.png"}, 0.0f));

    TEXTURES.emplace("boat", Texture({"../assets/textures/RE_Boat.png"}, 0.0f));
    TEXTURES.emplace("boat_dark", Texture({"../assets/textures/RE_BoatDark.png"}, 0.0f));
    TEXTURES.emplace("cloth", Texture({"../assets/textures/RE_Cloth1.png",
                                       "../assets/textures/RE_Cloth2.png"},
                                      0.5f));

    TEXTURES.emplace("runway", Texture({"../assets/textures/RE_Runway.png"}, 0.0f));
    TEXTURES.emplace("runway_marking", Texture({"../assets/textures/RE_RunwayMarking.png"}, 0.0f));
    TEXTURES.emplace("ceiling", Texture({"../assets/textures/RE_Ceiling.png"}, 0.0f));

    TEXTURES.emplace("plane", Texture({"../assets/textures/RE_Plane.png"}, 0.0f));
    TEXTURES.emplace("plane_back", Texture({"../assets/textures/RE_Plane_Back.png"}, 0.0f));
    TEXTURES.emplace("plane_left", Texture({"../assets/textures/RE_Plane_Left.png"}, 0.0f));
    TEXTURES.emplace("plane_right", Texture({"../assets/textures/RE_Plane_Right.png"}, 0.0f));
    TEXTURES.emplace("plane_wing", Texture({"../assets/textures/RE_Plane_Rib.png"}, 0.0f));
    TEXTURES.emplace("plane_glass", Texture({"../assets/textures/RE_Plane_Glass.png"}, 0.0f));
    TEXTURES.emplace("plane_glass_side", Texture({"../assets/textures/RE_Plane_Glass_Side.png"}, 0.0f));
    TEXTURES.emplace("plane_engine", Texture({"../assets/textures/RE_Plane_Engine.png"}, 0.0f));
}