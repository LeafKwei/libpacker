#ifndef PACKER_VPROFILEWRITER_HPP
#define PACKER_VPROFILEWRITER_HPP

#include "packer/data/data.hpp"
PACKER_BEGIN

/**
 * VProfileWriter提供与具体方式无关的Profile写入功能。一个VProfileWriter对象应该只负责一个'.prf'文件的
 * 写入
 * 
 * 实现者需要确保，当VProfileWriter对象创建时，就完成了所有初始化，并且可以立即进行write操作
 */
class VProfileWriter{
public:
    virtual void write(const Profile &profile) =0;
    virtual ~VProfileWriter();
};


PACKER_END
#endif