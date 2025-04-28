#ifndef PACKER_VPROFILEREADER_HPP
#define PACKER_VPROFILEREADER_HPP

#include "packer/data.hpp"
PACKER_BEGIN

class VProfileReader{
public:
    virtual void initialize() =0;
    virtual bool read(Profile &profile) =0;
    virtual void finalize() =0;
    virtual ~VProfileReader();
};


PACKER_END
#endif