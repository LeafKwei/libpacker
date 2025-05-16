#ifndef PACKER_RCHARBUFFER_HPP
#define PACKER_RCHARBUFFER_HPP

#include "packer/packer.hpp"
PACKER_BEGIN

/* 对char类型的内存缓冲区的RAII封装 */
class CharBuffer{
public:
    CharBuffer();
    CharBuffer(int size);
    CharBuffer(const CharBuffer &oth) =delete;
    CharBuffer(CharBuffer &&oth) noexcept;
    ~CharBuffer();
    
    char* use();
    int size();

    operator bool();
    CharBuffer& operator=(CharBuffer &rhs) =delete;
    CharBuffer& operator=(CharBuffer &&rhs) noexcept;

private:
    int m_size;
    char* m_buffer;
};

PACKER_END
#endif