#ifndef PACKER_VIMAGEREADER_HPP
#define PACKER_VIMAGEREADER_HPP

#include "packer/core/VImage.hpp"
#include "packer/packer.hpp"
#include "packer/data.hpp"
PACKER_BEGIN

class VImageReader{
public:
    virtual VImage* read() =0;
    virtual ~VImageReader();
};

PACKER_END
#endif