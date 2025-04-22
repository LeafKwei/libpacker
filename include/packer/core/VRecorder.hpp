#ifndef PACKER_VRECODER_HPP
#define PACKER_VRECODER_HPP

#include "packer/data.hpp"
#include "packer/packer.hpp"
PACKER_BEGIN

/* Recoder用于记录每个png文件的布局位置，并提供了遍历所有png布局的功能 */
class VRecorder{
public:
    virtual void put(const Rect &rect) =0;
    virtual void begin() =0;
    virtual bool end() =0;
    virtual const Rect& next() const =0;
    virtual ~VRecorder() =0;
};

PACKER_END
#endif