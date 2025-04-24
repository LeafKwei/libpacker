#include <cstdlib>
#include "stdexcept"
#include "packer/impl/GapImage.hpp"
using std::logic_error;
using std::runtime_error;
PACKER_BEGIN

GapImage::GapImage() : m_width(0), m_height(0), m_data(NULL){

}

GapImage::GapImage(int width, int height) : m_width(0), m_height(0), m_data(NULL){
    createBuffer(width, height);
    m_width = width;
    m_height = height;
}

GapImage::~GapImage(){
    free(m_data);
}

void GapImage::readRawImage(){}
int GapImage::customedHeight() const { return 0; }
int GapImage::customedWidth() const { return 0; }
void GapImage::fillData(int x, int y, RGBA &rgb){}

int GapImage::width() const{
    return m_width;
}

int GapImage::height() const{
    return m_height;
}

RGBA GapImage::access(int x, int y) const{
    if(x < 0 || y < 0 || x >= m_width || y >= m_height) throw logic_error("Invalid postion.");
    return m_data[y * m_width + x];
}

void GapImage::place(int x, int y, const RGBA &rgb){
    if(x < 0 || y < 0 || x >= m_width || y >= m_height) throw logic_error("Invalid postion.");
    m_data[y * m_width + x] = rgb;
}

void GapImage::placeRect(int x, int y, const VImage &src, const Rect &rect){
    if(x < 0 || y < 0 || x >= m_width || y >= m_height) throw logic_error("Invalid postion.");
    if(x + rect.width > m_width || y + rect.height > m_height) throw logic_error("Out of range.");
    
    for(int vy = 0; vy < rect.height; vy++){
        for(int vx = 0; vx < rect.width; vx++){
            int pos = ((y + vy) * m_width) + (x + vx);
            m_data[pos] = src.access(rect.x + vx, rect.y + vy);
        }
    }
}

const RGBA* GapImage::accessAll(){
    return m_data;
}

void GapImage::custom(){
    readRawImage();
    int width = customedWidth(), height = customedHeight();
    createBuffer(width, height);
    m_width = width;
    m_height = height;

    m_data = (RGBA*) malloc(sizeof(RGBA) * width * height);
    if(m_data == NULL) throw runtime_error("Out of memery.");

    for(int y = 0; y < height; y++){
        for(int x = 0; x < height; x++){
            fillData(x, y, m_data[y * width + x]);
        }
    }
}

void GapImage::createBuffer(int width, int height){
    if(width < 0 || height < 0) throw logic_error("Invalid size.");
    m_data = (RGBA*) malloc(sizeof(RGBA) * width * height);
    if(m_data == NULL) throw std::runtime_error("Out of memery.");
}


PACKER_END