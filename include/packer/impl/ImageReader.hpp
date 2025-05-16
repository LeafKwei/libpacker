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
    VImage* read() override;

protected:
    virtual void initialize(int &width, int &height) =0;              //进行像素拷贝前的初始化，例如打开图片
    virtual void readAllRGB(RGBA *buffer) =0;                          //将原图片中的所有像素值保存RGBA结构体中               
    virtual void finalize() =0;                                                     //完成像素拷贝后的清理操作，例如关闭图片
};

PACKER_END
#endif