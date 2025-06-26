#ifndef PACKER_IMAGEWRITER_HPP
#define PACKER_IMAGEWRITER_HPP

#include "packer/core/VImageWriter.hpp"
PACKER_BEGIN

/**
 * ImageWriter实现了write函数，相比于ImageReader，它的实现要简单许多，它只是按序调用initialize，
 * writeRGB和finalize
 */
class ImageWriter : public VImageWriter{
public:
    void write(VImage &img) override;

protected:
    virtual void  openImage(ImageSize size) =0;                                                  //写入图片前的初始化，例如创建图片文件
    virtual inline void  writeRGB(int x, int y, const RGBA &rgba) noexcept =0;    //将RGB结构体写入到图片的指定位置
    virtual void  closeImage() =0;                                                                         //写入图片后的清理操作，例如关闭图片
};

PACKER_END
#endif