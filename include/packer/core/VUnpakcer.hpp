#ifndef PACKER_VUNPACKER_HPP
#define PACKER_VUNPACKER_HPP

#include <string>
#include <vector>
#include "packer/core/VImageReader.hpp"
#include "packer/core/VImageWriter.hpp"
#include "packer/core/VProfileReader.hpp"
PACKER_BEGIN

/**
 * VUnpacker提供解包器的功能，用户可以通过构造函数等途径(参照impl/Unpacker.hpp)向其中添加用作数据源的
 * VImageReader和VProfileReader对象，然后调用unpack执行解包，完成后，通过getImageById获取id对应的
 * 图片数据，也可以idList获取全部的id然后遍历所有图片
 * 
 * getImageById将从堆内存中分配VImage对象，用户应该确保自己管理和释放该对象
 */
class VUnpacker{
public:
    virtual void unpack() =0;
    virtual VImagePtr getImageById(const std::string &id) =0;
    virtual std::vector<std::string> idList() =0;
    virtual ~VUnpacker();
};

PACKER_END
#endif