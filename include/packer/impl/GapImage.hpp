#ifndef PACKER_GAPIMAGE_HPP
#define PACKER_GAPIMAGE_HPP

#include "packer/packer.hpp"
#include "packer/core/VImage.hpp"
PACKER_BEGIN

class GapImage : public VImage{
public:
    GapImage();
    virtual ~GapImage();

protected:
    

private:
    int m_width;
    int m_height;
    RGBA *m_data;
};

PACKER_END
#endif