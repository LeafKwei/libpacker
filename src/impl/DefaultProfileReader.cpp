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

/**
 * 每调用一次read函数就从文件中读取一行文本，然后将文本解析为一个Profile，当读取到文件末尾时返回RD_EOF，
 * 如果解析得到的Profile有缺失(比如文本行是空行)，则返回RD_RD_INCOMPLETE，反之返回RD_OK
 * 
 * 文件的打开和关闭由FilePtr的RAII机制完成
 */
Indicator DefaultProfileReader::read(Profile &profile){
    int eop = 0;
    CharBuffer idBuffer(1024);
    if(feof(m_file.use())) return Indicator::RD_EOF;
    memset(m_buffer.use(), 0, 1024);
    memset(idBuffer.use(), 0, 1024);
    fgets(m_buffer.use(), 1024, m_file.use());
    if(ferror(m_file.use())) throw runtime_error("IO error.");

    sscanf(m_buffer.use(), "%s : (%d,%d,%d,%d),(%d,%d,%d,%d),%d", idBuffer.use(), 
        &(profile.srcRange.x), &(profile.srcRange.y), &(profile.srcRange.width), &(profile.srcRange.height),
        &(profile.dstRange.x), &(profile.dstRange.y), &(profile.dstRange.width), &(profile.dstRange.height),
        &eop);
    
    profile.id = string(idBuffer.use());
    return eop ? Indicator::RD_OK : Indicator::RD_INCOMPLETE;
}

PACKER_END