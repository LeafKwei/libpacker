#ifndef PACKER_VPACKER_HPP
#define PACKER_VPACKER_HPP

#include "packer/core/VImageReader.hpp"
#include "packer/core/VImageWriter.hpp"
#include "packer/core/VProfileWriter.hpp"
PACKER_BEGIN

class VPacker{
public:
    virtual void addImageReader(VImageReader *imgReader) =0;
    virtual void pack() =0;
    virtual void save(VImageWriter &imgWriter, VProfileWriter &prfWriter) =0;
    virtual ~VPacker();
};

PACKER_END
#endif