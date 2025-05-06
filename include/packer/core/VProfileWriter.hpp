#ifndef PACKER_VPROFILEWRITER_HPP
#define PACKER_VPROFILEWRITER_HPP

#include "packer/data/data.hpp"
PACKER_BEGIN

class VProfileWriter{
public:
    virtual void initialize() =0;
    virtual void write(const Profile &profile) =0;
    virtual void finalize() =0;
    virtual ~VProfileWriter();
};


PACKER_END
#endif