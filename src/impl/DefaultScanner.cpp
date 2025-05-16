#include <stdexcept>
#include "packer/impl/DefaultScanner.hpp"
PACKER_BEGIN

DefaultScanner::DefaultScanner(){

}

DefaultScanner::~DefaultScanner(){

}

void DefaultScanner::scan(const VImage &img, Rect &result) {
    /* 从上到下找到首个非透明像素的坐标 */
    bool on = true;
    int x1 = -1, y1 = -1;
    for(int y = 0; (y < img.height() && on); y++){
        for(int x = 0; (x < img.width() && on); x++){
            if(img.access(x, y).a != 0){
                x1 = x;
                y1 = y;
                on = false;
            }
        }
    }

    /* 如果没有找到任何非透明像素，则说明此图片无有效内容 */
    if(on){
        result.width = 0;
        result.height = 0;
        return;
    }

    /* 从下到上找到首个非透明像素的坐标 */
    on = true;
    int x2, y2;
    for(int y = img.height() - 1; (y >= 0 && on); y--){
        for(int x = 0; (x < img.width() && on); x++){
            if(img.access(x, y).a != 0){
                x2 = x;
                y2 = y;
                on = false;
            }
        }
    }

    /* 从左到右找到首个非透明像素的坐标 */
    on = true;
    int x3, y3;
    for(int x = 0; (x < img.width() && on); x++){
        for(int y = 0; (y < img.height() && on); y++){
            if(img.access(x, y).a != 0){
                x3 = x;
                y3 = y;
                on = false;
            }
        }
    }

    /* 从右到左找到首个非透明像素的坐标 */
    on = true;
    int x4, y4;
    for(int x = img.width() - 1; (x >= 0 && on); x--){
        for(int y = 0; (y < img.height() && on); y++){
            if(img.access(x, y).a != 0){
                x4 = x;
                y4 = y;
                on = false;
            }
        }
    }

    /* 将得到的四个坐标综合计算出一个矩形的左上角坐标以及宽度和高度(x3,y1)(x4,y2)，这个矩形范围内包含了所有可见像素 */
    result.x = x3;
    result.y = y1;
    result.width = x4 - x3 + 1;
    result.height = y2 - y1 + 1;
}

PACKER_END