#ifndef PACKER_VUNPACKER_HPP
#define PACKER_VUNPACKER_HPP

#include <string>
#include <vector>
#include "packer/core/VImageReader.hpp"
#include "packer/core/VImageWriter.hpp"
#include "packer/core/VProfileReader.hpp"
PACKER_BEGIN

class VUnpacker{
public:
    virtual void unpack() =0;
    virtual VImage* getImageById(const std::string &id) =0;
    virtual std::vector<std::string> idList() =0;
    virtual ~VUnpacker();
};

PACKER_END
#endif