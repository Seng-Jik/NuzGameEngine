#include "SnowRVReader.h"
#include "../../include/Nuz/Engine.h"
#include "../../include/NuzUtils/SnowRVReader.h"
#include "../../include/Nuz/FileSystem/FileSystem.h"
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
        if(p == string::npos) throw std::runtime_error("NuzUtils::ISnowRVReader::ISnowRVReader()::Can not get value type in line " + std::to_string(lineNum) + ".");
        string type = line.substr(0,p);

        //Get Name
        auto p2 = line.find('=');
        if(p == string::npos) throw std::runtime_error("NuzUtils::ISnowRVReader::ISnowRVReader()::Can not find \'+\' in line" + std::to_string(lineNum) + ".");
        string name = Trim(line.substr(p,p2-p));
        if(name.empty()) throw std::runtime_error("NuzUtils::ISnowRVReader::ISnowRVReader()::Invaild name in line" + std::to_string(lineNum) + ".");

        //Get Value
        string value = line.substr(p2+1,line.length()-p2-1);

        if(type == "INT"){
            auto s = Trim(value);
            if(s.empty()) throw std::runtime_error("NuzUtils::ISnowRVReader::ISnowRVReader()::Invaild int value in line " + std::to_string(lineNum) + ".");
            m_ints[name] = atoi(s.c_str());
        }else if(type == "FLOAT"){
            auto s = Trim(value);
            if(s.empty()) throw std::runtime_error("NuzUtils::ISnowRVReader::ISnowRVReader()::Invaild float value in line " + std::to_string(lineNum) + ".");
            m_flts[name] = atof(s.c_str());
        }else if(type == "STR"){
            auto ps1 = value.find('\"');
            value = value.substr(ps1+1,value.length()-ps1-1);
            auto ps2 = value.find('\"',ps1);
            if(ps1 == string::npos || ps2 == string::npos) throw std::runtime_error("NuzUtils::ISnowRVReader::ISnowRVReader()::Invaild string value in line " + std::to_string(lineNum) + ".");
            m_strs[name] = value.substr(0,ps2);
        }else{
            throw std::runtime_error("NuzUtils::ISnowRVReader::ISnowRVReader()::Unknow type \"" + type +"\" in line " + std::to_string(lineNum) + ".");
        }
        ++lineNum;
    }
}

std::string SnowRVReader::GetString(const std::string& s)
{
    if(m_strs.count(s)) return m_strs[s];
    else throw std::runtime_error("NuzUtils::ISnowRVReader::GetString()::String value " + s +" not found.");
}

int SnowRVReader::GetInt(const std::string& s)
{
    if(m_ints.count(s)) return m_ints[s];
    else throw std::runtime_error("NuzUtils::ISnowRVReader::GetInt()::Int value " + s +" not found.");
}

double SnowRVReader::GetFloat(const std::string& s)
{
    if(m_flts.count(s)) return m_flts[s];
    else throw std::runtime_error("NuzUtils::ISnowRVReader::GetFloat()::Float value " + s +" not found.");
}

std::shared_ptr<NuzUtils::ISnowRVReader> NuzUtils::CreateSnowRVReader(const std::string& path){
    return std::shared_ptr<NuzUtils::ISnowRVReader>(new SnowRVReader(path));
}
