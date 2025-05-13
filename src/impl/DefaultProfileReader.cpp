#include <string>
#include <stdexcept>
#include <memory>
#include <cstdio>
#include <cstring>
#include "packer/impl/DefaultProfileReader.hpp"

using std::logic_error;
using std::runtime_error;
using std::string;
PACKER_BEGIN

DefaultProfileReader::DefaultProfileReader(const std::string &path) : m_fileName(path), m_file(path.c_str(), "r"), m_buffer(1024){}
DefaultProfileReader::~DefaultProfileReader(){}

Indicator DefaultProfileReader::read(Profile &profile){
    int eop = 0;
    CharBuffer idBuffer(1024);

    if(feof(m_file.use())) return Indicator::RD_EOF;
    memset(m_buffer.use(), 0, 1024);
    memset(idBuffer.use(), 0, 1024);
    char* ret = fgets(m_buffer.use(), 1024, m_file.use());
    if(ferror(m_file.use())) throw runtime_error("IO error.");

    sscanf(m_buffer.use(), "%s : (%d,%d,%d,%d),(%d,%d,%d,%d),%d", idBuffer.use(), 
        &(profile.srcRange.x), &(profile.srcRange.y), &(profile.srcRange.width), &(profile.dstRange.height),
        &(profile.dstRange.x), &(profile.dstRange.y), &(profile.dstRange.width), &(profile.dstRange.height),
        &eop);
    
    profile.id = string(idBuffer.use());
    return eop ? Indicator::RD_OK : Indicator::RD_INCOMPLETE;
}

PACKER_END