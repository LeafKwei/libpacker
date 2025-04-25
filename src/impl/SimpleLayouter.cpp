#include <stdexcept>
#include "packer/util/util.hpp"
#include "packer/impl/SimpleLayouter.hpp"
using std::logic_error;
PACKER_BEGIN

SimpleLayouter::SimpleLayouter() : SimpleLayouter(16, 40, 30)
{ }

SimpleLayouter::SimpleLayouter(int scale, int width, int height){
    if(scale <= 0) throw logic_error("Size must be a positive number.");
    if(width <= 0 || height <= 0) throw logic_error("Width or height must be a positive number.");
    m_scale = scale;
    m_width = width;
    m_height = height;
    m_note.resize(m_width * m_height);
}

void SimpleLayouter::laydown(int id, int width, int height){

}

int SimpleLayouter::currentWidth() const{
    return m_width;
}

int SimpleLayouter::currentHeight() const{
    return m_height;
}

Rect SimpleLayouter::rangeOf(int id) const{
    auto pos = m_ranges.find(id);
    if(pos == m_ranges.end()) throw std::logic_error("Invalid ID.");
    return pos -> second;
}

void SimpleLayouter::setAt(int x, int y){
    m_note.set(transDimen(x, y));
}

void SimpleLayouter::unsetAt(int x, int y){
    m_note.unset(transDimen(x, y));
}

bool SimpleLayouter::testAt(int x, int y){
    return m_note.test(transDimen(x, y));
}

void SimpleLayouter::rangedSetAt(const Rect &rect){
    for(int y = 0; y < rect.height; y++){
        for(int x = 0; x < rect.width; x++){
            m_note.set(transDimen(x, y));
        }
    }
}

void SimpleLayouter::rangedUnsetAt(const Rect &rect){
     for(int y = 0; y < rect.height; y++){
        for(int x = 0; x < rect.width; x++){
            m_note.unset(transDimen(x, y));
        }
    }
}

void SimpleLayouter::expandHeight(int increment){
    if(increment <= 0) throw logic_error("Increment must be a positive number.");
    m_note.resize((m_height + increment) * m_width);
    m_height += increment;
 }

int SimpleLayouter::transDimen(int x, int y){
    if(isBadCoord(x, y, m_width, m_height)) throw logic_error("Invalid position.");
    return y * m_width + x;
}   

PACKER_END