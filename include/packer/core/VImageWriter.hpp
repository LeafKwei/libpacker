#ifndef PACKER_VIMAGEWRITER_HPP
#define PACKER_VIMAGEWRITER_HPP

#include "packer/core/VImage.hpp"
#include "packer/packer.hpp"
#include "packer/data/data.hpp"
PACKER_BEGIN

class VImageWriter {
public:
    virtual void write(VImage &img) =0;
    virtual ~VImageWriter();
};

PACKER_END
#endif