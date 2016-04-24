#include "SnowRVReader.h"
#include "../../include/Nuz/Engine.h"
#include "../../include/NuzUtils/SnowRVReader.h"
#include "../../include/Nuz/FileSystem/FileSystem.h"
#include "../../include/Nuz/FileSystem/LocalFile.h"
#include <cstdlib>
using namespace Nuz;
using namespace std;
using namespace _NuzUtils;

std::string SnowRVReader::Trim(const std::string& s)
{
    string t;
    for(auto p = s.begin();p != s.end();++p)
        if(*p != ' ' && *p != '\t' && *p != '\0')
            t+=*p;
    return t;
}

SnowRVReader::SnowRVReader(const std::string& path)
{
    auto buf = GetGameDevice().GetFileSystem().LoadFile(path);

    //Read As Binary File
    if((*buf)[0] == 0xFF){
        unsigned int ptr = 4;
        unsigned int strSize,intSize,fltSize;
        for(unsigned int i = 0;i < sizeof(strSize);++i)
            ((unsigned char*)(&strSize))[i] = (*buf)[ptr++];
        for(unsigned int i = 0;i < sizeof(intSize);++i)
            ((unsigned char*)(&intSize))[i] = (*buf)[ptr++];
        for(unsigned int i = 0;i < sizeof(fltSize);++i)
            ((unsigned char*)(&fltSize))[i] = (*buf)[ptr++];

        //Read Float Values
        for(unsigned int fltNum = 0;fltNum < fltSize;++fltNum){
            unsigned int length;
            std::string name;
            for(unsigned int i = 0;i < sizeof(length);++i)
                ((unsigned char*)&length)[i] = (*buf)[ptr++];

            for(unsigned int i = 0;i < length;++i)
                name += (char)(*buf)[ptr++];
            double value;
            for(unsigned int i = 0;i < sizeof(value);++i)
                ((unsigned char*)(&value))[i] = (*buf)[ptr++];
            m_flts[name] = value;
        }

        //Read Int Values
        for(unsigned int intNum = 0;intNum < intSize;++intNum){
            unsigned int length;
            std::string name;
            for(unsigned int i = 0;i < sizeof(length);++i)
                ((unsigned char*)&length)[i] = (*buf)[ptr++];

            for(unsigned int i = 0;i < length;++i)
                name += (char)(*buf)[ptr++];
            int value;
            for(unsigned int i = 0;i < sizeof(value);++i)
                ((unsigned char*)(&value))[i] = (*buf)[ptr++];
            m_ints[name] = value;
        }

        //Read String Values
        for(unsigned int strNum = 0;strNum < strSize;++strNum){
            unsigned int length;
            std::string name;
            for(unsigned int i = 0;i < sizeof(length);++i)
                ((unsigned char*)&length)[i] = (*buf)[ptr++];
            for(unsigned int i = 0;i < length;++i)
                name += (char)(*buf)[ptr++];

            std::string value;
            for(unsigned int i = 0;i < sizeof(length);++i)
                ((unsigned char*)&length)[i] = (*buf)[ptr++];
            for(unsigned int i = 0;i < length;++i)
                value += (char)(*buf)[ptr++];
            m_strs[name] = value;
        }
        return;
    }

    unsigned int num = 0;
    unsigned int lineNum = 1;
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
        if(p == string::npos) throw SnowRVCompileFailed("NuzUtils::ISnowRVReader::ISnowRVReader()::Can not get value type in line " + std::to_string(lineNum) + ".");
        string type = line.substr(0,p);

        //Get Name
        auto p2 = line.find('=');
        if(p == string::npos) throw SnowRVCompileFailed("NuzUtils::ISnowRVReader::ISnowRVReader()::Can not find \'+\' in line" + std::to_string(lineNum) + ".");
        string name = Trim(line.substr(p,p2-p));
        if(name.empty()) throw SnowRVCompileFailed("NuzUtils::ISnowRVReader::ISnowRVReader()::Invaild name in line" + std::to_string(lineNum) + ".");

        //Get Value
        string value = line.substr(p2+1,line.length()-p2-1);

        if(type == "INT"){
            auto s = Trim(value);
            if(s.empty()) throw SnowRVCompileFailed("NuzUtils::ISnowRVReader::ISnowRVReader()::Invaild int value in line " + std::to_string(lineNum) + ".");
            m_ints[name] = atoi(s.c_str());
        }else if(type == "FLOAT"){
            auto s = Trim(value);
            if(s.empty()) throw SnowRVCompileFailed("NuzUtils::ISnowRVReader::ISnowRVReader()::Invaild float value in line " + std::to_string(lineNum) + ".");
            m_flts[name] = atof(s.c_str());
        }else if(type == "STR"){
            auto ps1 = value.find('\"');
            value = value.substr(ps1+1,value.length()-ps1-1);
            auto ps2 = value.find('\"',ps1);
            if(ps1 == string::npos || ps2 == string::npos) throw SnowRVCompileFailed("NuzUtils::ISnowRVReader::ISnowRVReader()::Invaild string value in line " + std::to_string(lineNum) + ".");
            m_strs[name] = value.substr(0,ps2);
        }else{
            throw SnowRVCompileFailed("NuzUtils::ISnowRVReader::ISnowRVReader()::Unknow type \"" + type +"\" in line " + std::to_string(lineNum) + ".");
        }
        ++lineNum;
    }
}

