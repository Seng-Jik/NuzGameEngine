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

        std::string m_currentDir;

        void loadFromBin(const std::shared_ptr<std::vector<uint8_t> >&);
        void loadFromText(const std::shared_ptr<std::vector<uint8_t> >&);
	public:
        void Load(const std::string& csv);
		std::string PopString() override;
        float PopFloat() override;
        double PopDouble() override;
        int PopInt() override;
        bool LineEnd() const override;
        bool NextLine() override;
        bool IsLastLine() const override;
        void Reset() override;
        std::string GetCurrentDir() const override;
        void SaveToBinaryFile(const std::string&) const override;
	};

	std::shared_ptr<NuzUtils::ICSVReader> CreateCSVReader(const std::string& path);
}

