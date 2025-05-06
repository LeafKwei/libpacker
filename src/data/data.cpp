#include "packer/data/data.hpp"
PACKER_BEGIN

Record::Record() : imgptr(nullptr){}
Point::Point() : x(0), y(0) {}
Rect::Rect() : x(0), y(0), width(0), height(0) {}
RGBA_Struct::RGBA_Struct() : r(0), g(0), b(0), a(0) {}

Profile::operator bool(){
    if(id.length() == 0) return false;
    return true;
}

Record::operator bool(){
    return profile && (imgptr != nullptr);
}

Point::operator bool(){
    return x >= 0 && y >= 0;
}

Rect::operator bool(){
    return x >= 0 && y >= 0;
}

PACKER_END