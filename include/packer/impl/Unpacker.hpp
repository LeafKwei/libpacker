#ifndef PACKER_UNPACKER_HPP
#define PACKER_UNPACKER_HPP

#include <vector>
#include <map>
#include <string>
#include "packer/core/VUnpakcer.hpp"
PACKER_BEGIN

class Unpacker : public VUnpacker{
public:
    Unpacker(VImageReader *imgReader, VProfileReader *prfReader);
    void unpack() override;
    VImage* getImageById(const std::string &id) override;
    std::vector<std::string> idList() override;
    ~Unpacker();

private:
    State m_state;
    VImage *m_image;
    std::map<std::string, Profile> m_profiles;
    VImageReader *m_imgReader;
    VProfileReader *m_prfReader;

    void readProfiles();
    VImage *dumpImage(const Profile &prf);
};

PACKER_END
#endif