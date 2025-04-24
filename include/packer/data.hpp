#ifndef PACKER_DATA_HPP
#define PACKER_DATA_HPP

#include <cstdint>
#include "packer/packer.hpp"
PACKER_BEGIN

struct Point{
    int x;
    int y;
    Point() : x(0), y(0) {}
};

struct Rect{
    int x;
    int y;
    int width;
    int height;
    Rect() : x(0), y(0), width(0), height(0) {}
};

struct RGBA_Struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    RGBA_Struct() : r(0), g(0), b(0), a(0) {}
};

typedef RGBA_Struct RGBA;

PACKER_END
#endif