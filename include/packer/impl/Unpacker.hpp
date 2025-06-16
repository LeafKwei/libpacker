#ifndef PACKER_UNPACKER_HPP
#define PACKER_UNPACKER_HPP

#include <vector>
#include <map>
#include <string>
#include "packer/core/VUnpakcer.hpp"
PACKER_BEGIN

/**
 * Unpacker根据构造函数传入的ImageReader和ProfileReader来读取待解包的图片以及子图片的位置信息，
 * 用户需要确保ImageReader和ProfileReader都是从堆内存中分配的，Unpacker会负责delete两者
 */
class Unpacker : public VUnpacker{
public:
    Unpacker(VImageReader *imgReader, VProfileReader *prfReader);
    void unpack() override;
    VImage* getImageById(const std::string &id) override;
    std::vector<std::string> idList() override;
    ~Unpacker();

private:
    State m_state;
    VImagePtr m_image;
    std::map<std::string, Profile> m_profiles;
    VImageReaderPtr m_imgReader;
    VProfileReaderPtr m_prfReader;

    void readProfiles();
    VImage *dumpImage(const Profile &prf);
};

PACKER_END
#endif