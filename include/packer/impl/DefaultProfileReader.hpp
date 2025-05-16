#ifndef PACKER_DEFAULTPROFILEREADER_HPP
#define PACKER_DEFAULTPROFILEREADER_HPP

#include <cstdio>
#include "packer/core/VProfileReader.hpp"
#include "packer/raii/CharBuffer.hpp"
#include "packer/raii/FilePtr.hpp"
PACKER_BEGIN

/* 基于C标准库IO函数实现的'.prf'文件的读取功能 */
class DefaultProfileReader : public VProfileReader{
public:
    DefaultProfileReader(const std::string &path);
    Indicator read(Profile &profile) override;
    ~DefaultProfileReader();

private:
    FilePtr m_file;
    CharBuffer m_buffer;
    std::string m_fileName;
};

PACKER_END
#endif