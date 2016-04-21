#pragma once
#include <stdexcept>
namespace Nuz{
    /* 异常类：错误的文件名格式 */
    class InvalidFileName:public std::invalid_argument{
    public:
        inline InvalidFileName(const std::string& s):std::invalid_argument(s){};
    };

    /* 异常类：无法打开文件 */
    class CannotOpenFile:public std::runtime_error{
    public:
        inline CannotOpenFile(const std::string& s):std::runtime_error(s){};
    };

}
