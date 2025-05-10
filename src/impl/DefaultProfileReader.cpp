#include <string>
#include <stdexcept>
#include <memory>
#include <cstdio>
#include <cstring>
#include "packer/impl/DefaultProfileReader.hpp"

using std::logic_error;
using std::runtime_error;
PACKER_BEGIN

DefaultProfileReader::DefaultProfileReader(const std::string &path) : m_fileName(path){}

void DefaultProfileReader::initialize(){
    RFilePtr file(m_fileName.c_str(), "r");
    m_file = std::move(file);

    RCharBuffer buffer(1024);
    m_buffer = std::move(buffer);
}

bool DefaultProfileReader::read(Profile &profile){
    while(!feof(m_file.use())){
        memset(m_buffer.use(), 0, 1024);
        fgets(m_buffer.use(), 1024, m_file.use());
        
    }
}

void DefaultProfileReader::finalize(){
    
}

PACKER_END