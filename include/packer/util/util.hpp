#ifndef PACKER_UTIL_HPP
#define PACKER_UTIL_HPP

#include "packer/packer.hpp"
#include "packer/data/data.hpp"
PACKER_BEGIN

inline bool isBadCoord(int x, int y, int width, int height){
    if(x < 0 || y < 0 || x >= width || y >= height)  return true;
    return false;
}

PACKER_END
#endif