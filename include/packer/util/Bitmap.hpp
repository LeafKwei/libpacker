#ifndef PACKER_BITMAP_HPP
#define PACKER_BITMAP_HPP

#include <cstdint>
#include "packer/packer.hpp"
PACKER_BEGIN

class Bitmap{
public:
    Bitmap(int size=16);
    Bitmap(const Bitmap &oth) =delete;
    ~Bitmap();
    Bitmap& operator=(const Bitmap &rhs) =delete;
    void set(int pos);                       //将pos位置的bit置1
    void setn(int pos, int n);           //将pos位置开始，长度为n的所有bit置1
    void unset(int pos);                  //将pos位置的bit置0
    void unsetn(int pos, int n);       //将pos位置开始，长度为n的bit置0
    bool test(int pos) const;           //测试pos位置的bit是否为1
    bool testAND(int pos, int len); //测试pos位置开始，长度为len的所有bit是否均为1
    bool testOR(int pos, int len);    //测试pos位置开始，长度为len 的所有bit是否至少有一个为1
    void resize(int size);    //重设Bitmap的大小，已set的bit位将再在新的Bitmap中保留
    int size() const;           //获取Bitmap的大小
    void clear();                //将所有bit位置0
    inline bool isBadIdx(int idx) const; //检查索引是否越界

private:
    int m_size;
    int m_bytes;
    uint8_t *m_ptr;
};

PACKER_END
#endif