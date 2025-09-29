#ifndef POINT_H
#define POINT_H

struct Point
{
    float x; // + right
    float y; // + down
    float z; // + towards the screen
};

// // class defining a triangular surface
// class Surface
// {
// private:
//     Point p1;
//     Point p2;
//     Point p3;

// public:
//     Surface(); // default constructor (initializes object to default state with no arguments)
//     Surface(const Point &_p1, const Point &_p2, const Point &_p3);
//     Surface(const Surface &);            // copy constructor
//     ~Surface();                          // destructor
//     Surface &operator=(const Surface &); // copy/assignment operator
// };

// // implementation
// Surface::Surface() : p1({-1.0f, -1.0f, 0.0f}), p2(-1.0f, -1.0f, 0.0f), p3(-1.0f, -1.0f, 0.0f) {}
// Surface::Surface(const Point &_p1, const Point &_p2, const Point &_p3) : p1(_p1), p2(_p2), p3(_p3) {}
// Surface::Surface(const Surface &s)
// {
//     p1 = s.p1;
//     p2 = s.p2;
//     p3 = s.p3;
// }

// Surface::~Surface() {}

// Surface &Surface::operator=(const Surface &s)
// {
//     if (this != &s)
//     {
//         p1 = s.p1;
//         p2 = s.p2;
//         p3 = s.p3;
//     }
//     return *this;
// }

#endif