std::string SnowRVReader::GetString(const std::string& s)
{
    if(m_strs.count(s)) return m_strs[s];
    else throw ValueNotFound("NuzUtils::ISnowRVReader::GetString()::String value " + s +" not found.");
}

int SnowRVReader::GetInt(const std::string& s)
{
    if(m_ints.count(s)) return m_ints[s];
    else throw ValueNotFound("NuzUtils::ISnowRVReader::GetInt()::Int value " + s +" not found.");
}

double SnowRVReader::GetFloat(const std::string& s)
{
    if(m_flts.count(s)) return m_flts[s];
    else throw ValueNotFound("NuzUtils::ISnowRVReader::GetFloat()::Float value " + s +" not found.");
}

void SnowRVReader::SaveToFastReadFile(const std::string& file){
    std::shared_ptr<std::vector<unsigned char> > buf(new std::vector<unsigned char>);
    buf -> push_back(0xFF);
    buf -> push_back('N');
    buf -> push_back('u');
    buf -> push_back('z');

    unsigned int strSize = m_strs.size(),intSize = m_ints.size(),fltSize = m_flts.size();

    //Sizes Output
    for(unsigned int i = 0;i < sizeof(strSize);++i)
        buf -> push_back(((unsigned char*)&strSize)[i]);
    for(unsigned int i = 0;i < sizeof(intSize);++i)
        buf -> push_back(((unsigned char*)&intSize)[i]);
    for(unsigned int i = 0;i < sizeof(fltSize);++i)
        buf -> push_back(((unsigned char*)&fltSize)[i]);

    //Float values
    for(auto p = m_flts.begin();p != m_flts.end();++p){
        const std::string& s = p -> first;
        unsigned int length = s.length();
        for(unsigned int i = 0;i < sizeof(length);++i)
            buf -> push_back(((unsigned char*)&length)[i]);
        for(char c:s)
            buf -> push_back((unsigned char)c);

        for(unsigned int i = 0;i < sizeof(double);++i)
            buf -> push_back(((unsigned char*)&p->second)[i]);
    }

    //Int Values
    for(auto p = m_ints.begin();p != m_ints.end();++p){
        const std::string& s = p -> first;
        unsigned int length = s.length();
        for(unsigned int i = 0;i < sizeof(length);++i)
            buf -> push_back(((unsigned char*)&length)[i]);
        for(char c:s)
            buf -> push_back((unsigned char)c);

        for(unsigned int i = 0;i < sizeof(int);++i)
            buf -> push_back(((unsigned char*)&p->second)[i]);
    }

    //String Values
    for(auto p = m_strs.begin();p != m_strs.end();++p){
        const std::string& s = p -> first;
        unsigned int length = s.length();
        for(unsigned int i = 0;i < sizeof(length);++i)
            buf -> push_back(((unsigned char*)&length)[i]);
        for(char c:s)
            buf -> push_back((unsigned char)c);

        const std::string& s2 = p -> second;
        length = s2.length();
        for(unsigned int i = 0;i < sizeof(length);++i)
            buf -> push_back(((unsigned char*)&length)[i]);
        for(char c:s2)
            buf -> push_back((unsigned char)c);
    }
    Nuz::GetGameDevice().GetLocalFile().SaveFile(buf,file);
}

std::shared_ptr<NuzUtils::ISnowRVReader> NuzUtils::CreateSnowRVReader(const std::string& path){
    return std::shared_ptr<NuzUtils::ISnowRVReader>(new SnowRVReader(path));
}
