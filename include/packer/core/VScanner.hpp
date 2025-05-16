#ifndef PACKER_VSCANNER_HPP
#define PACKER_VSCANNER_HPP

#include "packer/data/data.hpp"
#include "packer/core/VImage.hpp"
#include "packer/packer.hpp"
PACKER_BEGIN

/**
 * VScanner提供扫描器的功能，它可以对一个VImage对象执行扫描，并最终获取一个保存在result中的矩形区域，
 * 该矩形区域囊括了VImage中非透明像素所在的范围。Scanner的主要目的是过滤掉图片中的透明像素
 */
class VScanner{
public:
    virtual void scan(const VImage &img, Rect &result) =0;
    virtual ~VScanner();
};

PACKER_END
#endif