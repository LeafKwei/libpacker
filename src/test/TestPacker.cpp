#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include "packer/impl/Packer.hpp"
#include "packer/impl/Unpacker.hpp"
#include "packer/impl/ImageReader.hpp"
#include "packer/impl/ImageWriter.hpp"
#include "packer/impl/DefaultProfileWriter.hpp"
#include "packer/impl/DefaultProfileReader.hpp"

using std::string;
using std::vector;
using namespace packer;

class NoSrcImageReader : public ImageReader{
public:
    NoSrcImageReader(){
        buf[0] = '@';
        buf[1] = '$';
        buf[2] = '&';
        srand(time(NULL));
    }

    std::string id() override{
        string tmp;

        for(int i = 0; i < 16; i++){
            tmp.push_back(rand() % 26 + 65);
        }

        return tmp;
    }

    ~NoSrcImageReader(){
        //std::cout << "~NoSrcImageReader" << std::endl;
    }

protected:
    ImageSize openImage() override{
        this -> width = rand() % 26 + 15;
        this -> height = rand() % 26 + 15;
        return makeImageSize(width, height);
    }

    inline void readRGB(int x, int y, RGBA &rgba) noexcept override{
        if((y < 5 || y > height - 5) || (x < 5 || x > width - 5)){
            rgba.a = 0;
            return;
        }

        rgba.a = 255;
        rgba.r = buf[index];
        rgba.g = buf[index];
        rgba.b =  buf[index];
    }

    void closeImage() override{
        index = (index + 1) % 3;
    }

private:
    static int index;
    char buf[3];
    int width;
    int height;
};

int NoSrcImageReader::index = 0;

class FileImageReader : public ImageReader{
public:
    FileImageReader(const char *path){
        file = fopen(path, "r");
        string tmp(path);
        size_t pos =  tmp.rfind('/');
        if(pos != string::npos){
            tmp = tmp.substr(pos + 1, tmp.length() - (pos + 1));
        }

        ID = tmp;
        pos = tmp.find(".");
        if(pos != string::npos){
            ID = tmp.substr(0, pos);
        }
    }

    ~FileImageReader(){
        //std::cout << "~FileImageReader" << std::endl;
    }

    std::string id() override{
        return ID;
    }

protected:
    ImageSize openImage() override{
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *buffer = (char*) calloc(65535, 1);
        fgets(buffer, 65535, file);
        this -> width = strlen(buffer);
        this -> height = size / this -> width;
        width = this -> width;
        height = this -> height;
        fseek(file, 0, SEEK_SET);
        free(buffer);

        return makeImageSize(width, height);
    }

    inline void readRGB(int x, int y, RGBA &rgba) noexcept override{
        int ch = fgetc(file);
        if(ch == '\n') return;
        if(ch == '#'){
            rgba.a = 0;
            return;
        }

        rgba.a = 255;
        rgba.r = rgba.g = rgba.b = ch;
    }

    void closeImage() override{
        fclose(file);
    }

private:
    int width;
    int height;
    string ID;
    FILE *file;
};

class FileImageWriter : public ImageWriter{
public:
    FileImageWriter(const char* path) : path(path){}

protected:
    void  openImage(ImageSize size) override{
        file = fopen(path.c_str(), "w");
        this -> width = toWidth(size);
        this -> height = toHeight(size);
    }

    inline void writeRGB(int x, int y, const RGBA &rgba) noexcept override{
        if(y != 0 && x == 0) fputc('\n', file);
        int ch = (rgba.a == 0) ? '#' : rgba.r;
        fputc(ch, file);
    }

    virtual void closeImage() override{
        fclose(file);
    }

private:
    int width;
    int height;
    FILE *file;
    string path;
};

int main(int argc, char *argv[]){
    if(argc == 1 || strcmp(argv[1], "pack") == 0){
        Packer packer(16, 30);
        FileImageWriter fwriter("output.txt");
        DefaultProfileWriter pwriter("output.prf");

        packer.addImageReader(new NoSrcImageReader());
        packer.addImageReader(new NoSrcImageReader());
        packer.addImageReader(new NoSrcImageReader());
        packer.addImageReader(new NoSrcImageReader());

        packer.pack();
        packer.save(fwriter, pwriter);
    }
    else{
        Unpacker unpacker(new FileImageReader("output.txt"), new DefaultProfileReader("output.prf"));
        unpacker.unpack();
        std::vector<string> idvec = unpacker.idList();

        for(auto &id : idvec){
            VImagePtr  imgptr(unpacker.getImageById(id));
            FileImageWriter fwriter((id + ".txt").c_str());
            fwriter.write(*(imgptr.get()));
        }
    }
}
