#ifndef PACKER_SCALEDLAYOUTER_HPP
#define PACKER_SCALEDLAYOUTER_HPP

#include "packer/core/VLayouter.hpp"
#include "packer/util/Bitmap.hpp"
PACKER_BEGIN

class ScaledLayouter : public VLayouter{
public:
    ScaledLayouter();
    ScaledLayouter(int scale, int layouterWidth, int layouterHeight);
    void laydown(int imageWidth, int imageHeight, Rect &result) override;
    int packedImageWidth() const override;
    int packedImageHeight() const override;

private:
    int m_scale;
    int m_layouterWidth;
    int m_layouterHeight;
    Bitmap m_note;

    inline int scale(int value) const;
    void setAt(int x, int y);
    void unsetAt(int x, int y);
    bool testAt(int x, int y);
    bool testAtRect(const Rect &rect);
    void rangedSetAt(const Rect &rect);
    void rangedUnsetAt(const Rect &rect);
    void expandHeight(int increment);
    int transDimension(int x, int y);
};

PACKER_END
#endif