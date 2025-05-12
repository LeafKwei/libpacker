#include <cstdio>
#include <cstring>
#include <stdexcept>
#include "packer/impl/DefaultProfileWriter.hpp"

using std::logic_error;
using std::runtime_error;
using std::string;
PACKER_BEGIN

DefaultProfileWriter::DefaultProfileWriter(const std::string &path) : m_fileName(path){

}

void DefaultProfileWriter::initialize(){
    FilePtr file(m_fileName.c_str(), "r");
    m_file = std::move(file);

    CharBuffer buffer(1024);
    m_buffer = std::move(buffer);
}

void DefaultProfileWriter::write(const Profile &profile){
    memset(m_buffer.use(), 0, 1024);
    sprintf(m_buffer.use(), "%s:(%d,%d,%d,%d),(%d,%d,%d,%d),%d\n", profile.id.c_str(), 
        profile.srcRange.x, profile.srcRange.y, profile.srcRange.width, profile.srcRange.height,
        profile.dstRange.x, profile.dstRange.y, profile.dstRange.width, profile.dstRange.height,
        1);
    fwrite(m_buffer.use(), 1, strlen(m_buffer.use()), m_file.use());
    if(ferror(m_file.use())) throw runtime_error("IO error.");
}

void DefaultProfileWriter::finalize(){

}

PACKER_END