# 1.libpacker简介
libpacker是一个用于将一组png图片合并为一个png图片的工具库，并且提供了提取其中任意一张png图片的功能。libpacker没有与任何图片库绑定，正因如此，libpacker无法直接使用，用户首先需要根据自身情况实现一组接口，这些接口用于提供图片的读取和写入功能。



# 2.libpacker的组成

libpacker主要借助下方的类及其派生类来完成图片的打包和解包功能：

* VImage：对于图片的像素数据的抽象接口，提供与具体图片种类无关的像素数据访问功能
* VImageReader：图片的读取接口，向上提供图片的像素数据以及图片的id，用户需要实现此类的接口
* VImageWriter：图片的写入接口，上层应用会向此类提供像素数据，用户需要实现此类的接口以便决定如何处理这些像素数据
* VProfileReader：档案读取接口，档案(Profile)记录了一张png图片的大小以及位置信息，此接口已存在默认实现，用户可选择自定义
* VProfileWriter：档案写入接口，此接口已存在默认实现，用户可选择自定义
* VScanner：扫描器接口，扫描器的作用是从上下左右四个方向对一个png图片的像素进行扫描，并根据最终得到的四个坐标计算出一个矩形范围，该范围内囊括了该png图片的所有非透明像素
* VLayouter：布局器接口，布局器用于计算指定宽度和高度的png图片在最后合并的图片(后续称图集)中的位置，以及计算所有图片合并时，总的宽度和高度
* VPacker：打包器接口，向用户提供打包功能
* VUnpacker：解包器接口，向用户提供解包功能



# 3.打包流程

1. 用户通过VPacker::addImageReader向打包器中添加VImageReader 

2. 用户调用VPacker::pack执行打包 

3. VPacker根据用户添加的ImageReader对象读取图片数据并保存为VImage对象 

4. VPacker使用VScanner扫描每一个VImage对象并保存它们的非透明像素范围
5. VPacker使用VLayouter计算每一个VImage对象在图集中的位置
6. VPacker通过VLayouter::packedWidth和VLayouter::packerHeight获取到图集的宽度和高度，并以此创建一个VImage对象，然后将每一个VImage对象的像素数据拷贝到该对象中
7. 用户调用VPacker::save函数，并提供VImageWriter和VProfileWriter对象，以保存图集及其中每个png图片的位置信息(Profile)



# 4.解包流程

1. 用户通过Unpacker::Unpacker构造函数传入图集的VImageReader和VProfileReader

2. 用户调用VUnpacker::unpack执行解包

3. Unpacker通过用户提供的VImageReader和VProfileReader读入图集的像素数据以及Profile

4. 用户调用Unpacker::getImageById获取特定的图片
5. Unpacker根据id查找到Profile，然后根据Profile中记录的图片宽高创建一个空白的VImage对象，然后再根据Profile记录的位置信息将图集中对应位置的像素数据拷贝到VImage对象并返回给用户



# 5.接口实现

## 5.1.实现ImageReader

在开始前，我们假设存在图片库mypng，库中提供了以下接口：

```C++
PNGHandle* mypng::open(const char *name); //打开png文件
int mypng::width(PNGHandle *handle);      //获取图片宽度
int mypng::height(PNGHandle *handle);     //获取图片高度
int mypng::read(int x, int y, PNGHandle *handle);  //读取指定位置的像素
void mypng::close(PNGHandle *handle);     //关闭png文件

PNGHandle* mypng::create(int width, int height); //创建png文件
void mypng::write(int x, int y, int pix, PNGHandle *handle); //向指定位置写入像素
void mypng::save(const char *name, PNGHandle *handle); //保存png文件
```

要实现我们的ImageReader，我们首先需要使用一个类继承ImageReader，并实现其中的initialize、readAllRGB、finalize函数，它们的作用分别是打开图片并初始化、拷贝像素、关闭图片，同时，还需要实现VImageReader中的id函数，该函数需要返回一个string，用于标识该图片，以便后续解包时作为图片的索引。

```C++
#include "packer/impl/ImageReader.hpp"
using packer::ImageReader;

class MyImageReader : public ImageReader{
public:
    MyImageReader(const char *name) : m_name(name){}
    
    std::string id() override{
        return m_name;
    }
    
protected:
    void initialize(int &width, int &height) override{
        m_handle = mypng::open(m_name.cstr());
        width = mypng::width(m_handle);
        height = mypng::height(m_handle);
    }
    
    void readAllRGB(RGBA *buffer) override{
        int width = mypng::width(m_handle);
        int height = mypng::height(m_handle);
        
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                int pix = mypng::read(x, y, m_handle);
                
                /* 分别获取每个分量并赋值给RGBA成员 */
                RGBA &rgb = buffer[y * width + x];
                rgb.a = pix & 0xFF;
                rgb.b = (pix >> 8) & 0xFF;
                rgb.g = (pix >> 16) & 0xFF;
                rgb.r = (pix >> 24) & 0xFF;
            }
        }
    }
    
    void finalize() override{
        mypng::close(m_hanlde);
    }
    
private:
    std::string m_name;
    PNGHandle *m_handle;
};
```

