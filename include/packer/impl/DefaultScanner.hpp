#ifndef PACKER_DEFAULTSCANNER_HPP
#define PACKER_DEFAULTSCANNER_HPP

#include <map>
#include "packer/packer.hpp"
#include "packer/core/VScanner.hpp"

PACKER_BEGIN

class DefaultScanner : public VScanner{
public:
    DefaultScanner();
    ~DefaultScanner() override;
    void scan(const VImage &img, Rect &result) override;
};

PACKER_END
#endif