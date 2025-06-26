#include <stdexcept>
#include <functional>
#include "packer/util/util.hpp"
#include "packer/impl/ScaledLayouter.hpp"
using std::logic_error;
using std::function;
PACKER_BEGIN

ScaledLayouter::ScaledLayouter(int scale, int layouterWidth, int layouterHeight){
    if(scale <= 0) throw logic_error("Scale must be a positive number.");
    if(layouterWidth <= 0 || layouterHeight <= 0) throw logic_error("Width or height must be a positive number.");
    
    m_scale = scale;
    m_layouterWidth = layouterWidth;
    m_layouterHeight = layouterHeight;
    m_note.resize(m_layouterWidth * m_layouterHeight);
}

Rect ScaledLayouter::laydown(ImageSize size){
    int imageWidth = toWidth(size);
    int imageHeight = toHeight(size);

    if(imageWidth <= 0 ||  imageHeight <= 0) throw logic_error("Width or height must be a positive number.");

    Rect result;
    int scaledWidth, scaledHeight;
    scaledWidth = imageWidth / m_scale;
    scaledHeight = imageHeight / m_scale;
    scaledWidth += imageWidth % m_scale == 0 ? 0 : 1;
    scaledHeight += imageHeight % m_scale == 0 ? 0 : 1;
    result = scaledLaydown(scaledWidth, scaledHeight);
    result.x = scale(result.x);
    result.y = scale(result.y);
    result.width = scale(result.width);
    result.height = scale(result.height);
    return result;
}

Rect ScaledLayouter::scaledLaydown(int scaledWidth, int scaledHeight){
    if(scaledWidth > m_layouterWidth) throw logic_error("Image width after scale must less than layouter width.");
   
    while(true){
        /**
         * 假设布局器的宽高为6x6，而scaledWidth和scaledHeight为3x3，那我们实际需要遍历的范围就只有4x4，因为超出4x4
         * 范围外的坐标的加上scaledWidth和scaledHeight已经超出了布局器的范围，而calcRange正是用于计算我们需要遍历的
         * 范围
         */
        Rect range = calcRange(scaledWidth, scaledHeight);
        if(!range) {
            expandHeight(scaledHeight - m_layouterHeight);
            continue;
        }

        Rect result;

        /**
         * 遍历矩形范围内的每个点，并根据点的坐标和图片宽高生成一个矩形范围，然后检查矩形是否已被占用(即其中是否有bit为1)，
         * 当找到一个未被占用的矩形时，将矩形中的所有bit置1，然后返回矩形作为结果
         */ 
        for(int y = range.y; y < range.y + range.height; y++){
            for(int x = range.x; x < range.x + range.width; x++){
                result.x = x;
                result.y = y;
                result.width = scaledWidth;
                result.height = scaledHeight;

                if(rangedTestAt(result)) continue;
                rangedSetAt(result);
                return result;
            }
        }

        expandHeight(scaledHeight);
    }
}

Rect ScaledLayouter::calcRange(int scaledWidth, int scaledHeight){
    Rect range;
    range.x = -1;
    range.y = -1;

    if(m_layouterHeight < scaledHeight) return range;
    range.x = 0;
    range.y = 0;
    range.width = m_layouterWidth - scaledWidth + 1;
    range.height = m_layouterHeight - scaledHeight + 1;
    return range;
}

/**
 * 由于缩放和扩展高度的缘故，布局器的宽度和高度可能比实际使用到的要更大，因此packedWidth和packedHeight函数在返回宽度
 * 和高度前还需要减去那些多余的量。计算这些多余的量的方法是从下到上(计算高度)或从右到左(计算宽度)依次test每行/列，如果该行/列
 * 不存在为1的bit，那么就说明该行/列未实际使用，需要减去
 */
int ScaledLayouter::packedWidth() const{
    int width = m_layouterWidth;
    for(int x = m_layouterWidth - 1; x >= 0; x--){
        for(int y = 0; y < m_layouterHeight; y++){
            if(m_note.test(transDimension(x, y))){
                return scale(width);
            }
        }
        --width;
    }

    return scale(width);
}

int ScaledLayouter::packedHeight() const{
    int height = m_layouterHeight;
    for(int y = m_layouterHeight - 1; y >= 0; y--){
        if(m_note.testOR(transDimension(0, y), m_layouterWidth)){
            break;
        }
        --height;
    }

    return scale(height);
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

void ScaledLayouter::rangedWork(const Rect &rect, function<void(int,int)> func){
    if(isBadCoord(rect.x, rect.y, m_layouterWidth, m_layouterHeight)) throw logic_error("Invalid position.");
    for(int y = rect.y; y < rect.y + rect.height; y++){
        int pos = transDimension(rect.x, y);
        if(pos + rect.width > m_note.size()) throw logic_error("Out of range.");
        func(pos, rect.width);
    }
}

void ScaledLayouter::rangedSetAt(const Rect &rect){
    rangedWork(rect, [this](int pos, int width) -> void{
        m_note.setn(pos, width);
    });
}

void ScaledLayouter::rangedUnsetAt(const Rect &rect){
     rangedWork(rect, [this](int pos, int width) -> void{
        m_note.unsetn(pos, width);
     });
}

bool ScaledLayouter::rangedTestAt(const Rect &rect){
    if(isBadCoord(rect.x, rect.y, m_layouterWidth, m_layouterHeight)) throw logic_error("Invalid position.");
    for(int y = rect.y; y < rect.y + rect.height; y++){
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

int ScaledLayouter::transDimension(int x, int y) const{
    if(isBadCoord(x, y, m_layouterWidth, m_layouterHeight)) throw logic_error("Invalid position.");
    return y * m_layouterWidth + x;
}

PACKER_END