#ifndef PACKER_VLAYOUT_HPP
#define PACKER_VLAYOUT_HPP

#include "packer/packer.hpp"
#include "packer/data.hpp"
PACKER_BEGIN

class VLayout{
public:
    virtual int finalWidth() const =0;
    virtual int finalHeight() const =0;
    virtual Cell cellOf(int id) const =0;
};

PACKER_END
#endif