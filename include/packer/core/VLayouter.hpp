#ifndef PACKER_VLAYOUTER_HPP
#define PACKER_VLAYOUTER_HPP

#include "packer/packer.hpp"
#include "packer/data/data.hpp"
PACKER_BEGIN

/* Layouter计算指定宽高的图片在最终合并的png文件中的布局位置 */
class VLayouter{
public:
    virtual Rect laydown(int imageWidth, int imageHeight) =0;
    virtual int packedWidth() const =0;
    virtual int packedHeight() const =0;
    virtual ~VLayouter();
};

PACKER_END
#endif