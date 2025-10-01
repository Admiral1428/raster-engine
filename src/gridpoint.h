#ifndef GRIDPOINT_H
#define GRIDPOINT_H

struct GridPoint
{
    int x;   // + right from top left of window
    int y;   // + down from top left of window
    float z; // between 0 and 1 if within view frustum
};

#endif