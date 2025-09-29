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
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
// Opaque colors
const Color BLACK = {0, 0, 0, 255};
const Color WHITE = {255, 255, 255, 255};

#endif