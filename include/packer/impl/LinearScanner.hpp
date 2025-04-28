#ifndef PACKER_LINEARSCANNER_HPP
#define PACKER_LINEARSCANNER_HPP

#include <map>
#include "packer/packer.hpp"
#include "packer/data.hpp"
#include "packer/core/VScanner.hpp"

PACKER_BEGIN

class LinearScanner : public VScanner{
public:
    LinearScanner();
    ~LinearScanner() override;
    bool scan(const VImage &img, Rect &result) override;
};

PACKER_END
#endif