#include "packer/util/util.hpp"

inline bool isBadCoord(int x, int y, int width, int height){
    if(x < 0 || y < 0 || x >= width || y >= height)  return true;
    return false;
}