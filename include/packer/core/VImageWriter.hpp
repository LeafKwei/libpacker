#ifndef PACKER_VIMAGEWRITER_HPP
#define PACKER_VIMAGEWRITER_HPP

#include "packer/core/VImage.hpp"
#include "packer/packer.hpp"
#include "packer/data/data.hpp"
PACKER_BEGIN

/**
 * VImageWriter将图片的写入操作与具体的写入方式隔离，
 * 同样的，它也不关注图片数据会被写入何处，只是向上提
 * 供了一个图片数据写入接口。每一个VImageWriter一个只
 * 负责一个png图片的写入
 * 
 * 实现者需要确保，当VImageWriter对象创建时，就已经初始
 * 化好了一切，并且可以立即执行write操作
 */
class VImageWriter {
public:
    virtual void write(VImage &img) =0;
    virtual ~VImageWriter();
};

PACKER_END
#endif