#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include "packer/packer.hpp"
#include "packer/util/Bitmap.hpp"

using std::logic_error;
using std::runtime_error;
PACKER_BEGIN

Bitmap::Bitmap(int size) : m_ptr(nullptr){
    if(size <= 0) throw logic_error("Unexcepted bitmap size.");
    resize(size);
}

Bitmap::~Bitmap(){
    if(m_ptr != NULL) free(m_ptr);
}

void Bitmap::set(int pos){
    int byteIdx = pos / 8;
    if(byteIdx < 0 || byteIdx >= m_bytes) throw logic_error("Invalid postion.");
    m_ptr[byteIdx] |= 1 << (pos % 8);
}

void Bitmap::unset(int pos){
    int byteIdx = pos / 8;
    if(byteIdx < 0 || byteIdx >= m_bytes) throw logic_error("Invalid postion.");
    m_ptr[byteIdx] &= ~(1 << (pos % 8));
}

bool Bitmap::test(int pos) const{
    int byteIdx = pos / 8;
    if(byteIdx < 0 || byteIdx >= m_bytes) throw logic_error("Invalid postion.");
    uint8_t tmp = m_ptr[byteIdx];
    return (tmp >> (pos % 8)) & 1;
}

void Bitmap::resize(int size){
    if(size <= 0) return;
    int tmp_bytes = (size / 8) + 1;
    uint8_t* tmp_ptr = (uint8_t*) calloc(sizeof(uint8_t) * tmp_bytes, 1);
    if(tmp_ptr == NULL) throw runtime_error("Out of memery.");

    /* Bitmap未初始化时，直接赋值指针 */
    if(m_ptr == NULL){
        m_size = size;
        m_bytes = tmp_bytes;
        m_ptr = tmp_ptr;
        return;
    }

    /* Bitmap已初始化时，先拷贝已有数据再赋值指针 */
    int cnt = m_bytes < tmp_bytes ? m_bytes : tmp_bytes;
    memcpy(tmp_ptr, m_ptr, cnt);
    free(m_ptr);
    m_size = size;
    m_bytes = tmp_bytes;
    m_ptr = tmp_ptr;
}

void Bitmap::clear(){
    memset(m_ptr, 0, m_bytes);
}

int Bitmap::size() const{
    return m_size;
}

PACKER_END