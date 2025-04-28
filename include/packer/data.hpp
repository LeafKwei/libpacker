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
};

struct Record{
    Profile profile;
    std::unique_ptr<VImage> imgptr;
    Record() : imgptr(nullptr){}
};

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