#include <iostream>
#include "packer/data.hpp"
#include "packer/impl/GapImage.hpp"
using packer::RGBA;
using packer::Rect;
using packer::GapImage;
using packer::VImage;

class MyImage : public GapImage{
public:
    MyImage(int width, int height){
        tmp1 = width;
        tmp2 = height;
        custom();
    }

protected:
    void readRawImage() override{
        m_cusWidth = tmp1;
        m_cusHeight = tmp2;
    }

    int customedWidth() const override{
        return m_cusWidth;
    }

    int customedHeight() const override{
        return m_cusHeight;
    }

    void fillData(int x, int y, RGBA &rgb) override{
        rgb.a = 255;
        rgb.r = 29;
        rgb.g = 100;
        rgb.b = 30;
    }

private:
    int tmp1, tmp2;
    int m_cusWidth;
    int m_cusHeight;
};

void printImage(const VImage &img){
    std::cout << "----------------------------" << std::endl;
    std::cout << img.width() << "," << img.height() << std::endl;
    for(int y = 0; y < img.height(); y++){
        for(int x = 0; x < img.width(); x++){
            if(img.access(x, y).a == 255){
                std::cout << "*";
            }
            else{
                std::cout << "+";
            }
        }
        std::cout << std::endl;
    }
}

int main(void){
    MyImage img1(10, 10);
    GapImage img2(50, 50);
    printImage(img1);
    packer::Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.width = 10;
    rect.height = 10;
    img2.placeRect(20, 20, img1, rect);
    printImage(img2);

    std::cout << "over" << std::endl;
    return 0;
}