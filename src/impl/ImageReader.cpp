#include <stdexcept>
#include "packer/impl/Image.hpp"
#include "packer/impl/ImageReader.hpp"

using std::logic_error;
using std::runtime_error;
using std::string;
PACKER_BEGIN

VImage* ImageReader::read(){
    int width, height;
    initialize(width, height);
    if(width <=0 || height <= 0) throw logic_error("Size must be a positive number.");

    VImage *img = new Image(width, height);
    if(img == nullptr) throw runtime_error("Out of memery.");

    readAllRGB(img->accessAll());
    finalize();

    return img;
}

PACKER_END