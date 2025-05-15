#ifndef PACKER_PACKER__HPP
#define PACKER_PACKER__HPP

#include <vector>
#include "packer/core/VPacker.hpp"
PACKER_BEGIN

class Packer : public VPacker{
public:
    Packer(int scale=16, int scaledWidth=40);
    void addImageReader(VImageReader *imgReader) override;
    void pack() override;
    void save(VImageWriter &imgWriter, VProfileWriter &prfWriter) override;
    ~Packer();

private:
    State m_state;
    int m_scale;
    int m_scaledWidth;
    int m_packedWidth;
    int m_packedHeight;
    VImage *m_image;
    std::vector<VImageReader*> m_readers;
    std::vector<Record> m_records;

    void readImage();
    void scanImage();
    void layImage();
    void packImage();
};

PACKER_END
#endif