#ifndef PACKER_DATA_HPP
#define PACKER_DATA_HPP

#include <cstdint>
#include "packer/packer.hpp"
PACKER_BEGIN

struct Point{
    int x;
    int y;
};

struct Rect{
    int x1;
    int y1;
    int x2;
    int y2;
};

struct RGBA_Struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

typedef RGBA_Struct RGBA;

PACKER_END
#endif