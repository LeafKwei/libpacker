#ifndef PACKER_SCALEDLAYOUTER_HPP
#define PACKER_SCALEDLAYOUTER_HPP

#include <functional>
#include "packer/core/VLayouter.hpp"
#include "packer/util/Bitmap.hpp"
PACKER_BEGIN

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