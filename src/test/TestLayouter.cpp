#include <cstdio>
#include <iostream>
#include "packer/impl/ScaledLayouter.hpp"

using packer::Rect;

void printRect(const Rect &r){
    printf("X:%d, Y:%d, W:%d, H:%d\n", r.x, r.y, r.width, r.height);
}

void printLayouter(const packer::VLayouter &layouter){
    printf("W: %d, H: %d\n", layouter.packedWidth(), layouter.packedHeight());
}

int main(void){
    packer::ScaledLayouter layouter(16, 2, 1);
    Rect r1 = layouter.laydown(makeImageSize(40, 50));
    printRect(r1);
    Rect r2 = layouter.laydown(makeImageSize(50, 40));
    printRect(r2);
    Rect r3 = layouter.laydown(makeImageSize(100, 300));
    printRect(r3);
    Rect r4 = layouter.laydown(makeImageSize(300, 100));
    printRect(r4);
    Rect r5 = layouter.laydown(makeImageSize(1,1));
    printRect(r5);
    printLayouter(layouter);
}