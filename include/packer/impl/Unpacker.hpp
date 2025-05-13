#ifndef PACKER_UNPACKER_HPP
#define PACKER_UNPACKER_HPP

#include <vector>
#include "packer/core/VUnpakcer.hpp"
PACKER_BEGIN

class Unpacker : public VUnpacker{
public:
    void setSource(VImageReader *imgReader, VProfileReader *prfReader) override;
    void unpack() override;
    VImage* getImageById(const std::string &id) override;
    std::vector<std::string> idList() override;
    ~Unpacker();

private:
    State m_state;
    std::vector<Record> m_records;
};

PACKER_END
#endif