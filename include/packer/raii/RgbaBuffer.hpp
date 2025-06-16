#ifndef PACKER_RGBABUFFER_HPP
#define PACKER_RGBABUFFER_HPP

#include <cstdlib>
#include "packer/packer.hpp"
#include "packer/data/data.hpp"
PACKER_BEGIN

/* 对RGBA结构体数组的RAII封装 */
class RgbaBuffer{
public:
    RgbaBuffer();
    RgbaBuffer(int size);
    RgbaBuffer(const RgbaBuffer &oth) =delete;
    RgbaBuffer(RgbaBuffer &&oth) noexcept;
    ~RgbaBuffer();

    RGBA* use();
    const RGBA* cuse() const;
    int size();

    operator bool();
    RgbaBuffer& operator=(const RgbaBuffer &rhs) =delete;
    RgbaBuffer& operator=(RgbaBuffer &&rhs) noexcept;

private:
    int m_size;
    RGBA *m_buffer;
};

PACKER_END
#endif