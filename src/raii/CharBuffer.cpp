#include <stdexcept>
#include <cassert>
#include "packer/raii/CharBuffer.hpp"

using std::logic_error;
using std::runtime_error;
PACKER_BEGIN

CharBuffer::CharBuffer() : m_buffer(NULL){}

CharBuffer::CharBuffer(int size){
    m_buffer = (char*) malloc(size * sizeof(char));
    if(m_buffer == NULL) throw runtime_error("Failed to malloc memory.");
    m_size = size;
}

CharBuffer::CharBuffer(CharBuffer &&oth) noexcept : 
    m_buffer(oth.m_buffer), m_size(oth.m_size)
{
    oth.m_buffer = NULL;
}

CharBuffer::~CharBuffer(){
    free(m_buffer);
    m_buffer = NULL;
}

char* CharBuffer::use(){
    return m_buffer;
}

int CharBuffer::size(){
    return m_size;
}

CharBuffer::operator bool(){
    return m_buffer != NULL ? true : false;
}

CharBuffer& CharBuffer::operator=(CharBuffer &&rhs) noexcept{
    assert(this != std::addressof(rhs));
    m_buffer = rhs.m_buffer;
    m_size = rhs.m_size;
    rhs.m_buffer = NULL;
    return *this;
}

PACKER_END