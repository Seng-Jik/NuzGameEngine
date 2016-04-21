#pragma once
#include <stdexcept>
namespace Nuz{
    /* �쳣�ࣺ������ļ�����ʽ */
    class InvalidFileName:public std::invalid_argument{
    public:
        inline InvalidFileName(const std::string& s):std::invalid_argument(s){};
    };

    /* �쳣�ࣺ�޷����ļ� */
    class CannotOpenFile:public std::runtime_error{
    public:
        inline CannotOpenFile(const std::string& s):std::runtime_error(s){};
    };

}
