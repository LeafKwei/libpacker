#ifndef PACKER_VPROFILEREADER_HPP
#define PACKER_VPROFILEREADER_HPP

#include "packer/data/data.hpp"
PACKER_BEGIN

/**
 * VProfileReader同样是提供与具体方式无关的Profile读取功能，Profile是每一个被合并的png图片的记录信息，
 * 包括这些图片的宽度，高度，在最终合并得到的图片中的位置等。read函数在读取一个Profile后会返回一个indicator
 * 枚举用于指示此次读取的状态。一个VProfileReader对象应该只管理一个'.prf'文件的读取
 * 
 * 实现者需要确保，当VProfileReader对象创建时就已经初始化好了一切，并且可以直接进行read操作
 */
class VProfileReader{
public:
    virtual Indicator read(Profile &profile) =0;
    virtual ~VProfileReader();
};


PACKER_END
#endif