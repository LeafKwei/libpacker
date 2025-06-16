#ifndef PACKER_PACKER__HPP
#define PACKER_PACKER__HPP

#include <vector>
#include "packer/core/VPacker.hpp"
#include "packer/raii/alias.hpp"
PACKER_BEGIN

/**
 * Packer使用前面提到的各种工具来完成打包功能，当调用pack时，Packer首先调用readImage函数从每个ImageReader中
 * 读取VImage及其id，然后调用scanImage扫描每个VImage的非透明像素范围，接着调用layImage计算每个VImage在最后
 * 合并的图片中的位置，最后调用packImage按照前面的步骤得出的信息合成所有VImage
 * 
 * save函数传递的ImageWriter和ProfileWriter分别用于保存合并后的图片以及其中每个子图片的位置信息
 */ 
class Packer : public VPacker{
public:
    Packer(int scale=16, int scaledWidth=40);   //scale和scaledWidth的作用参见ScaledLayouter
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
    VImagePtr m_image;
    std::vector<VImageReaderPtr> m_readers;
    std::vector<Record> m_records;

    void readImage();
    void scanImage();
    void layImage();
    void packImage();
};

PACKER_END
#endif