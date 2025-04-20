#ifndef PACKER_VIMAGE_HPP
#define PACKER_VIMAGE_HPP

#include "packer/data.hpp"
namespace packer{


/* 图片像素数据的接口，每一个RGBA结构体对应一个像素 */
class VImage{
public:
    virtual int width() const =0;
    virtual int height() const =0;
    virtual RGBA access(int x, int y) const =0;
    virtual void place(int x, int y, const RGBA &rgb) =0;
    virtual void PlaceRect(int x, int y, const VImage &src, const Rect &rect) =0;
    virtual const RGBA* accessAll() const =0;
    virtual ~VImage() =0;
};


}
#endif