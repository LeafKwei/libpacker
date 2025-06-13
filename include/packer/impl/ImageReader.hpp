#ifndef PACKER_IMAGEREADER_HPP
#define PACKER_IMAGEREADER_HPP

#include "packer/core/VImageReader.hpp"
PACKER_BEGIN

/**
 * ImageReader实现了read函数，将read函数拆分为了三个接口留给后续派生类实现，其中，initialize要求
 * 派生类执行像素数据拷贝前的初始化，例如打开具体的图片文件，然后将图片的宽高通过width和height两个
 * 引用传递给ImageReader，随后ImageReader会根据宽高创建一个Image对象，并将Image对象的RGBA内
 * 存块通过readAllRGB函数传递给派生类，由派生类负责将图片的像素数据填充到RGBA内存块中，最后，
 * ImageReader调用finalize函数执行派生类定义的清理工作
 */
class ImageReader : public VImageReader{
public:
    EVImagePtr read() noexcept override;

protected:
    virtual estruct beforeRead(int &width, int &height) noexcept;
    inline virtual estruct readRGB(int x, int y, RGBA &rgba) noexcept;
    virtual estruct afterRead() noexcept;
};

PACKER_END
#endif