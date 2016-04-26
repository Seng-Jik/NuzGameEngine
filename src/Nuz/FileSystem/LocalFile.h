#pragma once

#include "../../../include/Nuz/FileSystem/LocalFile.h"

namespace Nuz_{

    class LocalFile:public Nuz::ILocalFile{
    public:
        virtual std::shared_ptr<std::vector<uint8_t>> ReadFile(const std::string& path) const;
        virtual uint32_t GetFileSize(const std::string& path) const;
        virtual void SaveFile(const std::shared_ptr<std::vector<uint8_t>>,const std::string path) const;
        virtual void CopyFile(const std::string& src,const std::string& dst) const;
    };
}
