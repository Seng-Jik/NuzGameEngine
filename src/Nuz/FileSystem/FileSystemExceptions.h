#pragma once
#include <stdexcept>
namespace _Nuz{
    class Invalid_FileName:public std::invalid_argument{
    public:
        inline Invalid_FileName(const std::string& s):std::invalid_argument(s){};
    };
    class Cannot_OpenFile:public std::runtime_error{
    public:
        inline Cannot_OpenFile(const std::string& s):std::runtime_error(s){};
    };
}
