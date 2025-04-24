#ifndef PACKER_VSCANNER_HPP
#define PACKER_VSCANNER_HPP

#include "packer/data.hpp"
#include "packer/core/VImage.hpp"
#include "packer/packer.hpp"
PACKER_BEGIN

/* Scanner可以对一个VImage对象执行扫描，并在内部生成一个Rect用于记录VImage内非透明像素的范围 */
class VScanner{
public:
    virtual bool scan(int id, const VImage &img) =0;
    virtual Rect rangeOf(int id) const =0;
    virtual ~VScanner();
};

PACKER_END
#endif