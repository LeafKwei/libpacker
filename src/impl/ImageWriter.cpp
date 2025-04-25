#include "packer/impl/ImageWriter.hpp"
PACKER_BEGIN

void ImageWriter::write(VImage &img){
    initialize(img.width(), img.height());
    writeRGB(img.accessAll());
    finalize();
}  

PACKER_END