#include <stdexcept>
#include <cassert>
#include "packer/raii/RCharBuffer.hpp"

using std::logic_error;
using std::runtime_error;
PACKER_BEGIN

RCharBuffer::RCharBuffer() : m_buffer(NULL){}

RCharBuffer::RCharBuffer(int size){
    m_buffer = (char*) malloc(size * sizeof(char));
    if(m_buffer == NULL) throw runtime_error("Failed to malloc memory.");
    m_size = size;
}

RCharBuffer::RCharBuffer(RCharBuffer &&oth) noexcept : 
    m_buffer(oth.m_buffer), m_size(oth.m_size)
{
    oth.m_buffer = NULL;
}

RCharBuffer::~RCharBuffer(){
    free(m_buffer);
    m_buffer = NULL;
}

char* RCharBuffer::use(){
    return m_buffer;
}

int RCharBuffer::size(){
    return m_size;
}

RCharBuffer::operator bool(){
    return m_buffer != NULL ? true : false;
}

RCharBuffer& RCharBuffer::operator=(RCharBuffer &&rhs) noexcept{
    assert(this != std::addressof(rhs));
    m_buffer = rhs.m_buffer;
    m_size = rhs.m_size;
    rhs.m_buffer = NULL;
    return *this;
}

PACKER_END