当用户调用ImageReader的read函数时，ImageReader会首先调用initialize函数，以便让我们的MyImageReader首先打开和初始化图片，我们需要将图片的宽高通过width和height引用传递给基类，随后基类会创建一个与我们给定的宽高一致的空白VImage对象，并将该对象的RGBA缓冲区通过readAllRGB函数传递给我们的MyImageReader，而我们就需要在readAllRGB函数内实现将png图片的像素拷贝到RGBA缓冲区的功能。最后，基类调用finalize函数执行清理操作。



## 5.2.实现ImageWriter

ImageWriter的功能与ImageReader基本对称，我们首先需要使用一个类继承ImageWriter，然后实现initialize、writeAllRGB、finalize函数：

```C++
#include "packer/impl/ImageWriter.hpp"
using packer::ImageWriter;

class MyImageWriter : public ImageWriter{
public:
    MyImageWriter(const char *name) : m_name(name){}

protected:
    void initialize(int width, int height) override{
        m_handle = mypng::create(width, height);
    }
    
    void writeAllRGB(RGBA *buffer) override{
        int width = mypng::width(m_handle);
        int height = mypng::height(m_handle);
        
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                int pix = 0;
                RGBA &rgb = buffer[y * width + x];
                pix |= (rgb.r & 0xFF);
                pix << 8;
                pix |= (rgb.g & 0xFF);
                pix << 8;
                pix |= (rgb.b & 0xFF);
                pix << 8;
                pix |= (rgb.a & 0xFF);
                
                mypng::write(x, y, pix, m_handle);
            }
        }
    }
    
    void finalize() override{
        mypng::save(m_name.cstr(), m_handle);
        mypng::close(m_handle);
    }
    
private:
    std::string m_name;
    PNGHandle *m_handle;
};
```

基类会把将要写入的图片的宽高通过initialize函数传递给MyImageWriter，我们可以借此创建对应宽高的图片，然后，在writeAllRGB函数中将像素数据拷贝到我们的图片中，最后在finalize函数中将图片保存到文件。

 

# 6.使用

## 6.1.打包

打包功能的使用方式如下：

```C++
#include "packer/impl/Packer.hpp"
#include "packer/impl/DefaultProfileWriter.hpp"
using packer::Packer;
using packer::DefaultProfileWriter;

void doPack(){
    Packer packer(16, 30); //设置图集宽度为480像素(16x30)，需要打包的图片不能超过此宽度
    MyImageWriter iwriter("total.png");
    DefaultProfileWriter pwriter("total.prf");
    
    packer.addImageReader(new MyImageReader("a.png")); //packer在析构时会负责删除Reader对象，所以直接从堆上分配
    packer.addImageReader(new MyImageReader("b.png"));
    packer.addImageReader(new MyImageReader("c.png"));
    packer.pack();  //打包
    packer.save(iwriter, pwriter); //保存
}
```

Packer为一次性工具，这意味着pack函数不可重复调用，并且调用pack函数后也不应该再调用addImageReader继续添加读取器。



## 6.2.解包

解包功能的使用方式如下：

```C++
#include "packer/impl/Unpacker.hpp"
#include "packer/impl/DefaultProfileReader.hpp"
using packer::Unpacker;
using packer::DefaultProfileReader;

void doUnpack(){
	//Unpacker析构时会负责删除reader，所以直接从堆上分配即可
   	Unpacker unpacker(new MyImageReader("total.png"), new DefaultProfileReader("total.prf"));
   	unpacker.unpack(); //解包
    VImage *img = unpacker.getImageById("a.png"); //使用前文中的id来获取图片，用户需要负责删除VImage对象
    
    /* 使用VImage对象 */
    ...
    delete img;
}
```

由于VImage对象并非可直接用于绘制的图片对象(例如在Qt中要使用QImage)，因此我们可以选择将MyImageWriter做些许调整，使之提供一个返回适用于平台的图片对象的接口。



## 6.3.例子

在src/test目录下存在源文件TestPacker.cpp，其中以文本字符的表现形式实现了ImageReader和ImageWriter，可供参考。
