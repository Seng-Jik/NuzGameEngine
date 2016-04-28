#include "SnowRVReader.h"
#include "../../include/Nuz/Engine.h"
#include "../../include/NuzUtils/SnowRVReader.h"
#include "../../include/Nuz/FileSystem/FileSystem.h"
#include "../../include/Nuz/FileSystem/LocalFile.h"
#include <cstdlib>
using namespace Nuz;
using namespace std;
using namespace NuzUtils_;

std::string SnowRVReader::Trim(const std::string& s)
{
    string t;
    for(auto p = s.begin();p != s.end();++p)
        if(*p != ' ' && *p != '\t' && *p != '\0')
            t+=*p;
    return t;
}

void SnowRVReader::loadFromBin(std::shared_ptr<std::vector<uint8_t> > buf)
{
    uint32_t ptr = 4;
    uint32_t strSize,intSize,fltSize;
    for(uint32_t i = 0;i < sizeof(strSize);++i)
        ((uint8_t*)(&strSize))[i] = (*buf)[ptr++];
    for(uint32_t i = 0;i < sizeof(intSize);++i)
        ((uint8_t*)(&intSize))[i] = (*buf)[ptr++];
    for(uint32_t i = 0;i < sizeof(fltSize);++i)
        ((uint8_t*)(&fltSize))[i] = (*buf)[ptr++];

    //Read Float Values
    for(uint32_t fltNum = 0;fltNum < fltSize;++fltNum){
        uint32_t length;
        std::string name;
        for(uint32_t i = 0;i < sizeof(length);++i)
            ((uint8_t*)&length)[i] = (*buf)[ptr++];

        for(uint32_t i = 0;i < length;++i)
            name += (char)(*buf)[ptr++];
        double value;
        for(uint32_t i = 0;i < sizeof(value);++i)
            ((uint8_t*)(&value))[i] = (*buf)[ptr++];
        m_flts[name] = value;
    }

    //Read Int Values
    for(uint32_t intNum = 0;intNum < intSize;++intNum){
        uint32_t length;
        std::string name;
        for(uint32_t i = 0;i < sizeof(length);++i)
            ((uint8_t*)&length)[i] = (*buf)[ptr++];

        for(uint32_t i = 0;i < length;++i)
            name += (char)(*buf)[ptr++];
        int value;
        for(uint32_t i = 0;i < sizeof(value);++i)
            ((uint8_t*)(&value))[i] = (*buf)[ptr++];
        m_ints[name] = value;
    }

    //Read String Values
    for(uint32_t strNum = 0;strNum < strSize;++strNum){
        uint32_t length;
        std::string name;
        for(uint32_t i = 0;i < sizeof(length);++i)
            ((uint8_t*)&length)[i] = (*buf)[ptr++];
        for(uint32_t i = 0;i < length;++i)
            name += (char)(*buf)[ptr++];

        std::string value;
        for(uint32_t i = 0;i < sizeof(length);++i)
            ((uint8_t*)&length)[i] = (*buf)[ptr++];
        for(uint32_t i = 0;i < length;++i)
            value += (char)(*buf)[ptr++];
        m_strs[name] = value;
    }
}

void SnowRVReader::loadFromText(std::shared_ptr<std::vector<uint8_t> > buf)
{
    uint32_t num = 0;
    uint32_t lineNum = 1;
    bool bRun = true;
    while(bRun){
        //GetLine
        string line;
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

        //If it is a # or empty line
        if(Trim(line).empty()) continue;
        if(line[0] == '#') continue;

        //Get Type
        auto p = line.find(' ');
        if(p == string::npos) throw SnowRVCompileFailed("Can not get value type in line " + std::to_string(lineNum) + ".");
        string type = line.substr(0,p);

        //Get Name
        auto p2 = line.find('=');
        if(p == string::npos) throw SnowRVCompileFailed("Can not find \'+\' in line" + std::to_string(lineNum) + ".");
        string name = Trim(line.substr(p,p2-p));
        if(name.empty()) throw SnowRVCompileFailed("Invaild name in line" + std::to_string(lineNum) + ".");

        //Get Value
        string value = line.substr(p2+1,line.length()-p2-1);

        if(type == "INT"){
            auto s = Trim(value);
            if(s.empty()) throw SnowRVCompileFailed("Invaild int value in line " + std::to_string(lineNum) + ".");
            m_ints[name] = atoi(s.c_str());
        }else if(type == "FLOAT"){
            auto s = Trim(value);
            if(s.empty()) throw SnowRVCompileFailed("Invaild float value in line " + std::to_string(lineNum) + ".");
            m_flts[name] = atof(s.c_str());
        }else if(type == "STR"){
            auto ps1 = value.find('\"');
            value = value.substr(ps1+1,value.length()-ps1-1);
            auto ps2 = value.find('\"',ps1);
            if(ps1 == string::npos || ps2 == string::npos) throw SnowRVCompileFailed("Invaild string value in line " + std::to_string(lineNum) + ".");
            m_strs[name] = value.substr(0,ps2);
        }else{
            throw SnowRVCompileFailed("Unknow type \"" + type +"\" in line " + std::to_string(lineNum) + ".");
        }
        ++lineNum;
    }
}


