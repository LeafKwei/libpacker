#include <iostream>
#include "packer/data/data.hpp"
#include "packer/impl/Image.hpp"
#include "packer/impl/ImageReader.hpp"
#include "packer/impl/ImageWriter.hpp"
using packer::RGBA;
using packer::Rect;
using packer::Image;
using packer::VImage;
using packer::ImageReader;
using packer::ImageWriter;

class MyReader : public ImageReader{
protected:
    std::string id() override{
        return "";
    }

    void initialize(int &width, int &height) override{
            width = 30;
            height = 60;
    }

    inline void readRGB(int x, int y, RGBA &rgba) override{
        rgba.a = 255;
    }

    void finalize() override{

    }

private:
    int tmp1, tmp2;
    int m_cusWidth;
    int m_cusHeight;
};

class MyWriter : public ImageWriter{
protected:
    void initialize(int width, int height) override{
        this -> width = width;
        this -> height = height;
        std::cout << "----------------------------" << std::endl;
        std::cout << "image size: " << width << ", " << height << std::endl;;
    }

    inline void writeRGB(int x, int y, const RGBA &rgba) override{
        /* 在打印新行前打印换行符 */
        if(y != 0 && x == 0){
            std::cout << std::endl;
        }

        if(rgba.a == 255){
            std::cout << "*";
        }
        else{
             std::cout << "+";
        }
    }

    void finalize(){
            std::cout << "over" << std::endl;
    }

private:
    int width;
    int height;
};

int main(void){
    MyReader reader;
    MyWriter writer;
    VImage *img1 = reader.read();
    Image img2(50, 50);
    writer.write(*img1);
    packer::Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.width = 10;
    rect.height = 10;
    img2.placeRect(20, 20, *img1, rect);
    writer.write(img2);

    delete img1;
    return 0;
}