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
    free(m_ptr);
    m_ptr = NULL;
}

void Bitmap::set(int pos){
    int byteIdx = pos / 8;
    if(isBadIdx(byteIdx)) throw logic_error("Invalid postion.");
    m_ptr[byteIdx] |= 1 << (pos % 8);
}

void Bitmap::setn(int pos, int n){
    int maxIdx = (pos + n - 1) / 8;
    if(isBadIdx(maxIdx)) throw logic_error("Invalid postion or length.");
    for(int i = pos; i < pos + n; i++){
        int byteIdx = i / 8;
        m_ptr[byteIdx] |= (1 << i % 8);
    }
}

void Bitmap::unset(int pos){
    int byteIdx = pos / 8;
    if(isBadIdx(byteIdx)) throw logic_error("Invalid postion.");
    m_ptr[byteIdx] &= ~(1 << (pos % 8));
}

void Bitmap::unsetn(int pos, int n){
    int maxIdx = (pos + n - 1) / 8;
    if(isBadIdx(maxIdx)) throw logic_error("Invalid postion or length.");
    for(int i = pos; i < pos + n; i++){
        int byteIdx = i / 8;
        m_ptr[byteIdx] &= ~(1 << i % 8);
    }
}

bool Bitmap::test(int pos) const{
    int byteIdx = pos / 8;
    if(isBadIdx(byteIdx)) throw logic_error("Invalid postion.");
    uint8_t tmp = m_ptr[byteIdx];
    return (tmp >> (pos % 8)) & 1;
}

bool Bitmap::testAND(int pos, int len){
    int result = 1;
    int maxIdx = (pos + len - 1) / 8;
    if(isBadIdx(maxIdx)) throw logic_error("Invalid postion or length.");
    for(int i = pos; i < pos + len; i++){
        int byteIdx = i / 8;
        uint8_t tmp = m_ptr[byteIdx];
        result &= ((tmp >> (i % 8)) & 1);
        if(result == 0) break;
    }

    return result;
}

bool Bitmap::testOR(int pos, int len){
     int result = 0;
    int maxIdx = (pos + len - 1) / 8;
    if(isBadIdx(maxIdx)) throw logic_error("Invalid postion or length.");
    for(int i = pos; i < pos + len; i++){
        int byteIdx = i / 8;
        uint8_t tmp = m_ptr[byteIdx];
        result |= ((tmp >> (i % 8)) & 1);
        if(result == 1) break;
    }

    return result;
}

void Bitmap::resize(int size){
    if(size <= 0) throw logic_error("Size must be a positive number.");
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

inline bool Bitmap::isBadIdx(int idx) const{
    if(idx < 0 || idx >= m_bytes) return true;
    return false;
}

PACKER_END