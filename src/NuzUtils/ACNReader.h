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

        void loadFromText(const std::shared_ptr<std::vector<uint8_t> >& buf);
        void loadFromBinary(const std::shared_ptr<std::vector<uint8_t> >& buf);
	public:
        NuzUtils::IACNReader::ACNOpr GetOpr(std::string& arg) noexcept override;
        void Reset() noexcept override;
        void Load(const std::string& path);
	};
}
