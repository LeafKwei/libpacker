#ifndef PACKER_DEFAULTPROFILEWRITER_HPP
#define PACKER_DEFAULTPROFILEWRITER_HPP

#include <cstdio>
#include "packer/core/VProfileWriter.hpp"
PACKER_BEGIN

class DefaultProfileWriter : public VProfileWriter{
public:
    DefaultProfileWriter(const std::string &path) ;
    void initialize() override;
    void write(const Profile &profile) override;
    void finalize() override;

private:
    std::string m_fileName;
};

PACKER_END
#endif