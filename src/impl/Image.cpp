#include <cstdlib>
#include <stdexcept>
#include "iostream"
#include "packer/impl/Image.hpp"
#include "packer/util/util.hpp"
using std::logic_error;
using std::runtime_error;
PACKER_BEGIN

Image::Image(int width, int height) : m_width(0), m_height(0), m_data(NULL){
    auto err = createBuffer(width, height);
    if(err){
        throw runtime_error(err);
    }

    m_width = width;
    m_height = height;
}

Image::~Image(){
    free(m_data);
}

int Image::width() const noexcept{
    return m_width;
}

int Image::height() const noexcept{
    return m_height;
}

ERGBA Image::access(int x, int y) const noexcept{
    if(isBadCoord(x, y, m_width, m_height)) return make_evalue(ErrCode::InvalidNumber, "Coords should be in range of image size.", RGBA());
    return make_evalue_ok(m_data[y * m_width + x]);
}

estruct Image::place(int x, int y, const RGBA &rgb) noexcept{
    if(isBadCoord(x, y, m_width, m_height)) return make_estruct(ErrCode::InvalidNumber, "Coords should be in range of image size.");
    m_data[y * m_width + x] = rgb;
    return make_estruct_ok();
}

estruct Image::placeRect(int x, int y, const VImage &src, const Rect &rect) noexcept{
    if(isBadCoord(x, y, m_width, m_height)) return make_estruct(ErrCode::InvalidNumber, "Coords should be in range of image size.");
    if(x + rect.width > m_width || y + rect.height > m_height) return make_estruct(ErrCode::OutOfBound, "Image given size is too large.");
    
    for(int vy = 0; vy < rect.height; vy++){
        for(int vx = 0; vx < rect.width; vx++){
            int pos = ((y + vy) * m_width) + (x + vx);
            auto [err, rgb] = src.access(rect.x + vx, rect.y + vy);  //经过上方的坐标检查后，此处应该不会发生错误，因此不考虑错误检查
            m_data[pos] = rgb;
        }
    }

    return make_estruct_ok();
}

ERGBAPtr Image::accessAll() noexcept{
    return make_evalue_ok(m_data);
}

estruct Image::createBuffer(int width, int height) noexcept{
    if(width < 0 || height < 0){
        return make_estruct(ErrCode::InvalidNumber, "Invalid size.");
    }

    m_data = (RGBA*) calloc(width * height, sizeof(RGBA));
    if(m_data == NULL){
        return make_estruct(ErrCode::OutOfMem, "No memory.");
    }

    return make_estruct_ok();
}

PACKER_END