#ifndef PACKER_DATA_HPP
#define PACKER_DATA_HPP

#include <cstdint>
namespace packer{


struct RGBA{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

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


}
#endif