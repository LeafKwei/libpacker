#ifndef PACKER_VPACKER_HPP
#define PACKER_VPACKER_HPP

#include "packer/core/VImageReader.hpp"
#include "packer/core/VImageWriter.hpp"
#include "packer/core/VProfileWriter.hpp"
PACKER_BEGIN

/**
 * VPacker提供打包器的功能，用户首先通过addImageReader向其中添加需要打包的png图片对应的reader，
 * 然后调用pack进行打包，最后调用save即可保存打包后的图片。用户应该确保添加的reader是从堆内存中
 * 分配的，VPacker会在打包完成后负责delete这些reader
 */
class VPacker{
public:
    virtual void addImageReader(VImageReader *imgReader) =0;
    virtual void pack() =0;
    virtual void save(VImageWriter &imgWriter, VProfileWriter &prfWriter) =0;
    virtual ~VPacker();
};

PACKER_END
#endif