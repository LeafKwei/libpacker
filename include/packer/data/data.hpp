#ifndef PACKER_DATA_HPP
#define PACKER_DATA_HPP

#include <cstdint>
#include <string>
#include <memory>
#include "packer/packer.hpp"
PACKER_BEGIN
class VImage;

enum class State{
    PK_EMPTY,             //Packer内没有添加任何reader(初始状态)
    PK_PACKED,           //Packer已执行过打包操作
    UPK_NOP,              //Unpacker未执行任何操作(初始状态)
    UPK_UNPACKED   //Unpacker已执行过解包操作
};

enum class Indicator{
    RD_OK,                     //读取成功
    RD_EOF,                    //已到达文件末尾
    RD_INCOMPLETE     //信息不完整(例如字段缺失或者该文本是一个空行)
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