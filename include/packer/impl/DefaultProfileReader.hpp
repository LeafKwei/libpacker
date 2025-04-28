#ifndef PACKER_DEFAULTPROFILEREADER_HPP
#define PACKER_DEFAULTPROFILEREADER_HPP

#include <cstdio>
#include "packer/core/VProfileReader.hpp"
PACKER_BEGIN

class DefaultProfileReader : public VProfileReader{
public:
    DefaultProfileReader(const std::string &path);
    void initialize() override;
    bool read(Profile &profile) override;
    void finalize() override;

private:
    std::string m_fileName;
};

PACKER_END
#endif