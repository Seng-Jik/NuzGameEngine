#pragma once
#include "../../include/NuzUtils/CSVReader.h"
#include <map>
#include <vector>
#include <memory>

namespace NuzUtils_{

	class CSVReader:public NuzUtils::ICSVReader{
    private:
        std::vector<std::vector<std::string> > m_csvCache;
        uint16_t m_x,m_y;

        void loadFromBin(std::shared_ptr<std::vector<uint8_t> >);
        void loadFromText(std::shared_ptr<std::vector<uint8_t> >);
	public:
        void Load(const std::string& csv);
		std::string PopString() override;
        float PopFloat() override;
        double PopDouble() override;
        int PopInt() override;
        bool LineEnd() override;
        bool NextLine() override;
        bool IsLastLine() override;
        void Reset() override;
        void SaveToFastReadFile(const std::string&) override;
	};

	std::shared_ptr<NuzUtils::ICSVReader> CreateCSVReader(const std::string& path);
}

