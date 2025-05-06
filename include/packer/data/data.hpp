#ifndef PACKER_DATA_HPP
#define PACKER_DATA_HPP

#include <cstdint>
#include <string>
#include <memory>
#include "packer/packer.hpp"
#include "packer/core/VImage.hpp"
PACKER_BEGIN

struct Profile{
	std::string id;
    Rect srcRange;
    Rect dstRange;
    operator bool();
};

struct Record{
    Profile profile;
    std::unique_ptr<VImage> imgptr;
    Record();
    operator bool();
};

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

typedef RGBA_Struct RGBA;

PACKER_END
#endif