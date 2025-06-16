#include <cstdlib>
#include <stdexcept>
#include "iostream"
#include "packer/impl/Image.hpp"
#include "packer/util/util.hpp"
using std::logic_error;
using std::runtime_error;
PACKER_BEGIN

Image::Image(int width, int height) : m_width(0), m_height(0), m_data(width * height){
    m_width = width;
    m_height = height;
}

Image::~Image(){
    
}

int Image::width() const noexcept{
    return m_width;
}

int Image::height() const noexcept{
    return m_height;
}

RGBA Image::access(int x, int y) const{
    if(isBadCoord(x, y, m_width, m_height)) throw logic_error("Invalid position.");
    const RGBA *data = m_data.cuse();
    return data[y * m_width + x];
}

void Image::place(int x, int y, const RGBA &rgb){
    if(isBadCoord(x, y, m_width, m_height)) throw logic_error("Invalid position.");
    RGBA *data = m_data.use();
    data[y * m_width + x] = rgb;
}

void Image::placeRect(int x, int y, const VImage &src, const Rect &rect){
    if(isBadCoord(x, y, m_width, m_height)) throw logic_error("Invalid position.");
    if(x + rect.width > m_width || y + rect.height > m_height) throw logic_error("Out of range.");
    
    RGBA *data = m_data.use();

    for(int vy = 0; vy < rect.height; vy++){
        for(int vx = 0; vx < rect.width; vx++){
            int pos = ((y + vy) * m_width) + (x + vx);
            data[pos] = src.access(rect.x + vx, rect.y + vy);
        }
    }
}

RGBA* Image::accessAll(){
    return m_data.use();
}

PACKER_END