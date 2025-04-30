#include <stdexcept>
#include "packer/util/util.hpp"
#include "packer/impl/ScaledLayouter.hpp"
using std::logic_error;
PACKER_BEGIN

ScaledLayouter::ScaledLayouter() : ScaledLayouter(16, 40, 30)  //640x480
{ }

ScaledLayouter::ScaledLayouter(int scale, int layouterWidth, int layouterHeight){
    if(scale <= 0) throw logic_error("Scale must be a positive number.");
    if(layouterWidth <= 0 || layouterHeight <= 0) throw logic_error("Width or height must be a positive number.");
    
    m_scale = scale;
    m_layouterWidth = layouterWidth;
    m_layouterHeight = layouterHeight;
    m_note.resize(m_layouterWidth * m_layouterHeight);
}

void ScaledLayouter::laydown(int imageWidth, int imageHeight, Rect &result){
    
}

int ScaledLayouter::packedImageWidth() const{
    return scale(m_layouterWidth);
}

int ScaledLayouter::packedImageHeight() const{
    return scale(m_layouterHeight);
}

inline int ScaledLayouter::scale(int value) const{
    return value  * m_scale;
}

void ScaledLayouter::setAt(int x, int y){
    m_note.set(transDimension(x, y));
}

void ScaledLayouter::unsetAt(int x, int y){
    m_note.unset(transDimension(x, y));
}

bool ScaledLayouter::testAt(int x, int y){
    return m_note.test(transDimension(x, y));
}

void ScaledLayouter::rangedSetAt(const Rect &rect){
    if(isBadCoord(rect.x, rect.y, m_layouterWidth, m_layouterHeight)) throw logic_error("Invalid position.");
    for(int y = rect.y; y < rect.height; y++){
        int pos = transDimension(rect.x, y);
        if(pos + rect.width > m_note.size()) throw logic_error("Out of range.");
        m_note.setn(pos, rect.width);
    }
}

void ScaledLayouter::rangedUnsetAt(const Rect &rect){
     if(isBadCoord(rect.x, rect.y, m_layouterWidth, m_layouterHeight)) throw logic_error("Invalid position.");
     for(int y = rect.y; y < rect.height; y++){
        int pos = transDimension(rect.x, y);
        if(pos + rect.width > m_note.size()) throw logic_error("Out of range.");
        m_note.unsetn(pos, rect.width);
    }
}

bool ScaledLayouter::testAtRect(const Rect &rect){
    if(isBadCoord(rect.x, rect.y, m_layouterWidth, m_layouterHeight)) throw logic_error("Invalid position.");
    for(int y = 0; y < rect.height; y++){
        int pos = transDimension(rect.x, y);
        if(pos + rect.width > m_note.size()) throw logic_error("Out of range.");
        if(m_note.testOR(pos, rect.width)) return true;
    }

    return false;
}

void ScaledLayouter::expandHeight(int increment){
    if(increment <= 0) throw logic_error("Increment must be a positive number.");
    m_note.resize((m_layouterHeight + increment) * m_layouterWidth);
    m_layouterHeight += increment;
 }

int ScaledLayouter::transDimension(int x, int y){
    if(isBadCoord(x, y, m_layouterWidth, m_layouterHeight)) throw logic_error("Invalid position.");
    return y * m_layouterWidth + x;
}

PACKER_END