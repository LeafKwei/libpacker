#ifndef PACKER_VLAYOUTER_HPP
#define PACKER_VLAYOUTER_HPP

#include "packer/core/VRecorder.hpp"
#include "packer/packer.hpp"
PACKER_BEGIN

/* Layouter对每个单独的png文件计算它们在最终合并的png文件中的布局位置 */
class VLayouter{
    virtual void laydown(int width, int height) =0;
    virtual int finalWidth() const =0;
    virtual int finalHeight() const =0;
    virtual const VRecorder& getLayout() const =0;
    virtual ~VLayouter() =0;
};

PACKER_END
#endif