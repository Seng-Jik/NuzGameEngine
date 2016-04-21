#pragma once
#include <map>
#include "../../include/NuzUtils/SnowRVReader.h"

namespace _NuzUtils{

	class SnowRVReader:public NuzUtils::ISnowRVReader{
    private:
        std::map<std::string,int> m_ints;
        std::map<std::string,float> m_flts;
        std::map<std::string,std::string> m_strs;

        std::string Trim(const std::string& s);
	public:
	    SnowRVReader(const std::string& path);
		virtual std::string GetString(const std::string&);
		virtual int GetInt(const std::string&);
		virtual double GetFloat(const std::string&);
	};

}