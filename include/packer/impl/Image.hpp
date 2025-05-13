#ifndef PACKER_IMAGE_HPP
#define PACKER_IMAGE_HPP

#include "packer/packer.hpp"
#include "packer/core/VImage.hpp"
PACKER_BEGIN

class Image : public VImage{
public:
    Image(int width, int height);
    ~Image();
    int width() const override;
    int height() const override;
    RGBA access(int x, int y) const override;
    void place(int x, int y, const RGBA &rgb) override;;
    void placeRect(int x, int y, const VImage &src, const Rect &rect) override;
    RGBA* accessAll() override;

private:
    int m_width;
    int m_height;
    RGBA *m_data;

    void createBuffer(int width, int height);
};

PACKER_END
#endif