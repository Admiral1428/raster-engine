#ifndef CONSTANTS_H
#define CONSTANTS_H

struct Color
{
    unsigned char r; // Red (0-255)
    unsigned char g; // Green (0-255)
    unsigned char b; // Blue (0-255)
    unsigned char a; // Alpha (0-255, for transparency)
};

// Window dimensions

// Default renderer options
const int WIDTH{640};
const int HEIGHT{480};
const float PLANE_N{0.3f};   // near clipping plane
const float PLANE_F{100.0f}; // far clipping plane
const float FOV{90.0f};      // field of view in degrees
// Tolerances for rendering
const float TOL_IN_TRIANGLE{1e-4};   // tolerance check for coordinate in triangle
const float TOL_SHIFT_SURFACE{1e-6}; // tolerance used to offset surfaces to avoid z-fighting
// Diminished lighting options
const float Z_BRIGHT = 0.95;
const float Z_DARK = 0.99;
const float DARK_FACTOR = 0.75;
// Opaque colors
const Color BLACK = {0, 0, 0, 255};
const Color WHITE = {255, 255, 255, 255};
const Color RED = {255, 0, 0, 255};
const Color BLUE = {0, 0, 255, 255};
const Color GREEN = {0, 255, 0, 255};
const Color MEDGREEN = {0, 180, 0, 255};
const Color DKGREEN = {0, 100, 0, 255};
const Color YELLOW = {255, 255, 0, 255};
const Color MAGENTA = {255, 0, 255, 255};
const Color CYAN = {0, 255, 255, 255};
const Color BROWN = {150, 75, 0, 255};
const Color TAN = {210, 180, 140, 255};
const Color SKY_BLUE = {135, 206, 235, 255};
// Background color for screen
const Color BACK_COLOR = SKY_BLUE;

#endif