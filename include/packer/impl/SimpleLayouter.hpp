#ifndef PACKER_SIMPLELAYOUTER_HPP
#define PACKER_SIMPLELAYOUTER_HPP

#include <map>
#include "packer/core/VLayouter.hpp"
#include "packer/util/Bitmap.hpp"
PACKER_BEGIN

class SimpleLayouter : public VLayouter{
public:
    SimpleLayouter();
    SimpleLayouter(int scale, int width, int height);
    void laydown(int width, int height, Rect &result) override;
    int currentWidth() const override;
    int currentHeight() const override;

private:
    int m_scale;
    int m_width;
    int m_height;
    Bitmap m_note;

    void setAt(int x, int y);
    void unsetAt(int x, int y);
    bool testAt(int x, int y);
    void rangedSetAt(const Rect &rect);
    void rangedUnsetAt(const Rect &rect);
    void expandHeight(int increment);
    inline int transDimen(int x, int y);
};

PACKER_END
#endif