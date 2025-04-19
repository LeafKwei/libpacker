#ifndef PACKER_VIRTIMAGE_HPP
#define PACKER_VIRTIMAGE_HPP

#include "packer/data.hpp"
namespace packer{

/* 图片像素数据的接口，每一个RGBA结构体对应一个像素 */
class VirtImage{
public:
    virtual int width() const =0;
    virtual int height() const =0;
    virtual RGBA access(int x, int y) const =0;
    virtual void place(int x, int y, const RGBA &rgb) =0;
    virtual const RGBA* accessAll() const =0;
};


}
#endif