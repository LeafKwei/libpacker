#ifndef PACKER_RCHARBUFFER_HPP
#define PACKER_RCHARBUFFER_HPP

#include "packer/packer.hpp"
PACKER_BEGIN

class RCharBuffer{
public:
    RCharBuffer();
    RCharBuffer(int size);
    RCharBuffer(const RCharBuffer &oth) =delete;
    RCharBuffer(RCharBuffer &&oth) noexcept;
    ~RCharBuffer();
    
    char* use();
    int size();

    operator bool();
    RCharBuffer& operator=(RCharBuffer &rhs) =delete;
    RCharBuffer& operator=(RCharBuffer &&rhs) noexcept;

private:
    int m_size;
    char* m_buffer;
};

PACKER_END
#endif