#include <iostream>
#include <stdexcept>
#include <memory>
#include "packer/impl/Image.hpp"
#include "packer/impl/Unpacker.hpp"

using std::logic_error;
using std::runtime_error;
using std::out_of_range;
using std::unique_ptr;
using std::vector;
using std::string;
using std::cerr;
using std::endl;
using std::make_pair;
PACKER_BEGIN

Unpacker::Unpacker(VImageReader *imgReader, VProfileReader *prfReader) : 
    m_state(State::UPK_NOP), m_image(nullptr), 
    m_imgReader(nullptr), m_prfReader(nullptr) 
{
    if(imgReader == nullptr || prfReader == nullptr) throw logic_error("Reader should not be nullptr.");
    m_imgReader = VImageReaderPtr(imgReader);
    m_prfReader = VProfileReaderPtr(prfReader);
}

Unpacker::~Unpacker(){
    
}

void Unpacker::unpack(){
    if(m_state == State::UPK_UNPACKED) throw logic_error("Can not unpack repeatly.");

    try{
        m_image = m_imgReader -> read();
        readProfiles();
        m_state = State::UPK_UNPACKED;
    }
    catch(logic_error &err){
        throw logic_error(string("Failed: ") + err.what());
    }
    catch(runtime_error &err){
        throw logic_error(string("*Failed: ") + err.what());
    }
}

VImage* Unpacker::getImageById(const std::string &id){
    if(m_state  != State::UPK_UNPACKED) throw logic_error("Unpack first.");
    if(m_profiles.find(id) == m_profiles.cend()) return nullptr;

    try{
        VImage *img = dumpImage(m_profiles.at(id));
        return img;
    }
    catch(logic_error &err){
        throw logic_error(string("Failed: ") + err.what());
    }
    catch(runtime_error &err){
        throw logic_error(string("*Failed: ") + err.what());
    }
}

std::vector<std::string> Unpacker::idList(){
    if(m_state  != State::UPK_UNPACKED) throw logic_error("Unpack first.");

    vector<string> idvec;
    for(auto &p : m_profiles){
        idvec.push_back(p.first);
    }

    return idvec;
}

void Unpacker::readProfiles(){
    Profile prf;
    Indicator ind;

    while((ind = m_prfReader -> read(prf)) != Indicator::RD_EOF){
        if(ind == Indicator::RD_INCOMPLETE){
            cerr << "Incomplete profile will be ignored(It may be an blank line)." << endl;
            continue;
        }

        m_profiles.insert(make_pair(prf.id, prf));
    }
}

VImage* Unpacker::dumpImage(const Profile &prf){
    VImage *img = new Image(prf.srcRange.width, prf.srcRange.height);
    if(img == nullptr) throw runtime_error("Out of memory.");
    
    Rect realRange;
    realRange.x = prf.dstRange.x;
    realRange.y = prf.dstRange.y;
    realRange.width = prf.srcRange.width;
    realRange.height = prf.srcRange.height;
    img -> placeRect(0, 0, *m_image, realRange);
    return img;
}

PACKER_END