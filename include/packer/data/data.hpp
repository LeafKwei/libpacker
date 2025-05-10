#ifndef PACKER_DATA_HPP
#define PACKER_DATA_HPP

#include <cstdint>
#include <string>
#include <memory>
#include "packer/packer.hpp"
PACKER_BEGIN
class VImage;

struct Point{
    int x;
    int y;
    Point();
    operator bool();
};

struct Rect{
    int x;
    int y;
    int width;
    int height;
    Rect();
    operator bool();
};

struct RGBA_Struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    RGBA_Struct();
};
struct Profile{
	std::string id;
    Rect srcRange;
    Rect dstRange;
    operator bool();
};

struct Record{
    Profile profile;
    VImage *imgptr;
    Record();
    operator bool();
};

typedef RGBA_Struct RGBA;

PACKER_END
#endif