#ifndef PACKER_DEFAULTPROFILEWRITER_HPP
#define PACKER_DEFAULTPROFILEWRITER_HPP

#include <cstdio>
#include "packer/core/VProfileWriter.hpp"
#include "packer/raii/CharBuffer.hpp"
#include "packer/raii/FilePtr.hpp"
PACKER_BEGIN

class DefaultProfileWriter : public VProfileWriter{
public:
    DefaultProfileWriter(const std::string &path) ;
    void initialize() override;
    void write(const Profile &profile) override;
    void finalize() override;

private:
    FilePtr m_file;
    CharBuffer m_buffer;
    std::string m_fileName;
};

PACKER_END
#endif