#include <stdexcept>
#include "packer/impl/Image.hpp"
#include "packer/impl/ImageReader.hpp"

using std::logic_error;
using std::runtime_error;
using std::string;
PACKER_BEGIN

EVImagePtr ImageReader::read() noexcept{
    int width, height;

    auto err = beforeRead(width, height);
    if(err) return make_evalue(err.code, err.what, nullptr);
    if(width <= 0 || height <= 0) return make_evalue(ErrCode::InvalidNumber, "Image size must be a positive number.", nullptr);

    VImage *imgptr = new Image(width, height);
    if(imgptr == nullptr) return make_evalue(ErrCode::OutOfMem, "No memory.", nullptr);

    auto [err, rgbaptr] = imgptr -> accessAll();
    if(err) {
        delete imgptr;
        return make_evalue(err.code, err.what, nullptr);
    }

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            RGBA &rgba = rgbaptr[y * width + x];
            auto err = readRGB(x, y, rgba);
            if(err.code != ErrCode::OK){ 
                delete imgptr;
                return make_evalue(err.code, err.what, nullptr);
            }
        }
    }

    auto err = afterRead();
    if(err){
        delete imgptr;
        return make_evalue(err.code, err.what, nullptr);
    }

    return make_evalue_ok(imgptr);
}

PACKER_END