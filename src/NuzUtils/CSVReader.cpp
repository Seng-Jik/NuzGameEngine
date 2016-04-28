#include "CSVReader.h"
#include "../../include/Nuz/Engine.h"
#include "../../include/Nuz/FileSystem/FileSystem.h"
#include "../../include/Nuz/FileSystem/LocalFile.h"

using namespace NuzUtils_;
using namespace NuzUtils;

static std::string Trim(const std::string& s)
{
    std::string t;
    for(auto p = s.begin();p != s.end();++p)
        if(*p != ' ' && *p != '\t' && *p != '\0')
            t+=*p;
    return t;
}

void CSVReader::loadFromBin(std::shared_ptr<std::vector<uint8_t> > buf)
{
    uint32_t ptr = 4;
    uint32_t lineCount;
    for(uint32_t i = 0;i < sizeof(lineCount);++i)
        ((uint8_t*)(&lineCount))[i] = (*buf)[ptr++];
    for(uint32_t lineNum = 0;lineNum < lineCount;++lineNum){
        //ReadLine
        //Line Size
        uint32_t lineSize;
        for(uint32_t i = 0;i < sizeof(lineSize);++i)
            ((uint8_t*)(&lineSize))[i] = (*buf)[ptr++];
            m_csvCache.push_back(std::vector<std::string>());
            auto p = m_csvCache.end();
            p--;
            //Read Units
        for(uint32_t unitNum = 0;unitNum < lineSize;++unitNum){
            //Read String Size
            uint32_t length;
            std::string unit;
            for(uint32_t i = 0;i < sizeof(length);++i)
                ((uint8_t*)&length)[i] = (*buf)[ptr++];

            //GetUnit
            for(uint32_t i = 0;i < length;++i)
                unit += (char)(*buf)[ptr++];

            p -> push_back(unit);
        }

    }
}

void CSVReader::loadFromText(std::shared_ptr<std::vector<uint8_t> > buf)
{
    uint32_t num = 0;
    uint32_t lineNum = 1;
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
}


std::shared_ptr<ICSVReader> NuzUtils::ICSVReader::CreateCSVReader(const std::string& path){
    auto p = new CSVReader;
    p -> Load(path);
    return std::shared_ptr<ICSVReader>(p);
}

void CSVReader::Load(const std::string& csv){
    Nuz::IEngine& eng = Nuz::IEngine::GetGameDevice();
    auto buf = eng.GetFileSystem().LoadFile(csv);
    m_csvCache.clear();

    //If it is an empty file.
    if(buf -> size() == 0) throw InvalidCSV("It is an empty csv file.");
    //Read binary CSV
    if((*buf)[0] == 0xFF)
        loadFromBin(buf);
    else loadFromText(buf);

    Reset();
}

std::string CSVReader::PopString(){
    if(LineEnd()) throw ValueNotFound("This line is end.");
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
    if(IsLastLine()) throw ValueNotFound("CSV Table End.");
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

void CSVReader::SaveToFastReadFile(const std::string& file){
    std::shared_ptr<std::vector<uint8_t> > buf(new std::vector<uint8_t>);
    buf -> push_back(0xFF);
    buf -> push_back('N');
    buf -> push_back('u');
    buf -> push_back('z');
    uint32_t lineCount = m_csvCache.size();
    for(uint32_t i = 0;i < sizeof(lineCount);++i)
        buf -> push_back(((uint8_t*)&lineCount)[i]);

    for(std::vector<std::string>& thisLine:m_csvCache){
        uint32_t size = thisLine.size();
        for(uint32_t i = 0;i < sizeof(size);++i)
            buf -> push_back(((uint8_t*)&size)[i]);
        for(std::string& s:thisLine){
            uint32_t length = s.length();
            for(uint32_t i = 0;i < sizeof(length);++i)
                buf -> push_back(((uint8_t*)&length)[i]);
            for(char c:s){
                buf -> push_back((uint8_t)c);
            }
        }
    }
    Nuz::IEngine::GetGameDevice().GetLocalFile() -> SaveFile(buf,file);
}
