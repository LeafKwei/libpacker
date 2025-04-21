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
    void set(int pos);    //将pos位置的bit置1
    void unset(int pos);  //将pos位置的bit置0
    bool test(int pos) const; //测试pos位置的bit是否为1
    void resize(int size);    //重设Bitmap的大小，已set的bit位将再在新的Bitmap中保留
    int size() const;         //获取Bitmap的大小
    void clear();             //将所有bit位置0

private:
    int m_size;
    int m_bytes;
    uint8_t *m_ptr;
};

PACKER_END
#endif