#pragma once
#include <map>
#include <memory>
#include <vector>
#include <cstdint>
#include "../../include/NuzUtils/SnowRVReader.h"

namespace NuzUtils_{

	class SnowRVReader:public NuzUtils::ISnowRVReader{
    private:
        std::map<std::string,int> m_ints;
        std::map<std::string,double> m_flts;
        std::map<std::string,std::string> m_strs;

        std::string Trim(const std::string& s);

        void loadFromBin(std::shared_ptr<std::vector<uint8_t> >);
        void loadFromText(std::shared_ptr<std::vector<uint8_t> >);
	public:
	    SnowRVReader(const std::string& path);
        std::string GetString(const std::string&) override;
        int GetInt(const std::string&) override;
        double GetFloat(const std::string&) override;
        void SaveToFastReadFile(const std::string&) override;
	};

}