SnowRVReader::SnowRVReader(const std::string& path)
{
    auto buf = IEngine::GetGameDevice().GetFileSystem().LoadFile(path);

    //If it is an empty file.
    if(buf -> size() == 0) throw SnowRVCompileFailed("It is an empty file.");
    //Read As Binary File
    if((*buf)[0] == 0xFF)
        loadFromBin(buf);
    else
        loadFromText(buf);
}

std::string SnowRVReader::GetString(const std::string& s) const
{
    if(m_strs.count(s)) return m_strs.at(s);
    else throw ValueNotFound("String value " + s +" not found.");
}

int SnowRVReader::GetInt(const std::string& s) const
{
    if(m_ints.count(s)) return m_ints.at(s);
    else throw ValueNotFound("Int value " + s +" not found.");
}

double SnowRVReader::GetFloat(const std::string& s) const
{
    if(m_flts.count(s)) return m_flts.at(s);
    else throw ValueNotFound("Float value " + s +" not found.");
}

void SnowRVReader::SaveToFastReadFile(const std::string& file) const{
    std::shared_ptr<std::vector<uint8_t> > buf(new std::vector<uint8_t>);
    buf -> push_back(0xFF);
    buf -> push_back('N');
    buf -> push_back('u');
    buf -> push_back('z');

    uint32_t strSize = m_strs.size(),intSize = m_ints.size(),fltSize = m_flts.size();

    //Sizes Output
    for(uint32_t i = 0;i < sizeof(strSize);++i)
        buf -> push_back(((uint8_t*)&strSize)[i]);
    for(uint32_t i = 0;i < sizeof(intSize);++i)
        buf -> push_back(((uint8_t*)&intSize)[i]);
    for(uint32_t i = 0;i < sizeof(fltSize);++i)
        buf -> push_back(((uint8_t*)&fltSize)[i]);

    //Float values
    for(auto p = m_flts.begin();p != m_flts.end();++p){
        const std::string& s = p -> first;
        uint32_t length = s.length();
        for(uint32_t i = 0;i < sizeof(length);++i)
            buf -> push_back(((uint8_t*)&length)[i]);
        for(char c:s)
            buf -> push_back((uint8_t)c);

        for(uint32_t i = 0;i < sizeof(double);++i)
            buf -> push_back(((uint8_t*)&p->second)[i]);
    }

    //Int Values
    for(auto p = m_ints.begin();p != m_ints.end();++p){
        const std::string& s = p -> first;
        uint32_t length = s.length();
        for(uint32_t i = 0;i < sizeof(length);++i)
            buf -> push_back(((uint8_t*)&length)[i]);
        for(char c:s)
            buf -> push_back((uint8_t)c);

        for(uint32_t i = 0;i < sizeof(int);++i)
            buf -> push_back(((uint8_t*)&p->second)[i]);
    }

    //String Values
    for(auto p = m_strs.begin();p != m_strs.end();++p){
        const std::string& s = p -> first;
        uint32_t length = s.length();
        for(uint32_t i = 0;i < sizeof(length);++i)
            buf -> push_back(((uint8_t*)&length)[i]);
        for(char c:s)
            buf -> push_back((uint8_t)c);

        const std::string& s2 = p -> second;
        length = s2.length();
        for(uint32_t i = 0;i < sizeof(length);++i)
            buf -> push_back(((uint8_t*)&length)[i]);
        for(char c:s2)
            buf -> push_back((uint8_t)c);
    }
    Nuz::IEngine::GetGameDevice().GetLocalFile() -> SaveFile(buf,file);
}

std::shared_ptr<NuzUtils::ISnowRVReader> NuzUtils::ISnowRVReader::CreateSnowRVReader(const std::string& path){
    return std::shared_ptr<NuzUtils::ISnowRVReader>(new SnowRVReader(path));
}
