#include <stdexcept>
#include "packer/util/util.hpp"
#include "packer/impl/SimpleLayouter.hpp"
using std::logic_error;
PACKER_BEGIN

SimpleLayouter::SimpleLayouter() : SimpleLayouter(16, 40, 30)  //640x480
{ }

SimpleLayouter::SimpleLayouter(int scale, int width, int height){
    if(scale <= 0) throw logic_error("Scale must be a positive number.");
    if(width <= 0 || height <= 0) throw logic_error("Width or height must be a positive number.");
    m_scale = scale;
    m_width = width;
    m_height = height;
    m_note.resize(m_width * m_height);
}

void SimpleLayouter::laydown(int width, int height, Rect &result){
    if(width <= 0 || height <= 0) throw logic_error("Width or height must be a positive number.");

    Rect range;
    confirmRange(width, height, range);
    if(range.width <= 0) throw logic_error("Image width is too large.");
    if(range.height <= 0 ) expandHeight(-range.height + 1);
}

int SimpleLayouter::currentWidth() const{
    return m_width;
}

int SimpleLayouter::currentHeight() const{
    return m_height;
}

void SimpleLayouter::setAt(int x, int y){
    m_note.set(transDimension(x, y));
}

void SimpleLayouter::unsetAt(int x, int y){
    m_note.unset(transDimension(x, y));
}

bool SimpleLayouter::testAt(int x, int y){
    return m_note.test(transDimension(x, y));
}

void SimpleLayouter::rangedSetAt(const Rect &rect){
    if(isBadCoord(rect.x, rect.y, m_width, m_height)) throw logic_error("Invalid position.");
    for(int y = rect.y; y < rect.height; y++){
        int pos = transDimension(rect.x, y);
        if(pos + rect.width > m_note.size()) throw logic_error("Out of range.");
        m_note.setn(pos, rect.width);
    }
}

void SimpleLayouter::rangedUnsetAt(const Rect &rect){
     if(isBadCoord(rect.x, rect.y, m_width, m_height)) throw logic_error("Invalid position.");
     for(int y = rect.y; y < rect.height; y++){
        int pos = transDimension(rect.x, y);
        if(pos + rect.width > m_note.size()) throw logic_error("Out of range.");
        m_note.unsetn(pos, rect.width);
    }
}

bool SimpleLayouter::testAtOR(const Rect &rect){
    if(isBadCoord(rect.x, rect.y, m_width, m_height)) throw logic_error("Invalid position.");
    for(int y = rect.y; y < rect.height; y++){
        int pos = transDimension(rect.x, y);
        if(pos + rect.width > m_note.size()) throw logic_error("Out of range.");
        if(m_note.testOR(pos, rect.width)) return true;
    }

    return false;
}

void SimpleLayouter::expandHeight(int increment){
    if(increment <= 0) throw logic_error("Increment must be a positive number.");
    m_note.resize((m_height + increment) * m_width);
    m_height += increment;
 }

int SimpleLayouter::transDimension(int x, int y){
    if(isBadCoord(x, y, m_width, m_height)) throw logic_error("Invalid position.");
    return y * m_width + x;
}

Rect SimpleLayouter::confirmRange(int width, int height, Rect &range){
    range.width = m_width - width + 1;
    range.height = m_height - height + 1;
    return range;
}

PACKER_END