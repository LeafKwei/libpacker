#include <stdexcept>
#include "packer/util/util.hpp"
#include "packer/impl/ScaledLayouter.hpp"
using std::logic_error;
PACKER_BEGIN

ScaledLayouter::ScaledLayouter(int scale, int layouterWidth, int layouterHeight){
    if(scale <= 0) throw logic_error("Scale must be a positive number.");
    if(layouterWidth <= 0 || layouterHeight <= 0) throw logic_error("Width or height must be a positive number.");
    
    m_scale = scale;
    m_layouterWidth = layouterWidth;
    m_layouterHeight = layouterHeight;
    m_note.resize(m_layouterWidth * m_layouterHeight);
}

Rect ScaledLayouter::laydown(int imageWidth, int imageHeight){
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
   
    Rect result;
    Rect testRange;
    result.x = -1;
    result.y = -1;

    while(true){
        Rect range = calcRange(scaledWidth, scaledHeight);
        if(!range) {
            expandHeight(scaledHeight - m_layouterHeight);
            continue;
        }

        for(int y = range.y; y < range.y + range.height; y++){
            for(int x = range.x; x < range.x + range.width; x++){
                testRange.x = x;
                testRange.y = y;
                testRange.width = scaledWidth;
                testRange.height = scaledHeight;


                printf("ranged test at :%d, %d\n", testRange.x, testRange.y);
                printf("test result: %d\n", rangedTestAt(testRange));
                if(rangedTestAt(testRange)){
                    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
                    printf("result.x:%d, result.y:%d\n", result.x, result.y);
                    for(int i = y; i < scaledHeight; i++){
                        printf("y%d==%d\t\t: ", i, i*m_scale);
                        for(int j = x; j < scaledWidth; j++){
                            printf("%d", m_note.test(transDimension(j, i)));
                        }
                        printf("\n");
                    }
                printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                }


                if(rangedTestAt(testRange)) continue;
                
                result.x = x;
                result.y = y;
                result.width = scaledWidth;
                result.height = scaledHeight;

                printf("------------------------------\n");
                    printf("result.x:%d, result.y:%d\n", result.x, result.y);
                    for(int i = 0; i < m_layouterHeight; i++){
                        printf("y%d==%d\t\t: ", i, i*m_scale);
                        for(int j = 0; j < m_layouterWidth; j++){
                            printf("%d", m_note.test(transDimension(j, i)));
                        }
                        printf("\n");
                    }
                printf("------------------------------\n");

                rangedSetAt(testRange);
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

bool ScaledLayouter::rangedTestAt(const Rect &rect){
    if(isBadCoord(rect.x, rect.y, m_layouterWidth, m_layouterHeight)) throw logic_error("Invalid position.");
    for(int y = rect.y; y < rect.height; y++){
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