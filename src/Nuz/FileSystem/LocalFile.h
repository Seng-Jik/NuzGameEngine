#pragma once

#include "../../../include/Nuz/FileSystem/LocalFile.h"

namespace _Nuz{

    class LocalFile:public Nuz::ILocalFile{
    public:
        virtual std::shared_ptr<std::vector<unsigned char>> ReadFile(const std::string& path) const;
        virtual unsigned long GetFileSize(const std::string& path) const;
        virtual void SaveFile(const std::shared_ptr<std::vector<unsigned char>>,const std::string path) const;
        virtual void CopyFile(const std::string& src,const std::string& dst) const;
    };
}
