#include "ACNReader.h"
#include "../../include/Nuz/Engine.h"
#include "../../include/Nuz/FileSystem/FileSystem.h"
#include "../../include/Nuz/FileSystem/LocalFile.h"
#include <iostream>

using namespace NuzUtils_;
using namespace NuzUtils;
using namespace std;

//ɾ��������еĿո���Ʊ����������\r
static std::string Trim(const std::string& s)
{
    std::string t;
    bool killSpace = true;
    for(auto p = s.begin();p != s.end();++p){
        if(((*p != ' ' && *p != '\t') || !killSpace)&& *p != '/r'){
            t+=*p;
            killSpace = false;
        }
    }
    return t;
}

void ACNReader::loadFromText(const std::shared_ptr<std::vector<uint8_t> >& buf)
{
    uint32_t num = 0;
    uint32_t lineNum = 1;
    bool bRun = true;
    ACNOprStruct opr;
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
        line = Trim(line);
        if(line.empty()) continue;
        if(line[0] == '#') continue;

        if(line[0] == '@'){
            opr.opr = NuzUtils::IACNReader::ACNOpr::PushAndCreateNode;
            opr.arg = line.substr(1,line.length() - 1);
            m_oprs.push_back(opr);
        }else if(line[0] == '$'){
            if(line == "$end") opr.opr = NuzUtils::IACNReader::ACNOpr::Pop;
            m_oprs.push_back(opr);
        }else if(line[0] == '-'){
            opr.opr = NuzUtils::IACNReader::ACNOpr::CreateVar;
            auto pos = line.find(':');
            opr.arg = line.substr(1,pos-1);
            m_oprs.push_back(opr);
            //TODO:�ڴ˴��ָ������ֵ���Ҵ���ָ��
            //δ���
        }
        else cout<<"Line:"<<line<<endl;

    }
}

void ACNReader::loadFromBinary(const std::shared_ptr<std::vector<uint8_t> >& buf)
{

}


NuzUtils::IACNReader::ACNOpr ACNReader::GetOpr(std::string& arg) noexcept
{
    if(m_now == m_oprs.end()){
        return NuzUtils::IACNReader::ACNOpr::End;
    }else{
        arg = m_now -> arg;
        auto opr = m_now -> opr;
        ++m_now;
        return opr;
    }
}

void ACNReader::Reset() noexcept
{
    m_now = m_oprs.begin();
}

void ACNReader::Load(const std::string& path)
{
    Nuz::IEngine& eng = Nuz::IEngine::GetGameDevice();
    auto buf = eng.GetFileSystem().LoadFile(path);
    loadFromText(buf);
    Reset();
}


std::shared_ptr<IACNReader> NuzUtils::IACNReader::CreateACNReader(const std::string& path){
    auto ptr = new ACNReader;
    ptr -> Load(path);
    return std::shared_ptr<IACNReader>(ptr);
}
