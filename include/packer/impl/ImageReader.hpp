#ifndef PACKER_IMAGEREADER_HPP
#define PACKER_IMAGEREADER_HPP

#include "packer/core/VImageReader.hpp"
PACKER_BEGIN

class ImageReader : public VImageReader{
public:
    VImage* read() override;

protected:
    virtual void initialize(int &width, int &height) =0;              //进行像素拷贝前的初始化，例如打开图片
    virtual void readAllRGB(RGBA *buffer) =0;                          //将原图片中的所有像素值保存RGBA结构体中               
    virtual void finalize() =0;                                                     //完成像素拷贝后的清理操作，例如关闭图片
};

PACKER_END
#endif