#include <cstdlib>
#include <stdexcept>
#include "iostream"
#include "packer/impl/Image.hpp"
#include "packer/util/util.hpp"
using std::logic_error;
using std::runtime_error;
PACKER_BEGIN

Image::Image(int width, int height) : m_width(0), m_height(0), m_data(NULL){
    createBuffer(width, height);
    m_width = width;
    m_height = height;
}

Image::~Image(){
    free(m_data);
}

int Image::width() const{
    return m_width;
}

int Image::height() const{
    return m_height;
}

RGBA Image::access(int x, int y) const{
    if(isBadCoord(x, y, m_width, m_height)) throw logic_error("Invalid position.");
    return m_data[y * m_width + x];
}

void Image::place(int x, int y, const RGBA &rgb){
    if(isBadCoord(x, y, m_width, m_height)) throw logic_error("Invalid position.");
    m_data[y * m_width + x] = rgb;
}

void Image::placeRect(int x, int y, const VImage &src, const Rect &rect){
    if(isBadCoord(x, y, m_width, m_height)) throw logic_error("Invalid position.");
    if(x + rect.width > m_width || y + rect.height > m_height) throw logic_error("Out of range.");
    
    for(int vy = 0; vy < rect.height; vy++){
        for(int vx = 0; vx < rect.width; vx++){
            int pos = ((y + vy) * m_width) + (x + vx);
            m_data[pos] = src.access(rect.x + vx, rect.y + vy);
        }
    }
}

RGBA* Image::accessAll(){
    return m_data;
}

void Image::createBuffer(int width, int height){
    if(width < 0 || height < 0) throw logic_error("Invalid size.");
    m_data = (RGBA*) malloc(sizeof(RGBA) * width * height);
    if(m_data == NULL) throw std::runtime_error("Out of memery.");
}

PACKER_END