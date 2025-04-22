#include "packer/impl/LinearScanner.hpp"

PACKER_BEGIN

LinearScanner::LinearScanner(){

}

LinearScanner::~LinearScanner(){

}

Rect LinearScanner::scan(const VImage &img) const{
    Rect result;

    /* 从上到下找到首个非透明像素的坐标 */
    int x1, y1;
    for(int y = 0; y < img.height(); y++){
        for(int x = 0; x < img.width(); x++){
            if(img.access(x, y).a != 0){
                x1 = x;
                y1 = y;
            }
        }
    }

    /* 从下到上找到首个非透明像素的坐标 */
    int x2, y2;
    for(int y = img.height() - 1; y >= 0; y--){
        for(int x = 0; x < img.width(); x++){
            if(img.access(x, y).a != 0){
                x2 = x;
                y2 = y;
            }
        }
    }

    /* 从左到右找到首个非透明像素的坐标 */
    int x3, y3;
    for(int x = 0; x < img.width(); x++){
        for(int y = 0; y < img.height(); y++){
            if(img.access(x, y).a != 0){
                x3 = x;
                y3 = y;
            }
        }
    }

    /* 从右到左找到首个非透明像素的坐标 */
    int x4, y4;
    for(int x = img.width() - 1; x >= 0; x--){
        for(int y = 0; y < img.height(); y++){
            if(img.access(x, y).a != 0){
                x4 = x;
                y4 = y;
            }
        }
    }

    /* 将得到的四个坐标综合计算出一个左上角和右上角坐标，这两个坐标划出了一个矩形范围，所有的可见像素都被包含在其中 */
    result.x1 = x3;
    result.y1 = y1;
    result.x2 = x4;
    result.y2 = y2;

    return result;
}

PACKER_END