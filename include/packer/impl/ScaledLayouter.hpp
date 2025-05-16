#ifndef PACKER_SCALEDLAYOUTER_HPP
#define PACKER_SCALEDLAYOUTER_HPP

#include <functional>
#include "packer/core/VLayouter.hpp"
#include "packer/util/Bitmap.hpp"
PACKER_BEGIN

/**
 * scaledLayouter是VLayouter的一种实现，构造函数中，scale是像素的缩放比例，例如scale为16时，代表Layouter中的一个像素点对应一个16x16范围的像素块。
 * layouterWidth是布局宽度，layouterHeight是布局高度，当我们调用laydown计算一个图片的位置时，Layouter首先会将图片宽高除以scale，得到一个缩放后
 * 的宽高，然后再根据缩放后的宽高计算图片的位置
 * 
 * ScaledLayouter使用Bitmap记录未被占据的像素和已被占据的像素位置。使用scale的主要目的是减少Bitmap所需记录的像素数量，以此减少Layouter需要遍历
 * 的像素数量。laydown以及packedWidth和packedHeight在返回结果前都会先将结果乘以scale，以恢复正常的比例
 * 
 * ScaledLayouter的layouterWidth是固定不变的，因此用户需要确保将要合并的png的宽度在除以scale后要小于layouterWidth。当Layouter发现当前的高度
 * 无法容纳新的图片时，会选择扩展laytouerHeight，换句话说，ScaledLayouter只能纵向扩展，而不能横向扩展
 */
class ScaledLayouter : public VLayouter{
public:
    ScaledLayouter(int scale, int layouterWidth, int layouterHeight);
    Rect laydown(int imageWidth, int imageHeight) override;
    int packedWidth() const override;
    int packedHeight() const override;

private:
    int m_scale;
    int m_layouterWidth;
    int m_layouterHeight;
    Bitmap m_note;

    inline int scale(int value) const;
    Rect scaledLaydown(int scaledWidth, int scaledHeight);
    void setAt(int x, int y);
    void unsetAt(int x, int y);
    bool testAt(int x, int y);
    void rangedWork(const Rect &rect, std::function<void(int,int)> func);
    bool rangedTestAt(const Rect &rect);
    void rangedSetAt(const Rect &rect);
    void rangedUnsetAt(const Rect &rect);
    void expandHeight(int increment);
    int transDimension(int x, int y) const;
    Rect calcRange(int scaledWidth, int scaledHeight);
};

PACKER_END
#endif