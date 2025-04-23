#ifndef PACKER_VSCANNER_HPP
#define PACKER_VSCANNER_HPP

#include "packer/data.hpp"
#include "packer/core/VImage.hpp"
#include "packer/packer.hpp"
PACKER_BEGIN

/* Scanner可以对一个VImage对象执行扫描，并返回Rect指出VImage中非透明像素的范围 */
class VScanner{
public:
    virtual bool scan(const VImage &img, Rect &result) const =0;
    virtual ~VScanner() =0;
};

PACKER_END
#endif