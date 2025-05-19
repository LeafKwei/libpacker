#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
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

protected:
    void initialize(int &width, int &height) override{
        this -> width = rand() % 26 + 15;
        this -> height = rand() % 26 + 15;
        width = this -> width;
        height = this -> height;
    }

    void readAllRGB(RGBA *buffer) override{
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                RGBA &rgba = buffer[y * width + x];
                if((y < 5 || y > height - 5) || (x < 5 || x > width - 5)){
                    rgba.a = 0;
                    continue;;
                }

                rgba.a = 255;
                rgba.r = buf[index];
                rgba.g = buf[index];
                rgba.b =  buf[index];
            }
        }
    }

    void finalize() override{
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

    std::string id() override{
        return ID;
    }

protected:
    void initialize(int &width, int &height) override{
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
    }

    void readAllRGB(RGBA *buffer) override{
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                RGBA &rgba = buffer[y * width + x];
                int ch = fgetc(file);
                if(ch == '\n') break;
                if(ch == '#'){
                    rgba.a = 0;
                    continue;
                }

                rgba.a = 255;
                rgba.r = rgba.g = rgba.b = ch;
            }
        }
    }

    void finalize() override{
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
    virtual void  initialize(int width, int height) override{
        file = fopen(path.c_str(), "w");
        this -> width = width;
        this -> height = height;
    }

    virtual void  writeAllRGB(const RGBA *buffer) override{
        for(int y = 0; y < height; y++){
            for(int x =0 ; x < width; x++){
                const RGBA &rgba = buffer[y * width + x];
                int ch = (rgba.a == 0) ? '#' : rgba.r;
                fputc(ch, file);
            }
            fputc('\n', file);
        }
    }

    virtual void finalize() override{
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
            VImage *img = unpacker.getImageById(id);
            FileImageWriter fwriter((id + ".txt").c_str());
            fwriter.write(*img);
            delete img;
        }
    }
}
