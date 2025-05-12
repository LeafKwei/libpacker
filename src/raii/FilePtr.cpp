#include <stdexcept>
#include <cassert>
#include "packer/raii/FilePtr.hpp"

using std::logic_error;
using std::runtime_error;
PACKER_BEGIN

FilePtr::FilePtr() : m_ptr(NULL){}

FilePtr::FilePtr(const char *path, const char *mode){
    m_ptr = fopen(path, mode);
    if(m_ptr == NULL) throw logic_error("Failed to open file.");
}

FilePtr::FilePtr(FilePtr &&oth) noexcept :
    m_ptr(oth.m_ptr)
{
    oth.m_ptr = NULL;
}

FilePtr::~FilePtr(){
    fclose(m_ptr);
    m_ptr = NULL;
}

FILE* FilePtr::use(){
    return m_ptr;
}

FilePtr::operator bool(){
    return m_ptr != NULL ? true : false;
}

FilePtr& FilePtr::operator=(FilePtr &&rhs) noexcept{
    assert(this != std::addressof(rhs));
    m_ptr = rhs.m_ptr;
    rhs.m_ptr = NULL;
    return *this;
}

PACKER_END