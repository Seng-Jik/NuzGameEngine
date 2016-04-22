#pragma once
#include "../../include/NuzUtils/CSVReader.h"
#include <map>
#include <vector>

namespace _NuzUtils{

	class CSVReader:public NuzUtils::ICSVReader{
    private:
        std::vector<std::vector<std::string> > m_csvCache;
        unsigned int m_x,m_y;

	public:
        void Load(const std::string& csv);
		virtual std::string PopString();
		virtual float PopFloat();
		virtual double PopDouble();
		virtual int PopInt();
		virtual bool LineEnd();
		virtual bool NextLine();
		virtual bool IsLastLine();
		virtual void Reset();
		virtual void SaveToFastReadFile(const std::string&);
	};

	std::shared_ptr<NuzUtils::ICSVReader> CreateCSVReader(const std::string& path);
}

