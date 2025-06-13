#include <sstream>
#include "gserr.hpp"

using std::string;
using std::stringstream;
using std::ostream;
using packer::Err_Struct;

//=========== Err_Struct ==============
Err_Struct::Err_Struct(ErrCode code, const char *what, const char *file, unsigned int row){
    this -> code = code;
    this -> what = what;
    this -> file = file;
    this -> row = row;
}

Err_Struct::Err_Struct(const Err_Struct &oth)
{
    this -> code = oth.code;
    this -> what = oth.what;
    this -> file = oth.file;
    this -> row = oth.row;
}

Err_Struct::operator string() const{
    stringstream stream;
    stream 
        << "code: " << static_cast<int>(code) 
        << ", what: " << what 
        << ", file_name: " << file 
        << ", row_number: " << row;

    return stream.str();
}

Err_Struct::operator bool() const{
    return code != ErrCode::OK;
}

//=========== Other functions ==============
ostream &operator<<(ostream &os, const Err_Struct &err){
    os << static_cast<string>(err);
    return os;
}