#ifndef PACKER_DEFAULTPROFILEREADER_HPP
#define PACKER_DEFAULTPROFILEREADER_HPP

#include <cstdio>
#include "packer/core/VProfileReader.hpp"
#include "packer/raii/RCharBuffer.hpp"
#include "packer/raii/RFilePtr.hpp"
PACKER_BEGIN

class DefaultProfileReader : public VProfileReader{
public:
    DefaultProfileReader(const std::string &path);
    void initialize() override;
    bool read(Profile &profile) override;
    void finalize() override;

private:
    RFilePtr m_file;
    RCharBuffer m_buffer;
    std::string m_fileName;
};

PACKER_END
#endif