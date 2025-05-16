#ifndef PACKER_IMAGEWRITER_HPP
#define PACKER_IMAGEWRITER_HPP

#include "packer/core/VImageWriter.hpp"
PACKER_BEGIN

/**
 * ImageWriter实现了write函数，相比于ImageReader，它的实现要简单许多，它只是按序调用initialize，
 * writeAllRGB和finalize
 */
class ImageWriter : public VImageWriter{
public:
    void write(VImage &img) override;

protected:
    virtual void  initialize(int width, int height) =0;                      //写入图片前的初始化，例如创建图片文件
    virtual void  writeAllRGB(const RGBA *buffer) =0;                 //将所有的RGB结构体写入到图片中
    virtual void finalize() =0;                                                        //写入图片后的清理操作，例如关闭图片
};

PACKER_END
#endif