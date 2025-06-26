#ifndef PACKER_VLAYOUTER_HPP
#define PACKER_VLAYOUTER_HPP

#include "packer/packer.hpp"
#include "packer/data/data.hpp"
PACKER_BEGIN

/**
 *  VLayouter是一个布局管理器，它的作用是计算一个指定宽高的图片在最后合并得到的图片中的位置。
 *  VLayouter还需要提供可以获取最后合并的图片的宽高的接口
 */
class VLayouter{
public:
    virtual Rect laydown(ImageSize size) =0;  //计算指定宽高的图片在最终合并得到的图片中的位置
    virtual int packedWidth() const =0;          //获取最终合并得到的图片所需的宽度
    virtual int packedHeight() const =0;         //获取最终合并得到的图片所需的高度
    virtual ~VLayouter();
};

PACKER_END
#endif