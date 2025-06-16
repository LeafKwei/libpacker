#include "packer/impl/ImageWriter.hpp"
PACKER_BEGIN

void ImageWriter::write(VImage &img){
    initialize(img.width(), img.height());
    
    auto data = img.accessAll();
    auto width = img.width();
    auto height = img.height();

    for(int y = 0; y < img.height(); y++){
        for(int x = 0; x < img.width(); x++){
            writeRGB(x, y, data[y * width + x]);
        }
    }

    finalize();
}

PACKER_END