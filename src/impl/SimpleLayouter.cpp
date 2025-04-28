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
    if(width <=0 || height <= 0) throw logic_error("Width or height must be a positive number.");
    if(width > m_width) throw logic_error("Image width is too large.");

    /* 计算缩放后的宽度和高度 */
    int scaledWidth = width / m_scale;
    int scaledHeight = height / m_scale;
    scaledWidth = scaledWidth > 0 ? scaledWidth : 1;
    scaledHeight = scaledHeight > 0 ? scaledHeight : 1;

    for(int y = 0; y < m_height;  y++){
        for(int x = 0; x < m_width; x++){
            /* 如果bit已占用，则跳过 */
            if(testAt(x, y)) continue;

            /* bit未占用时，检查当前坐标增加上图片宽高后是否越界 */
            if(x + scaledWidth > m_width) break;                                                       //x轴越界时则搜索下一行
            if(y + scaledHeight > m_height) expandHeight(width / m_scale + 1);     //y轴越界时则拓展高度

            /* 检查范围内的坐标是否是空置的 */
            
        }
    }
}

int SimpleLayouter::currentWidth() const{
    return m_width;
}

int SimpleLayouter::currentHeight() const{
    return m_height;
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