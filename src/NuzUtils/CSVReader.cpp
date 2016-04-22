#include "CSVReader.h"
#include "../../include/Nuz/Engine.h"
#include "../../include/Nuz/FileSystem/FileSystem.h"

using namespace _NuzUtils;
using namespace NuzUtils;

static std::string Trim(const std::string& s)
{
    std::string t;
    for(auto p = s.begin();p != s.end();++p)
        if(*p != ' ' && *p != '\t' && *p != '\0')
            t+=*p;
    return t;
}

std::shared_ptr<ICSVReader> NuzUtils::CreateCSVReader(const std::string& path){
    auto p = new CSVReader;
    p -> Load(path);
    return std::shared_ptr<ICSVReader>(p);
}

void CSVReader::Load(const std::string& csv){
    Nuz::IEngine& eng = Nuz::GetGameDevice();
    auto buf = eng.GetFileSystem().LoadFile(csv);
    m_csvCache.clear();

    unsigned int num = 0;
    unsigned int lineNum = 1;
    bool bRun = true;
    while(bRun){
        //GetLine
        std::string line;
        bool bGetLine_Run = true;
        while(bGetLine_Run){
            if(num >= buf -> size()){
                bRun = false;
                bGetLine_Run = false;
            }
            char c = (*buf)[num++];
            if(num >= buf -> size()){
                bRun = false;
                bGetLine_Run = false;
            }
            if(c == '\n') break;
            else if(c == '\r') break;
            else line += c;
        }
        if(Trim(line).empty()) continue;
        m_csvCache.push_back(std::vector<std::string>());
        auto p = m_csvCache.end();
        p--;


        //Read Units
        bool bGetUnitRun = true;
        while(bGetUnitRun){
            std::string thisUnit;
            auto pNextComma = line.find(',');
            if(pNextComma == std::string::npos){
                bGetUnitRun = false;
                thisUnit = line;
            }
            else{
                thisUnit = line.substr(0,pNextComma);
                line = line.substr(pNextComma+1,line.length() - pNextComma - 1);
            }
            p -> push_back(thisUnit);
        }
        ++lineNum;
    }
    Reset();
}

std::string CSVReader::PopString(){
    if(LineEnd()) throw std::runtime_error("NuzUtil::CSVReader::Pop*()::This line is end.");
    return m_csvCache[m_y][m_x++];
}

double CSVReader::PopDouble(){
    return atof(PopString().c_str());
}

float CSVReader::PopFloat(){
    return PopDouble();
}

int CSVReader::PopInt(){
    return atoi(PopString().c_str());
}

bool CSVReader::LineEnd(){
    return m_x >= m_csvCache[m_y].size();
}

bool CSVReader::NextLine(){
    if(IsLastLine()) throw std::runtime_error("NuzUtil::CSVReader::NextLine()::CSV Table End.");
    m_y++;
    m_x = 0;
    return !IsLastLine();
}

bool CSVReader::IsLastLine(){
    return m_y >= m_csvCache.size();
}

void CSVReader::Reset(){
    m_x = m_y = 0;
}
