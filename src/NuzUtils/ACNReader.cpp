#include "ACNReader.h"
#include "../../include/Nuz/Engine.h"
#include "../../include/Nuz/FileSystem/FileSystem.h"
#include "../../include/Nuz/FileSystem/LocalFile.h"
#include <iostream>

using namespace NuzUtils_;
using namespace NuzUtils;
using namespace std;

//删除左边所有的空格和制表符，并过滤\r,和其它文件的Trim不同
static std::string Trim(const std::string& s)
{
    std::string t;
    bool killSpace = true;
    for(auto p = s.begin();p != s.end();++p){
        if(((*p != ' ' && *p != '\t') || !killSpace)&& *p != '\r'){
            t+=*p;
            killSpace = false;
        }
    }
    return t;
}

//删除所有空格
static std::string Trim2(const std::string& s)
{
    std::string t;
    for(auto p = s.begin();p != s.end();++p){
        if(*p != ' ' && *p != '\t' && *p != '\r'){
            t+=*p;
        }
    }
    return t;
}

void ACNReader::loadFromText(const std::shared_ptr<std::vector<uint8_t> >& buf)
{
    uint32_t num = 0;
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
            opr.arg.clear();
            m_oprs.push_back(opr);
        }else if(line[0] == '-'){
            opr.opr = NuzUtils::IACNReader::ACNOpr::CreateVar;
            auto pos = line.find(':');  //此处需要一个检测npos的报错
            opr.arg = line.substr(1,pos-1);
            if(pos == string::npos) throw NuzUtils::IACNReader::InvalidACN("Split symbol not found in this ACN file.");
            m_oprs.push_back(opr);
            //TODO:在此处分割出各个值并且创建指令
            string args = line.substr(pos+1,line.length()-pos-1);
            opr.opr = NuzUtils::IACNReader::ACNOpr::AddVal;
            bool bSplitRun = true;
            while(bSplitRun){
                pos = args.find(',');
                if(pos == string::npos){
                    opr.arg = args;
                    bSplitRun = false;
                }else{
                    opr.arg = args.substr(0,pos);
                    args = args.substr(pos+1,args.length()-pos-1);
                }
                auto lpos = opr.arg.find('\"'),rpos = opr.arg.rfind('\"');
                if(lpos != string::npos && rpos != string::npos){
                    opr.arg = opr.arg.substr(lpos+1,rpos-lpos-1);
                }else{
                    opr.arg = Trim2(opr.arg);
                }
                m_oprs.push_back(opr);
            }
        }
        else cout<<"Line:"<<line<<endl;
    }
}

void ACNReader::loadFromBinary(const std::shared_ptr<std::vector<uint8_t> >& buf)
{
    //Read Count
    uint32_t count = *(uint32_t*)&(*buf)[4];

    auto pos = 4+sizeof(count);
    ACNOprStruct opr;
    for(uint32_t i = 0;i < count;++i){
        opr.arg.clear();

        //Read Opr
        opr.opr = (NuzUtils::IACNReader::ACNOpr)(*buf)[pos++];

        //Read Arg
        uint16_t length = *(uint16_t*)&(*buf)[pos];pos+=sizeof(uint16_t);
        for(int i = 0;i < length;++i)
            opr.arg += (char)(*buf)[pos++];

        m_oprs.push_back(opr);
    }
}


NuzUtils::IACNReader::ACNOpr ACNReader::GetOpr(std::string& arg) noexcept
{
    if(m_now == m_oprs.end()){
        arg.clear();
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

    if(buf -> empty()) throw InvalidACN("This is an empty acn file.");
    else if((*buf)[0] == 0xFF) loadFromBinary(buf);
    else loadFromText(buf);

    Reset();
    m_currentDir = eng.GetFileSystem().GetUpperDir(path);
}

void ACNReader::SaveToBinaryFile(const std::string& path) const
{
    std::shared_ptr<std::vector<uint8_t> > buf(new std::vector<uint8_t>);
    buf -> push_back(0xFF);
    buf -> push_back('N');
    buf -> push_back('u');
    buf -> push_back('z');

    //Write Count
    uint32_t count = m_oprs.size();
    for(uint32_t i = 0;i < sizeof(count);++i)
        buf -> push_back(((uint8_t*)&count)[i]);

    //Write Oprs
    for(auto& opr:m_oprs){
        buf -> push_back((uint8_t)opr.opr);

        uint16_t length = opr.arg.length();
        for(uint32_t i = 0;i < sizeof(length);++i)
            buf -> push_back(((uint8_t*)&length)[i]);
        for(char c:opr.arg){
            buf -> push_back((uint8_t)c);
        }
    }

    Nuz::IEngine::GetGameDevice().GetLocalFile() -> SaveFile(buf,path);
}

std::string ACNReader::GetCurrentDir() const noexcept
{
    return m_currentDir;
}

std::shared_ptr<IACNReader> NuzUtils::IACNReader::CreateACNReader(const std::string& path){
    auto ptr = new ACNReader;
    ptr -> Load(path);
    return std::shared_ptr<IACNReader>(ptr);
}
