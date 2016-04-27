#pragma once

#include "../../../include/Nuz/FileSystem/LocalFile.h"
#include <cstdint>
namespace Nuz_{

    class LocalFile:public Nuz::ILocalFile{
    public:
        std::shared_ptr<std::vector<uint8_t>> ReadFile(const std::string& path) const override;
        void SaveFile(const std::shared_ptr<std::vector<uint8_t>>,const std::string& path) const override;
    };
}
