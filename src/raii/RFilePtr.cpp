#include <stdexcept>
#include <cassert>
#include "packer/raii/RFilePtr.hpp"

using std::logic_error;
using std::runtime_error;
PACKER_BEGIN

RFilePtr::RFilePtr() : m_ptr(NULL){}

RFilePtr::RFilePtr(const char *path, const char *mode){
    m_ptr = fopen(path, mode);
    if(m_ptr == NULL) throw logic_error("Failed to open file.");
}

RFilePtr::RFilePtr(RFilePtr &&oth) noexcept :
    m_ptr(oth.m_ptr)
{
    oth.m_ptr = NULL;
}

RFilePtr::~RFilePtr(){
    fclose(m_ptr);
    m_ptr = NULL;
}

FILE* RFilePtr::use(){
    return m_ptr;
}

RFilePtr::operator bool(){
    return m_ptr != NULL ? true : false;
}

RFilePtr& RFilePtr::operator=(RFilePtr &&rhs) noexcept{
    assert(this != std::addressof(rhs));
    m_ptr = rhs.m_ptr;
    rhs.m_ptr = NULL;
}

PACKER_END