#ifndef PACKER_VSCANNER_HPP
#define PACKER_VSCANNER_HPP

#include "packer/data/data.hpp"
#include "packer/core/VImage.hpp"
#include "packer/packer.hpp"
PACKER_BEGIN

/* Scanner可以对一个VImage对象执行扫描，并将VImage内非透明像素的范围记录于result */
class VScanner{
public:
    virtual bool scan(const VImage &img, Rect &result) =0;
    virtual ~VScanner();
};

PACKER_END
#endif