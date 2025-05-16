#ifndef PACKER_VIMAGE_HPP
#define PACKER_VIMAGE_HPP

#include "packer/data/data.hpp"
#include "packer/packer.hpp"
PACKER_BEGIN

/**
 * VImage类用于将图片的像素数据从具体的图片(如png)中抽象出来，
 * 以实现一个与具体图片类型无关的像素数据管理接口
 */
class VImage{
public:
    virtual int width() const =0;
    virtual int height() const =0;
    virtual RGBA access(int x, int y) const =0;          //获取x,y坐标位置的像素
    virtual RGBA* accessAll() =0;                              //获取所有的像素数据
    virtual void place(int x, int y, const RGBA &rgb) =0;  //将x,y坐标位置的像素设置为指定像素
    virtual void placeRect(int x, int y, const VImage &src, const Rect &rect) =0; //将src中的由rect指定的范围内的像素拷贝到当前图片的x,y坐标开始的位置
    virtual ~VImage();
};

PACKER_END
#endif