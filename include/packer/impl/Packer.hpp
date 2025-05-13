#ifndef PACKER_PACKER__HPP
#define PACKER_PACKER__HPP

#include <vector>
#include "packer/core/VPacker.hpp"
PACKER_BEGIN

class Packer : public VPacker{
public:
    void addImageReader(VImageReader *imgReader) override;
    void pack() override;
    void save(const VImageWriter &imgWriter, const VProfileWriter &prfWriter) override;
    ~Packer();

private:
    State m_state;
    std::vector<VImageReader*> m_readers;
    std::vector<Record> m_records;
};

PACKER_END
#endif