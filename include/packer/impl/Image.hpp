#ifndef PACKER_IMAGE_HPP
#define PACKER_IMAGE_HPP

#include "packer/packer.hpp"
#include "packer/core/VImage.hpp"
PACKER_BEGIN

/**
 * Image是对VImage的一种实现，主要作用是创建一个指定宽高的空白图片，也就相当于提前分配一片RGBA结构体组成的内存，
 * 再由ImageReader等向其中填充像素数据
 */
class Image : public VImage{
public:
    Image(int width, int height);
    ~Image();
    int width() const noexcept override;
    int height() const noexcept override;
    ERGBA access(int x, int y) const noexcept override;
    ERGBAPtr accessAll() noexcept override;
    estruct place(int x, int y, const RGBA &rgb) noexcept override;
    estruct placeRect(int x, int y, const VImage &src, const Rect &rect) noexcept override;

private:
    int m_width;
    int m_height;
    RGBA *m_data;

    estruct createBuffer(int width, int height) noexcept;
};

PACKER_END
#endif