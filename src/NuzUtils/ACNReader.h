#pragma once
#include "../../include/NuzUtils/ACNReader.h"
#include <vector>

namespace NuzUtils_{

	class ACNReader:public NuzUtils::IACNReader{
    private:
        struct ACNOprStruct{
            NuzUtils::IACNReader::ACNOpr opr;
            std::string arg;
        };
        std::vector<ACNOprStruct> m_oprs;
        std::vector<ACNOprStruct>::iterator m_now;

        std::string m_currentDir;

        void loadFromText(const std::shared_ptr<std::vector<uint8_t> >& buf);
        void loadFromBinary(const std::shared_ptr<std::vector<uint8_t> >& buf);
	public:
        NuzUtils::IACNReader::ACNOpr GetOpr(std::string& arg) noexcept override;
        void Reset() noexcept override;
        void SaveToBinaryFile(const std::string&) const override;
        std::string GetCurrentDir() const noexcept override;
        void Load(const std::string& path);
	};
}
