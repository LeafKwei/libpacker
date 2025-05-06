#ifndef PACKER_VLAYOUTER_HPP
#define PACKER_VLAYOUTER_HPP

#include "packer/packer.hpp"
#include "packer/data/data.hpp"
PACKER_BEGIN

/* Layouter计算指定宽高的图片在最终合并的png文件中的布局位置 */
class VLayouter{
public:
    virtual void laydown(int imageWidth, int imageHeight, Rect &result) =0;
    virtual int packedImageWidth() const =0;
    virtual int packedImageHeight() const =0;
    virtual ~VLayouter();
};

PACKER_END
#endif