#ifndef PACKER_ALIAS_HPP
#define PACKER_ALIAS_HPP

#include "packer/packer.hpp"
PACKER_BEGIN

//================ Type Alias ================
class VImage;
class VImageReader;
class VProfileReader;

using VImagePtr = std::shared_ptr<VImage>;
using VImageReaderPtr = std::shared_ptr<VImageReader>;
using VProfileReaderPtr = std::shared_ptr<VProfileReader>;

PACKER_END
#endif