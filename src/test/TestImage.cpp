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

    void readRGB(RGBA *buffer) override{
        for(int y = 0; y < 60; y++){
            for(int x = 0; x < 30; x++){
                RGBA &rgb = buffer[y * 30 + x];
                rgb.a = 255;
            }
        }
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

    void writeRGB(const RGBA *buffer) override{
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                if(buffer[y * width + x].a == 255){
                    std::cout << "*";
                }
                else{
                    std::cout << "+";
                }
            }
            std::cout << std::endl;
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