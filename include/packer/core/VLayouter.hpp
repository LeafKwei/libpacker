#ifndef PACKER_VLAYOUTER_HPP
#define PACKER_VLAYOUTER_HPP

#include "packer/packer.hpp"
#include "packer/data.hpp"
PACKER_BEGIN

/* Layouter计算指定宽高的图片在最终合并的png文件中的布局位置 */
class VLayouter{
public:
    virtual void laydown(int id, int width, int height) =0;
    virtual int currentWidth() const =0;
    virtual int currentHeight() const =0;
    virtual Rect rangeOf(int id) const =0;
    virtual ~VLayouter();
};

PACKER_END
#endif