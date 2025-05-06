#ifndef PACKER_LINEARSCANNER_HPP
#define PACKER_LINEARSCANNER_HPP

#include <map>
#include "packer/packer.hpp"
#include "packer/core/VScanner.hpp"

PACKER_BEGIN

class DefaultScanner : public VScanner{
public:
    DefaultScanner();
    ~DefaultScanner() override;
    bool scan(const VImage &img, Rect &result) override;
};

PACKER_END
#endif