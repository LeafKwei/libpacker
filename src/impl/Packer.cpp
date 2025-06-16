#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "packer/impl/Packer.hpp"
#include "packer/impl/Image.hpp"
#include "packer/impl/DefaultScanner.hpp"
#include "packer/impl/ScaledLayouter.hpp"

using std::logic_error;
using std::runtime_error;
using std::cerr;
using std::endl;
using std::string;
PACKER_BEGIN

Packer::Packer(int scale, int scaledWidth) : m_state(State::PK_EMPTY), m_image(nullptr) {
    if(scale <= 0 || scaledWidth <= 0) throw logic_error("Invalid scale or scaled width.");
    m_scale = scale;
    m_scaledWidth = scaledWidth;
}

Packer::~Packer(){
    
}

void Packer::addImageReader(VImageReader *imgReader){
    if(imgReader == nullptr) throw logic_error("Image reader can not be nullptr.");
    m_readers.push_back(VImageReaderPtr(imgReader));
}

void Packer::pack(){
    if(m_state == State::PK_PACKED) throw logic_error("Can not pack repeatly.");
    try{
        readImage();
        scanImage();
        layImage();
        packImage();
        m_state = State::PK_PACKED;
    }
    catch(logic_error &err){
        throw logic_error(string("Failed: ") + err.what());
    }
    catch(runtime_error &err){
        throw logic_error(string("*Failed: ") + err.what());
    }
}

void Packer::save(VImageWriter &imgWriter, VProfileWriter &prfWriter){
    if(m_state != State::PK_PACKED) throw logic_error("Operation `save' can be used only after pack.");
    try{
        for(auto &rc : m_records){
            if(!rc) continue;
            prfWriter.write(rc.profile);
        }

        imgWriter.write(*(m_image.get()));
    }
    catch(logic_error &err){
        throw logic_error(string("Failed: ") + err.what());
    }
    catch(runtime_error &err){
        throw logic_error(string("*Failed: ") + err.what());
    }
}

void Packer::readImage(){
    for(auto &reader : m_readers){
        Record record;
        record.imgptr = reader -> read();
        record.profile.id = reader -> id();
        m_records.push_back(record);
    }
}

void Packer::scanImage(){
    DefaultScanner scanner;

    for(auto &rc : m_records){
        Rect tmp;
        scanner.scan(*(rc.imgptr.get()), tmp);
        rc.profile.srcRange = tmp;
    }
}

void Packer::layImage(){
    auto beg = m_records.begin();
    auto end = m_records.end();
    ScaledLayouter layouter(m_scale, m_scaledWidth, (int)(1.5 * m_scaledWidth));

    //将vector中的Record按图片大小升序排序
    std::sort(m_records.begin(), m_records.end(), [](const Record &r1, const Record &r2) -> bool{
        int area1 = r1.profile.srcRange.width * r1.profile.srcRange.height;
        int area2 = r2.profile.srcRange.width * r2.profile.srcRange.height;
        return area1 < area2;
    });

    for(auto &rc : m_records){
        Rect tmp;
        Rect &src = rc.profile.srcRange;
        Rect &dst = rc.profile.dstRange;

        if(!src) continue;
        tmp = layouter.laydown(src.width, src.height);
        dst = tmp;
    }

    m_packedWidth = layouter.packedWidth();
    m_packedHeight = layouter.packedHeight();
}

void Packer::packImage(){
    VImagePtr imgptr(new Image(m_packedWidth, m_packedHeight));
    if(imgptr == nullptr) throw runtime_error("Out of memory.");

    for(auto &rc : m_records){
        Rect &src = rc.profile.srcRange;
        Rect &dst = rc.profile.dstRange;

        if(!rc){
            cerr << "Ignore an image: " << rc.profile.id << ", because it may be an empty image." << endl;
            continue;
        }

        imgptr -> placeRect(dst.x, dst.y, *(rc.imgptr.get()), src);
    }

    m_image = imgptr;
}

PACKER_END