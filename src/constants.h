#ifndef SURFACE_H
#define SURFACE_H

struct Color
{
    unsigned char r; // Red (0-255)
    unsigned char g; // Green (0-255)
    unsigned char b; // Blue (0-255)
    unsigned char a; // Alpha (0-255, for transparency)
};

// Window dimensions

// Default renderer options
const int WIDTH = 1080;
const int HEIGHT = 1080;
const float PLANE_N = 0.1f;   // near clipping plane
const float PLANE_F = 100.0f; // far clipping plane
const float FOV = 90.0f;      // field of view in degrees
// Opaque colors
const Color BLACK = {0, 0, 0, 255};
const Color WHITE = {255, 255, 255, 255};
const Color RED = {255, 0, 0, 255};
const Color BLUE = {0, 0, 255, 255};
const Color GREEN = {0, 255, 0, 255};
const Color YELLOW = {255, 255, 0, 255};
const Color MAGENTA = {255, 0, 255, 255};
const Color CYAN = {0, 255, 255, 255};

#endif