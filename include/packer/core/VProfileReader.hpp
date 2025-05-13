#ifndef PACKER_VPROFILEREADER_HPP
#define PACKER_VPROFILEREADER_HPP

#include "packer/data/data.hpp"
PACKER_BEGIN

class VProfileReader{
public:
    virtual Indicator read(Profile &profile) =0;
    virtual ~VProfileReader();
};


PACKER_END
#endif