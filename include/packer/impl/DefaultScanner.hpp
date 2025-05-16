#ifndef PACKER_DEFAULTSCANNER_HPP
#define PACKER_DEFAULTSCANNER_HPP

#include <map>
#include "packer/packer.hpp"
#include "packer/core/VScanner.hpp"

PACKER_BEGIN

/** 
 * VScanner的实现，采用的算法是从上到下，从下到上横向扫描，找到位于最上方和最下方的首个非透明像素，
 * 以及从左到右，从右到左的纵向扫描，找到位于最左方和最右方的首个非透明像素，最后根据这四个点的坐标
 * 算出一个矩形范围，这个范围囊括了所有的非透明像素
 */
class DefaultScanner : public VScanner{
public:
    DefaultScanner();
    ~DefaultScanner() override;
    void scan(const VImage &img, Rect &result) override;
};

PACKER_END
#endif