#ifndef GSERR_HPP
#define GSERR_HPP

#include <tuple>
#include <string>
#include <vector>
#include <iostream>
#include "packer/packer.hpp"
#include "packer/core/VImage.hpp"
PACKER_BEGIN

//============ Error Definition =================
enum class ErrCode{
    OK = 0,
    OutOfMem,
    OutOfBound
};

struct Err_Struct{
    ErrCode code;
    const char *what;
    const char *file;
    unsigned int row;

    Err_Struct(
        ErrCode code=ErrCode::OK,
        const char *what="",
        const char *file="",
        unsigned int row=0
    );

    operator std::string() const;
};

//============ Type Alias =================
using ebool             = std::tuple<Err_Struct, bool>;
using echar             = std::tuple<Err_Struct, char>;
using eshort            = std::tuple<Err_Struct, short>;
using eint              = std::tuple<Err_Struct, int>;
using efloat           = std::tuple<Err_Struct, float>;
using edouble       = std::tuple<Err_Struct, double>;
using estring          = std::tuple<Err_Struct, std::string>;
//--------- Only for libpacker ---------
using EVImagePtr    = std::tuple<Err_Struct, VImage*>;
using ERGBA            = std::tuple<Err_Struct, RGBA>;
using ERGBAPtr       = std::tuple<Err_Struct, RGBA*>;
using ERect              = std::tuple<Err_Struct, Rect>;
using EIndicator       = std::tuple<Err_Struct, Indicator>;
using EStringVector  = std::tuple<Err_Struct, std::vector<std::string>>;

PACKER_END

//============ Predefined =================
#define make_evalue(code, what, value) {{code, what, __FILE__, __LINE__}, value}
#define make_evalue_ok(value) make_evalue(ErrCode::OK, "", value)

//============ Overload =================
std::ostream &operator<<(std::ostream &os, const packer::Err_Struct &err);

#endif