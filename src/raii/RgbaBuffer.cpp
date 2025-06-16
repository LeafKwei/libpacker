#include <stdexcept>
#include <cassert>
#include "packer/raii/RgbaBuffer.hpp"

using std::logic_error;
using std::runtime_error;
PACKER_BEGIN

RgbaBuffer::RgbaBuffer() : m_buffer(NULL), m_size(0){}

RgbaBuffer::RgbaBuffer(int size) : m_buffer(NULL){
    m_buffer = (RGBA*) calloc(size, sizeof(RGBA));
    if(m_buffer == NULL) throw runtime_error("Failed to malloc memory.");
    m_size = size;
}

RgbaBuffer::RgbaBuffer(RgbaBuffer &&oth) noexcept 
    : m_buffer(oth.m_buffer) 
    , m_size(oth.m_size)
{
    oth.m_buffer = NULL;
}

RgbaBuffer::~RgbaBuffer(){
    free(m_buffer);
}

RGBA* RgbaBuffer::use(){
    return m_buffer;
}

const RGBA* RgbaBuffer::cuse() const{
    return m_buffer;
}

int RgbaBuffer::size(){
    return m_size;
}

RgbaBuffer::operator bool(){
    return m_buffer != NULL;
}

RgbaBuffer& RgbaBuffer::operator=(RgbaBuffer &&rhs) noexcept{
    assert(this != std::addressof(rhs));
    free(m_buffer);
    m_buffer = rhs.m_buffer;
    rhs.m_buffer = NULL;
    return *this;
}

PACKER_END