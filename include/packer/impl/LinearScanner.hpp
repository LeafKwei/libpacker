#ifndef PACKER_LINEARSCANNER_HPP
#define PACKER_LINEARSCANNER_HPP

#include "packer/packer.hpp"
#include "packer/data.hpp"
#include "packer/core/VScanner.hpp"
PACKER_BEGIN

class LinearScanner : public VScanner{
public:
    LinearScanner();
    virtual ~LinearScanner();
    virtual bool scan(const VImage &img, Rect &result) const;

private:

};

PACKER_END
#endif