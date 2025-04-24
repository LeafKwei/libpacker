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
    ~LinearScanner();
    bool scan(int id, const VImage &img) override;
    Rect rangeOf(int id) const override;

private:
    std::map<int, Rect> m_ranges;
};

PACKER_END
#endif