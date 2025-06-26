#include <stdexcept>
#include "packer/impl/Image.hpp"
#include "packer/impl/ImageReader.hpp"

using std::exception;
using std::logic_error;
using std::runtime_error;
using std::string;
PACKER_BEGIN

VImagePtr ImageReader::read(){
    ImageSize size =  openImage();
    int width = toWidth(size);
    int height = toHeight(size);

    if(width <=0 || height <= 0) throw logic_error("Size must be a positive number.");

    VImagePtr imgptr(new Image(width, height));
    if(imgptr == nullptr) throw runtime_error("Out of memery.");

    auto data = imgptr -> accessAll();
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            readRGB(x, y, data[y * width + x]);
        }
    }

    closeImage();
    return imgptr;
}

PACKER_END