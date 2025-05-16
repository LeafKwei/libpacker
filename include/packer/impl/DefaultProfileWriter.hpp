#ifndef PACKER_DEFAULTPROFILEWRITER_HPP
#define PACKER_DEFAULTPROFILEWRITER_HPP

#include <cstdio>
#include "packer/core/VProfileWriter.hpp"
#include "packer/raii/CharBuffer.hpp"
#include "packer/raii/FilePtr.hpp"
PACKER_BEGIN

/* 基于C标准库IO函数实现的'.prf'文件的写入功能 */
class DefaultProfileWriter : public VProfileWriter{
public:
    DefaultProfileWriter(const std::string &path) ;
    void write(const Profile &profile) override;
    ~DefaultProfileWriter();

private:
    FilePtr m_file;
    CharBuffer m_buffer;
    std::string m_fileName;
};

PACKER_END
#endif