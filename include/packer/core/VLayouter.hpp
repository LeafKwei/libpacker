#ifndef PACKER_VLAYOUTER_HPP
#define PACKER_VLAYOUTER_HPP

#include "packer/core/VLayout.hpp"
#include "packer/packer.hpp"
PACKER_BEGIN

/* Layouter计算指定宽高的图片在最终合并的png文件中的布局位置 */
class VLayouter{
public:
    virtual void laydown(int id, int width, int height) =0;
    virtual const VLayout& getLayout() const =0;
    virtual ~VLayouter() =0;
};

PACKER_END
#endif