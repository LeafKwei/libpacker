#ifndef PACKER_VIMAGEREADER_HPP
#define PACKER_VIMAGEREADER_HPP

#include <string>
#include "packer/core/VImage.hpp"
#include "packer/packer.hpp"
#include "packer/data/data.hpp"
PACKER_BEGIN

/**
 * VImageReader将VImage对象的读取操作与具体的读取方式隔离，
 * 它并不关注以何种方式(例如文件或网络)获取图片数据，仅仅是向
 * 上提供了一个VImage的读取接口。每一个VImageReader应该只
 * 负责一个png图片的读取。
 * 
 * 实现者需要确保，当VImageReader对象创建时，就已经初始化
 * 好了一切，并且可以立即进行read和id操作
 */
class VImageReader{
public:
    virtual VImage* read() =0;  //读取一个VImage对象
    virtual std::string id() =0;    //获取该VImage对象的id
    virtual ~VImageReader();
};

PACKER_END
#endif